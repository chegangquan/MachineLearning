import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

k_max = 5
k = 1

while k <= 5:
    # 画类半径
    targets = pd.read_csv("E:/k=" + str(k) + " targets_data.csv", header=None)  # 读取类别数据
    center = pd.read_csv("E:/k=" + str(k) + " center_data.csv", header=None)  # 读取中心点数据
    data = pd.read_csv("E:/data.txt", header=None)  # 读取完整数据

    data_x = data[0].values  # 所有数据点的x
    data_y = data[1].values  # 所有数据点的y

    center_x = center[0].values  # 中心点的x
    center_y = center[1].values  # 中心点的y

    data_col = 2

    distance_max = []  # 中心点与该类的所有点的最远距离，即半径
    for i in range(k):
        distance_max.append(0)

    for i in range(k):  # 计算半径
        for j in range(len(data)):
            if targets.values[0][j] == i:
                dis = sum((center.values[i] - data.values[j]) ** 2) ** 0.5
                if dis > distance_max[i]:
                    distance_max[i] = round(dis, 2)

    x = []  # 圆的x轴的取值范围（中心点x值 - 半径，中心点x值 + 半径）
    y = []  # 圆的y轴的取值范围 y = (r**2 - (x-中心点x值)**2)**0.5 + 中心点y值

    for i in range(k):
        x.append(np.arange(center.values[i][0] - distance_max[i], center.values[i][0] + distance_max[i], 0.0001))
        y.append([])
        y[i].append((distance_max[i] ** 2 - (x[i] - center.values[i][0]) ** 2) ** 0.5 + center.values[i][1])
        y[i].append(-1 * ((distance_max[i] ** 2 - (x[i] - center.values[i][0]) ** 2) ** 0.5) + center.values[i][1])

    plt.xlabel('X')
    plt.ylabel('Y')

    ax = plt.gca()
    ax.set_aspect(1)  # x,y轴等比例

    plt.xlim(-4, 12)
    plt.ylim(0, 12)

    plt.scatter(data_x, data_y, c=targets.values)
    plt.scatter(center_x, center_y, c='RED')
    plt.scatter([2], [6], s=100, marker="*")
    for i in range(k):
        for j in range(2):
            plt.plot(x[i], y[i][j], c="RED")
    plt.savefig("k=" + str(k) + " scatter.jpg")
    plt.show()

    k = k + 1

# 画wss曲线图
wss = pd.read_csv("E:/k_max=" + str(k_max) + " wss_data.csv", header=None)  # 读取wss数据
x = np.arange(1, k_max + 1, 1)
y = wss.values[0]
plt.scatter(x, y)
plt.plot(x, y)
plt.savefig("k_max=" + str(k_max) + " wss.jpg")
plt.show()

