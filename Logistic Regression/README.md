# Logistic
#实验四  《逻辑回归二分类》
## 组员信息

组长：陈港泉

组员：黎家豪


## 作业题目和内容

学习sigmoid函数和逻辑回归算法。将实验三.2中的样例数据用聚类的结果打标签{0，1}，并用逻辑回归模型拟合。
1. 学习并画出sigmoid函数
2. 设计梯度下降算法，实现逻辑回归模型的学习过程。
3. 根据给定数据（实验三.2），用梯度下降算法进行数据拟合，并用学习好的模型对(2,6)分类。
（对2,3实现有难度的同学，可以直接调用sklearn中LogisticRegression进行学习）

## data文件

| X | Y   |  类别  |
|-----|-----:| :----:  |
|3.45| 7.08 |1|
|4.29|9.55|1
|3.35|6.65|1
|3.17|6.41|1
|3.68|5.99|1
|2.11|4.08|1
|2.58|7.1|1
|3.45|7.88|1
|6.17|5.4|0
|4.2|6.46|1
|5.87|3.87|0
|5.47|2.21|0
|5.97|3.62|0
|6.24|3.06|0
|6.89|2.41|0
|5.38|2.32|0
|5.13|2.73|0
|7.26|4.19|0
|6.32|3.62|0

## 基于Logistic回归和Sigmoid函数的分类
### 1 sigmoid函数
>f( x )=1/( 1+e^-x )
当x为0时，sigmoid函数的值为0.5，随着x的增大，对应的函数值将逼近1；而随着x的减小，对应的函数值将逼近0

### 2 sigmoid函数图

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021010922393958.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)


### 3 logistic回归
为了实现Logistic回归分类器，我们可以在每个特征上都乘上一个回归系数，然后把所有结果的值相加，将这个总和代入sigmoid函数中，进而得到一个范围在0~1之间的值。这样我们就可以将大于0.5的数据分入1类，小于0.5的分入0类。
现在我们的问题变为：最佳的回归系数是多少？如何确定？

将sigmoid函数的输人记为z，由下面公式得出：
**z = θ0x0 + θ1x1 + θ2x2 + • • • + θnxn**
如果采用向量的写法，上述公式可以写成z= θTX, 它表示将这两个数值向量对应元素相乘然后全部加起来即得到z值。其中的向量x是分类器的输人数据，向量θ就是我们要找到的最佳参数(系数) , 从而使得分类器尽可能地精确。为了寻找该最佳参数，需要用到**梯度下降**。


## 梯度下降
### 1 什么是梯度下降
梯度下降的基本过程就和下山的场景很类似。

首先，我们有一个可微分的函数。这个函数就代表着一座山。我们的目标就是找到这个函数的最小值，也就是山底。根据之前的场景假设，最快的下山的方式就是找到当前位置最陡峭的方向，然后沿着此方向向下走，对应到函数中，就是找到给定点的梯度 ，然后朝着梯度相反的方向，就能让函数值下降的最快！因为梯度的方向就是函数之变化最快的方向。

我们重复利用这个方法，反复求取梯度，最后就能到达局部的最小值，这就类似于我们下山的过程。而求取梯度就确定了最陡峭的方向，也就是场景中测量方向的手段。
### 2 通俗理解
我们对一个多元函数求偏导,会得到多个偏导函数.这些导函数组成的向量,就是梯度。
当我们把梯度中的所有偏导函数都变为0的时候,就可以找到每个系数的对应最优解。
梯度下降中求偏导数的未知数不是x和y,而是x的参数**θ**
数据集中数据是固定的,结果是固定的,我们要找到的是数据中样本与结果的对应规律.所以求得θ才是我们的目的。
### 3 相关公式
#### a假设函数（hypothesis function）：
　　所谓假设函数，就是监督学习中，我们拟合样本特征映射到目标变量的函数，记为 hθ(x)，θ为函数的参数。在此次实验中我们可以表示为：
　　**hθ(x) = θ0 + θ1·x1+θ2·x2；**
#### b损失函数（loss function）：
　　
　　又称为代价函数。通常用损失函数来度量拟合的程度，从而评估模型拟合的好坏，记为 J(θ)。损失函数是关于 θ 的函数！此时θ不再是函数的参数，而是损失函数的自变量！对于线性回归的损失函数可以表示为：　　
　　***J(θ) = 1/(2 *m) * ∑ ( hθ(xi) - yi )^2****
　　其中 m表示样本数量， xi 表示第 i 个样本特征，yi 表示第 i 个样本对应的标签的真实值， hθ(xi) 为假设函数。 当我们计算损失时，是将每个样本中的特征 xi 和对应的标签真实值 yi 带入损失函数，此时，损失函数中就只剩下 θ 是未知的。 　　
　　每一个样本都会有一个拟合损失，将所有样本的损失相加，就是整个样本集的拟合损失。

#### c损失函数的梯度：
损失函数的梯度即对 θi 求偏导，由于损失函数是关于 θ 的函数，因此，θ 的取值不同，得出来的的梯度向量也是不同的。借用“下山”的比喻来解释，θ 的不同取值，相当于处于山上的不同位置，每一个位置都会计算出一个梯度向量 ▽J(θ) 。
***▽J(θ)=1/m(hθ(x) - y)*xj****
##### d推导过程

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110000614547.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)
 #### e梯度下降求解θ
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/2021011000145038.png#pic_center)
α在梯度下降算法中被称作为学习率或者步长，意味着我们可以通过α来控制每一步走的距离，α不能太大，以免错过了最低点。也不能太小，走的太慢，导致收敛过慢。

α太大的情形：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110002007445.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)
我们期待的效果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110002130899.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)
### 作业环境, 文件说明，函数说明，调用的函数库以及涉及哪些技术
环境：win10、pycharm、python3.6

语言：python、Markdown

调用的函数库：matplotlib.pyplot pandas numpy

#### 函数说明
**1 sigmoid()**
返回sigmoid函数值 

**2 draw_sigmoid():**
画sigmoid函数图，x轴的取值范围 -10, 10

**3 gradient_down（）**
迭代梯度下降求得最佳参数θ

**4 plot（）**
画样本数据拟合图 ，样本数据散点图加上分界线

**5 classify（）**
将数据代入模型，返回分类结果

### 结果
**1 数据拟合到sigmoid**
粉红色的线为，sigmoid的标准函数值
蓝色点为样本数据的拟合结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021011000375759.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)
**2样本数据的真实分布散点图及分类决策边界**
	绿色✩为（2，6）的分类结果，属于类别1![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110003947934.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NDAzMjIwOA==,size_16,color_FFFFFF,t_70#pic_center)
	![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110004255404.png#pic_center)

### 难题与解决
梯度下降算法，主要是参考以下几个博客
[1.梯度下降与随机梯度下降概念及推导过程](https://blog.csdn.net/weixin_39445556/article/details/83661219)
[2.梯度下降算法原理讲解——机器学习](https://blog.csdn.net/qq_41800366/article/details/86583789)

### 总结
本次实验的重难点在于求得假设函数h的最佳参数θ，需要使用的方法是梯度下降优化算法，需要通过参考相关资料，理解一些相关的公式并手动推导。