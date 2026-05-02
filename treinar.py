import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib

# 1. Carregar os dados (ajustado para sua pasta 'data')
print("Carregando datasets...")
train_df = pd.read_csv('data/mitbih_train.csv', header=None)
test_df = pd.read_csv('data/mitbih_test.csv', header=None)

# 2. Separar características (X) e rótulos (y)
# Os sinais de ECG ocupam as primeiras 187 colunas; a última é a classe.
X_train = train_df.iloc[:, :-1].values
y_train = train_df.iloc[:, -1].values
X_test = test_df.iloc[:, :-1].values
y_test = test_df.iloc[:, -1].values

# 3. Treinar o modelo
# Usaremos Random Forest por ser robusto e lidar bem com sinais fuidorentos
print("Treinando o modelo Random Forest... Isso pode levar um minuto.")
model = RandomForestClassifier(n_estimators=100, n_jobs=-1, random_state=42)
model.fit(X_train, y_train)

# 4. Validar o modelo
y_pred = model.predict(X_test)
print(f"\nAcurácia no Teste: {accuracy_score(y_test, y_pred):.4f}")
print("\nRelatório de Classificação:")
print(classification_report(y_test, y_pred))

# 5. Salvar o modelo para o seu C++ usar depois
joblib.dump(model, 'data/modelo_ecg.pkl')
print("\nModelo salvo com sucesso em 'data/modelo_ecg.pkl'!")