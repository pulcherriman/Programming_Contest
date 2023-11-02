import numpy as np
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

def predict_equation(samples):
    # 入力データを準備
    X = np.array(samples)[:, :-1]  # N, D, Qの値
    y = np.array(samples)[:, -1]   # Xの値

    # 多項式特徴を生成
    poly = PolynomialFeatures(degree=2)  # 2次の多項式を使用。必要に応じてdegreeを変更可能
    X_poly = poly.fit_transform(X)

    # 多項式回帰を適用
    reg = LinearRegression().fit(X_poly, y)

    # 係数を表示
    print("Coefficients:", reg.coef_)
    print("Intercept:", reg.intercept_)

# ファイルからsamplesを読み取る
file_name = "predict_input.txt"  # ここに適切なファイル名を入れてください
samples = []

with open(file_name, 'r') as f:
    for line in f:
        # 各行からN, D, Q, Xの値を整数として抽出
        sample = list(map(int, line.strip().split()))
        samples.append(sample)

predict_equation(samples)
