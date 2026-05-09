#define ECG_PIN 36      // VP
#define LO_PLUS 32
#define LO_MINUS 33

int lastValue = 0;

void setup() {

  Serial.begin(115200);

  pinMode(ECG_PIN, INPUT);
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);

  // Melhor resolução ADC no ESP32
  analogReadResolution(12);

  delay(1000);
}

void loop() {

  // Detecta eletrodo desconectado
  if (digitalRead(LO_PLUS) == 1 || digitalRead(LO_MINUS) == 1) {

    Serial.println(0);
    delay(10);
    return;
  }

  // leitura bruta
  int raw = analogRead(ECG_PIN);

  // filtro simples
  int filtered = (raw + lastValue) / 2;

  lastValue = filtered;

  // MUITO IMPORTANTE:
  // apenas número no plotter (modifiquei)
  Serial.println(filtered);

  delay(15);
}