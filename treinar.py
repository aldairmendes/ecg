import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType

print("Carregando datasets...")
train_df = pd.read_csv('data/mitbih_train.csv', header=None)
test_df = pd.read_csv('data/mitbih_test.csv', header=None)

X_train = train_df.iloc[:, :-1].values
y_train = train_df.iloc[:, -1].values
X_test = test_df.iloc[:, :-1].values
y_test = test_df.iloc[:, -1].values

print("Treinando o modelo Random Forest...")
model = RandomForestClassifier(n_estimators=100, n_jobs=-1, random_state=42)
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print(f"\nAcurácia no Teste: {accuracy_score(y_test, y_pred):.4f}")
print(classification_report(y_test, y_pred))

joblib.dump(model, 'data/modelo_ecg.pkl')
print("Modelo .pkl salvo!")

print("\nExportando para ONNX...")
initial_type = [('float_input', FloatTensorType([None, 187]))]
modelo_onnx = convert_sklearn(model, initial_types=initial_type)
with open("data/modelo_ecg.onnx", "wb") as f:
    f.write(modelo_onnx.SerializeToString())
print("Modelo ONNX salvo em data/modelo_ecg.onnx!")