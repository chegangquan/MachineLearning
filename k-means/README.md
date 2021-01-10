#  实验三    《k-means聚类算法》
## 组员信息
组长：陈港泉

组员：黎家豪

分工：

陈港泉：实现中心点随机、计算不同k值的wss值

黎家豪：实现数据的读取和结果的保存、k-means、对聚类结果进行画图
## 作业题目和内容
题目
用C++实现k-means聚类算法，
1. 对实验二中的z-score归一化的成绩数据进行测试，观察聚类为2类，3类，4类，5类的结果，观察得出什么结论？
2. 由老师给出测试数据，进行测试，并画出可视化出散点图，类中心，类半径，并分析聚为几类合适。
样例数据(x,y)数据对：

    | x| y |
    | ------ | ------ |
    |3.45|7.08|
    |1.76|7.24|
    |4.29|9.55|
    |3.35|6.65|
    |3.17|6.41|
    |3.68|5.99|
    |2.11|4.08|
    |2.58|7.10|
    |3.45|7.88|
    |6.17|5.40|
    |4.20|6.46|
    |5.87|3.87|
    |5.47|2.21|
    |5.97|3.62|
    |6.24|3.06|
    |6.89|2.41|
    |5.38|2.32|
    |5.13|2.73|
    |7.26|4.19|
    |6.32|3.62|

找到聚类中心后，判断(2,6)是属于哪一类？

注意
除文件读取外，不能使用C++基础库以外的API和库函数。

## 作业环境：
环境：win10、vs 2019、pycharam（画图用）

语言：C++、python（画图用）、Markdown
## 文件说明：
**代码文件：**

k-means.cpp

k-means_paint.py

**student_score：学生成绩的聚类结果和图片**

* 数据文件
    * score.txt 学生标准化后的成绩
    * k_max=5 wss_score.csv  
    wss数据文件（k_max=5意思是k∈[1,5]）
    * k='x' targets_score.csv  
    聚类后的类标签文件 （k='x' ）
    * k='x' center_score.csv  
    聚类后的中心点坐标文件（k='x' ）
* 图片文件
    * k_max=5 wss.jpg  
    wss函数图


**teacher_data：老师数据的聚类结果和图片**

* 数据文件
    * data.txt 老师给出的二维数据
    * k_max=5 wss_data.csv  
    wss数据文件（k_max=5意思是k∈[1,5]）
    * k='x' targets_data.csv  
    聚类后的类标签文件 （k='x' ）
    * k='x' center_data.csv  
    聚类后的中心点坐标文件（k='x' ）
* 图片文件
    * k_max=5 wss.jpg  （wss函数图，当分为两类的时候，出现拐点，分为两类合适）
    * k='x' scatter.jpg  
    聚类后的类半径图（k='x'）



## 函数说明：

* 文件读取操作：  
    * **实现原理**：因为要读取的文件结构都属于n×m矩阵，所以我想用动态建立的n×m二维数组来储存文件数据。在读取文件的时候，用ifstream打开文件，再用getline将文件按行读取。因为getline读取出来的是一整行的字符串（例如："-0.69593,2.23804,-0.17959,0.21087,0.483,-1.18424,-0.48462,-1.46881,0.44906,-1.18424,-0.43389"），所以需要对读取出来的字符串再进行**字符串分割**和**字符串转浮点数**这两个操作。最后将分割出来的数据存到二维数组里。  
    * **主要函数**：  
    ① 读取double型数据的函数readfile_double2d()、  
    ② 读取int型数据的函数readfile_int_1d()

* 执行k-means算法:  
    * **实现原理**：  
    ① 先根据从文件读取出来的数据随机生成k个中心。  
    ② 进入循环：  
    根据中心点计算每个数据的类别。  
    根据刚刚的类别计算新的中心点。  
    判断新中心点与旧中心点是否相同，如果不一样继续进行循环，否则跳出循环。  
    ③将结果保存到csv文件里  
    * **主要函数**：  
    ① kmeans()  
    ② 随机中心点函数：srand_centre()  
    ③ 根据中心点计算类别函数：calculate_target()  
    ④ 保存结果函数：save_targets_center()  
    ⑤ 计算距离函数：distance()
* 计算wss：  
    * **实现原理**：输入k_max值，根据k_max值，将k=1到k=k_max进行迭代，算出每个k值的wss值。wss值就是将每个簇的质点与簇内样本点的平方距离误差和。最后将结果保存到csv文件里。  
    * **主要函数**：  
    wss()
* 画图：  
    * **实现原理**：使用python里的matplotlib库画出每个类的散点图，和wss的折线图。画类半径的时候，将类中心与距离类中心最远点的距离作为半径，然后根据类中心和半径画圆弧。  
    * **主要函数**：  
    plt.scatter()  
    plt.plot()

## 问题回答：
* 对实验二中的z-score归一化的成绩数据进行测试，观察聚类为2类，3类，4类，5类的结果，观察得出什么结论？    
    k-means的k值如何确定？  
    使用elbow method，x轴为聚类的数量，y轴为WSS（within cluster sum of squares）也就是各个点到cluster中心的距离的平方的和。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110122151231.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)
    
根据wss图就可以判断，聚为2类的时候就出现了较大的拐点，所以聚为2类比较合适。
* 由老师给出测试数据，进行测试，并画出可视化出散点图，类中心，类半径，并分析聚为几类合适。  
    ① k=1

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110121903548.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)

② k=2

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110121955540.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)

③ k=3

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110122019626.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)

④ k=4

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110122046121.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)

⑤ k=5

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110122104770.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)  

![当分为两类的时候，出现拐点，分为两类合适](https://img-blog.csdnimg.cn/20210110121622496.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3MjA1OQ==,size_16,color_FFFFFF,t_70)

根据散点图和wss图的拐点可以看出，聚为两类比较合适。点（2，6）使用⭐号进行表示，当k=2时，（2，6）属于中心点为（3.17,6.81）的那类。


## 总结
通过这次实验，学会了使用c++语言实验k-means算法，对k-means算法有了更加深刻的理解。在判断k-means的k值选择时，学会了使用elbow method进行寻找较合适的k值进行聚类。聚类完后，也学会了如何使用matplotlib展示聚类结果，画类半径。

