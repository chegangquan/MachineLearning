import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


# sigmoid函数
def sigmoid(z):
    return 1 / (1 + np.exp(-z))


# 画标准的sigmoid函数图
def draw_sigmoid():
    X = np.linspace(-10, 10, num=100)
    Y = sigmoid(X)
    plt.figure(figsize=(8, 6), dpi=100, facecolor='white')
    plt.plot(X, Y)
    plt.grid()
    plt.title('sigmoid')
    plt.xlabel('x')
    plt.ylabel('sigmoid(x)')
    plt.savefig("sigmoid.png")
    plt.show()


# 分类器
def classify(x, theta):
    z = theta[0] + theta[1] * x[0] + theta[2] * x[1]  # 代入模型
    if (sigmoid(z)) > 0.5:
        result = 1
        color = 'green'
    else:
        result = 0
        color = 'red'
    return result, color


def gradient_down(data, labels):
    alpha = 0.01  # 学习率
    cycle = 5000  # 迭代次数
    X = np.mat(data)
    Y = np.mat(labels).transpose()  # 标签，此时变为1列
    theta = np.ones((X.shape[1], 1))  # θ默认为1
    for i in range(cycle):
        h = X * theta  # 假设函数hθ(x)= θ0 + θ1*x1+ θ2*x2
        h = sigmoid(h)  # 拟合到sigmoid中
        gradient = (X.transpose() * (h - Y)) / 20  # J(θ)对θ求偏导，即得到梯度gradient
        theta = theta - alpha * gradient  # 梯度下降

    return theta.A


def plot(data, label, theta):
    dataX = np.array(data)
    fig = plt.figure()
    # 数据拟合结果画图
    ax = fig.add_subplot(111)
    x = dataX
    s, h = [], []
    for i in range(20):
        z = 0
        for j in range(3):
            z += theta[j] * x[i][j]  # h0
        h.append(z)
        s.append(sigmoid(z))
    ax.scatter(h, s)
    X = np.linspace(-10, 10, num=100)
    Y = sigmoid(X)
    ax.plot(X, Y, c='pink')
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('sigmoid(x)')
    plt.savefig("data_fitting.png")
    plt.show()
    # 划分样本数据为阴阳两类
    n = dataX.shape[0]
    X1, Y1, X2, Y2 = [], [], [], []
    for i in range(n):
        if label[i] == 0:  # 0类
            X1.append(dataX[i, 1])  # 坐标x
            Y1.append(dataX[i, 2])  # 坐标y
        else:  # 1类
            X2.append(dataX[i, 1])  # 坐标x
            Y2.append(dataX[i, 2])  # 坐标y

    # 画出样本数据的真实分布散点图
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(X1, Y1, s=30, c='red')  # 0类标红色
    ax.scatter(X2, Y2, s=30, c='green')  # 1类标记绿色

    # (2,6)的分类结果
    test = [2, 6]
    re, color = classify(test, theta)
    print(tuple(test), "属于类别 ", re)
    ax.scatter(test[0], test[1], s=100, marker='*', c=color)  # （2，6）

    # 加上决策边界
    x = np.arange(0, 10.0, 0.01)  # x轴范围，精度0.01
    '''
    根据θ0+θ1*x1+θ2*x2=0
    x2=(-θ0-θ1*x1)/θ2
    y=x2
    '''
    y = (-theta[0] - theta[1] * x) / theta[2]  # 决策边界
    ax.plot(x, y)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.savefig("classify.png")
    plt.show()


if __name__ == '__main__':
    draw_sigmoid()  # sigmoid函数标准图
    df = pd.read_csv('data.csv', header=None)  # 读取实验三的数据，已经打好标签
    dataMat = []  # 数据
    labelMat = []  # 标签
    row = df.shape[0]  # 数据行数
    for i in range(row):
        dataMat.append([1, df.iloc[i, 0], df.iloc[i, 1]])  # 数据部分,增加一维数据都为1
        labelMat.append(df.iloc[i, 2])  # 标签部分
    ta = gradient_down(dataMat, labelMat)  # 梯度下降求得最优参数θ
    plot(dataMat, labelMat, ta)  # 画出决策边界
