import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType

# 1. Carregar os dados
print("Carregando datasets...")
train_df = pd.read_csv('data/mitbih_train.csv', header=None)
test_df  = pd.read_csv('data/mitbih_test.csv',  header=None)

X_train = train_df.iloc[:, :-1].values.astype('float32')
y_train = train_df.iloc[:,  -1].values.astype('int64')
X_test  = test_df.iloc[:,  :-1].values.astype('float32')
y_test  = test_df.iloc[:,   -1].values.astype('int64')

# 2. Treinar
print("Treinando o modelo Random Forest... (pode levar 1-2 minutos)")
model = RandomForestClassifier(n_estimators=100, n_jobs=-1, random_state=42)
model.fit(X_train, y_train)

# 3. Avaliar
y_pred = model.predict(X_test)
print(f"\nAcuracia no Teste: {accuracy_score(y_test, y_pred):.4f}")
print(classification_report(y_test, y_pred))

# 4. Salvar .pkl (backup)
joblib.dump(model, 'data/modelo_ecg.pkl')
print("Modelo .pkl salvo em data/modelo_ecg.pkl")

# 5. Exportar para ONNX  <-- isso é o que o C++ precisa
print("\nExportando para ONNX...")
initial_type = [('float_input', FloatTensorType([None, 187]))]
modelo_onnx = convert_sklearn(model, initial_types=initial_type)
with open("data/modelo_ecg.onnx", "wb") as f:
    f.write(modelo_onnx.SerializeToString())
print("Modelo ONNX salvo em data/modelo_ecg.onnx")
print("\nPronto! Execute 'make' ou 'make simulation' para compilar o classificador C++.")