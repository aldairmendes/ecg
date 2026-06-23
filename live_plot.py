import argparse
import sys
import time
from collections import deque

import numpy as np
import matplotlib
# prefer an interactive GUI backend on Windows; try common options
for _bk in ('TkAgg', 'Qt5Agg', 'QtAgg', 'WXAgg', 'GTK3Agg', 'MacOSX'):
    try:
        # quick availability checks for common backends
        if _bk.startswith('Tk'):
            import tkinter  # type: ignore
        if _bk.startswith('Qt'):
            # prefer PyQt5 or PySide2 for Qt backends
            try:
                import PyQt5  # type: ignore
            except Exception:
                import PySide2  # type: ignore
        matplotlib.use(_bk, force=True)
        break
    except Exception:
        continue
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

try:
    import serial
    HAS_SERIAL = True
except Exception:
    HAS_SERIAL = False


def serial_generator(port, baudrate=115200):
    ser = serial.Serial(port, baudrate, timeout=1)
    try:
        while True:
            line = ser.readline().decode(errors='ignore').strip()
            if not line:
                continue
            # assume a single numeric value per line
            try:
                yield float(line)
            except ValueError:
                # skip non-numeric lines
                continue
    finally:
        ser.close()


def file_generator(path, column=None, delay=0.01):
    # read CSV-like file where samples are numeric and either one per line or comma-separated
    with open(path, 'r', errors='ignore') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = [p for p in line.split(',') if p != '']
            if column is None:
                for token in parts:
                    try:
                        yield float(token)
                    except Exception:
                        continue
                    time.sleep(delay)
            else:
                try:
                    yield float(parts[column])
                except Exception:
                    parts2 = line.split()
                    if not parts2:
                        continue
                    try:
                        yield float(parts2[column])
                    except Exception:
                        continue
                time.sleep(delay)


def simulate_sine(freq=1.0, fs=250, amplitude=1.0):
    t = 0.0
    dt = 1.0 / fs
    while True:
        yield amplitude * np.sin(2 * np.pi * freq * t)
        t += dt


def stdin_generator():
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        try:
            yield float(line)
        except ValueError:
            continue


def bandpass_fft(signal, fs, low=0.5, high=40.0):
    # simple FFT bandpass applied to a 1D numpy array
    n = len(signal)
    if n == 0:
        return signal
    freq = np.fft.rfftfreq(n, d=1.0 / fs)
    sp = np.fft.rfft(signal)
    mask = (freq >= low) & (freq <= high)
    sp[~mask] = 0
    filtered = np.fft.irfft(sp, n=n)
    return filtered


def detect_r_peaks(signal, fs, min_distance_s=0.35, threshold_factor=1.4):
    # very simple R-peak detection: local maxima above adaptive threshold
    if len(signal) < 3:
        return []
    # smooth by small moving average to reduce noise
    window = max(1, int(fs * 0.01))
    if window > 1:
        kernel = np.ones(window) / window
        smooth = np.convolve(signal, kernel, mode='same')
    else:
        smooth = signal

    mu = np.mean(smooth)
    sigma = np.std(smooth)
    threshold = mu + threshold_factor * sigma
    threshold = max(threshold, 0.2 * np.max(np.abs(smooth)))

    peaks = []
    mindist = int(min_distance_s * fs)
    for i in range(1, len(smooth) - 1):
        if smooth[i] > smooth[i - 1] and smooth[i] > smooth[i + 1] and smooth[i] > threshold:
            if not peaks or (i - peaks[-1]) >= mindist:
                peaks.append(i)
    return peaks


def draw_ecg_grid(ax, window_s, fs):
    # small square 0.04s per small box (25 mm/s -> 25 samples/s if fs==25) but keep time-based
    small_sec = 0.04
    major_sec = 0.2
    ax.set_facecolor('white')
    ax.set_xlim(-window_s, 0)
    # vertical lines
    left = -window_s
    right = 0
    xs_small = np.arange(left, right + small_sec, small_sec)
    xs_major = np.arange(left, right + major_sec, major_sec)
    for x in xs_small:
        ax.axvline(x, color='#f0f0f0', linewidth=0.6)
    for x in xs_major:
        ax.axvline(x, color='#e0e0e0', linewidth=1.0)
    # horizontal lines (amplitude grid)
    # assume display from -2.5 to 2.5, small box 0.1 mV
    y_min, y_max = ax.get_ylim()
    small_y = 0.1
    major_y = 0.5
    ys_small = np.arange(np.floor(y_min / small_y) * small_y, y_max + small_y, small_y)
    ys_major = np.arange(np.floor(y_min / major_y) * major_y, y_max + major_y, major_y)
    for y in ys_small:
        ax.axhline(y, color='#f7f7f7', linewidth=0.6)
    for y in ys_major:
        ax.axhline(y, color='#e8e8e8', linewidth=1.0)


def main():
    parser = argparse.ArgumentParser(description='Live ECG plot (serial, file or stdin source)')
    parser.add_argument('--serial', help='Serial port (e.g. COM3). If provided, reads lines from serial.')
    parser.add_argument('--file', help='CSV or text file with samples (one sample per line or CSV).')
    parser.add_argument('--stdin', action='store_true', help='Read numeric samples from stdin.')
    parser.add_argument('--window', type=float, default=5.0, help='Window length in seconds')
    parser.add_argument('--fs', type=float, default=250.0, help='Sampling frequency (Hz) for file/simulated source')
    parser.add_argument('--interval', type=int, default=40, help='Animation update interval in ms')
    args = parser.parse_args()

    if args.serial and not HAS_SERIAL:
        print('pyserial not installed; cannot use --serial. Falling back to file, stdin or simulation.')

    if args.stdin:
        gen = stdin_generator()
        fs = args.fs
    elif args.serial and HAS_SERIAL:
        gen = serial_generator(args.serial)
        fs = args.fs
    elif args.file:
        gen = file_generator(args.file, delay=1.0 / args.fs)
        fs = args.fs
    else:
        gen = simulate_sine(freq=1.0, fs=args.fs, amplitude=1.0)
        fs = args.fs

    window_samples = int(args.window * fs)
    buffer = deque([0.0] * window_samples, maxlen=window_samples)
    x = np.linspace(-args.window, 0, window_samples)

    # prefer a seaborn-like dark style if available, otherwise fall back
    for style_name in ('seaborn-dark', 'seaborn-darkgrid', 'seaborn', 'dark_background', 'ggplot', 'classic'):
        try:
            plt.style.use(style_name)
            break
        except Exception:
            continue
    fig, ax = plt.subplots(figsize=(9, 4))
    line, = ax.plot(x, np.array(buffer), color='k', lw=1.2)
    ax.set_ylim(-2.5, 2.5)
    ax.set_xlim(-args.window, 0)
    ax.set_xlabel('Time (s)')
    ax.set_ylabel('Amplitude (a.u.)')
    ax.set_title('ECG Live Plot')

    # draw ECG-like grid once
    draw_ecg_grid(ax, args.window, fs)

    # markers for detected R-peaks and BPM text
    peak_markers, = ax.plot([], [], 'ro', markersize=5, alpha=0.9)
    bpm_text = ax.text(0.02, 0.96, '', transform=ax.transAxes, fontsize=12, verticalalignment='top')

    tooltip = ax.annotate(
        '', xy=(0, 0), xytext=(15, 15), textcoords='offset points',
        color='white',
        bbox=dict(boxstyle='round', fc='#222', alpha=0.9, ec='white'),
        arrowprops=dict(arrowstyle='->', connectionstyle='arc3,rad=0', color='white'))
    tooltip.set_visible(False)

    last_bpm = None
    last_peak_times = np.array([])

    def compute_hover_bpm(x):
        nonlocal last_peak_times
        if len(last_peak_times) < 2:
            return None
        deltas = np.abs(last_peak_times - x)
        mask = deltas <= 1.5
        if np.sum(mask) >= 2:
            local_times = np.sort(last_peak_times[mask])
        else:
            local_times = np.sort(last_peak_times)

        if len(local_times) < 2:
            return None

        rr = np.diff(local_times)
        rr = rr[(rr > 0.3) & (rr < 2.0)]
        if rr.size == 0:
            return None

        bpm = 60.0 / np.median(rr[-4:])
        if bpm < 30 or bpm > 220:
            return None
        return bpm

    def on_mouse_move(event):
        if event.inaxes != ax or event.xdata is None:
            tooltip.set_visible(False)
            fig.canvas.draw_idle()
            return

        hover_bpm = compute_hover_bpm(event.xdata)
        if hover_bpm is None:
            tooltip.set_text(f'BPM local: --\nTempo: {event.xdata:.2f}s')
        else:
            tooltip.set_text(f'BPM local: {hover_bpm:.0f}\nTempo: {event.xdata:.2f}s')

        tooltip.xy = (event.xdata, event.ydata if event.ydata is not None else 0)
        tooltip.set_visible(True)
        fig.canvas.draw_idle()

    fig.canvas.mpl_connect('motion_notify_event', on_mouse_move)

    def update(frame):
        nonlocal last_bpm, last_peak_times
        try:
            value = next(gen)
        except StopIteration:
            return line, peak_markers, bpm_text
        except Exception:
            return line, peak_markers, bpm_text

        buffer.append(value)
        y = np.array(buffer)

        # apply bandpass to make waveform look like ECG
        filtered = bandpass_fft(y, fs, low=0.5, high=40.0)

        # normalize for display
        scale = np.percentile(np.abs(filtered), 99) if filtered.size else 1.0
        if scale <= 0:
            scale = 1.0
        display_y = filtered / (scale + 1e-12)

        line.set_ydata(display_y)

        # detect R-peaks in the current buffer
        peaks = detect_r_peaks(display_y, fs, min_distance_s=0.25, threshold_factor=0.9)
        # convert peak indices to times for plotting
        if peaks:
            peak_times = -args.window + np.array(peaks) / fs
            peak_vals = display_y[peaks]
            peak_markers.set_data(peak_times, peak_vals)
            last_peak_times = peak_times
        else:
            peak_markers.set_data([], [])
            last_peak_times = np.array([])

        # compute BPM from last few peaks
        bpm = None
        if len(peaks) >= 2:
            rr = np.diff(np.array(peaks)) / fs
            rr = rr[(rr >= 0.35) & (rr <= 1.5)]
            if len(rr) >= 2:
                rr_med = np.median(rr[-8:])
                if rr_med > 0:
                    bpm = 60.0 / rr_med
                    if 30 <= bpm <= 220:
                        last_bpm = bpm
        if bpm is None:
            bpm = last_bpm

        bpm_text.set_text(f'HR: {bpm:.0f} BPM' if bpm is not None else 'HR: -- BPM')

        return line, peak_markers, bpm_text

    anim = FuncAnimation(fig, update, interval=args.interval, blit=False, cache_frame_data=False)
    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    main()
