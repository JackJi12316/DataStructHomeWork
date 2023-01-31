# DataStructHomeWork
1.	问题描述
1.1项目题目
交通咨询系统
问题描述：设计一个交通咨询系统，用有向网表示10个城市的交通状况（飞机或动车），要求：能让旅客咨询从任一城市到另一个城市的最短路径、最短花费及最少时间等问题。
1.2问题分析
本题目主要以数据结构中的图论为出发点，通过建立所需图的邻接矩阵形式或邻接表形式将问题中的城市与路径包含其中。进而通过相关算法解决问题。
1.3数据以及算法支持
本题目的数据通过网络查询对现在的高速铁路网进行简化而获得的图1-1，以及本实验中所用到的算法支持来自《数据结构》此书。
 
图1  中国高速铁路网节选
 
2.	设计思路
2.1数据分析
将图1-1进行分析，并将图以数据形式表示。城市进行编号，路径与城市链接，赋予权值。
城市编号如下：
0:长春 1:沈阳 2:大连 3:呼和浩特 4:北京 5:天津 6:太原 7:石家庄 8:济南 9:青岛
路径（X）编号如下：
0<->1:1.0  1<->2:1.5  1<->4:3.0  1<->5:3.5  2<->5:4.0  3<->4:2.0  3<->6:4.5
4<->5:0.5  4<->7:1.0  5<->7:1.5  5<->8:1.0  6<->7:1.5  7<->8:2.0  8<->9:1.5
2.2算法分析
将城市看作为点，将城市之间的高铁线路看做边，就将整体划为图。题目要求求一座城市到另一座城市的最短距离，此问题可看做输出多源最短路径问题---Floyd算法。算法为多源算法，只能处理无向图（每边均为双向边），所以需要将数据转化为双向边来进行运算。
2.3程序设计
2.3.1 数据存储结构设计
为了实现Floyd算法，需要将已有数据存入邻接矩阵以便算法使用。由此建立结构体Point来记录单个城市的信息，建立结构体MatGraph来将各城市建立关系，以路径进行连接。
当两节点连接处的矩阵元素权值为INF（无穷）则代表两城市没有直接的高速铁路连接。
若两节点连接处的矩阵元素权值为0，则代表两节点为相同城市。
若两节点连接处的矩阵元素权值为正数，则代表两城市之间有线路且距离为权值。
 
图2  邻接矩阵存储方式说明

  通过给出的节点设计方法，将矩阵赋值。首先将矩阵全部赋予赋值INF，默认每点之间均无路径相连。之后对i=j的矩阵元素（X[i][i]）赋予0，代表相同两点之间距离为0。再把分析的数据依次赋予X[i][j]（可先只赋值单向路径，通过调换i，j进行单向表的建立）。赋值后得到实验所需矩阵X。
2.3.2 实验内容数据化
通过建立函数CreateMat(MatGraph *&m, double A[MAXV][MAXV], int n, int e)来将已有数据建立邻接矩阵，其中指针m指向所建立的图的信息。A[MAXV][MAXV]存放矩阵权值信息。n代表城市数量，e代表路径数量。函数主要作用用于对节点初始化，将已有矩阵X的值、节点个数和路径个数赋入图表指针m中。从而建立完整的邻接矩阵。之后可将城市名称通过m->p[i].city_name的方式依次赋值。
2.3.3 Floyd算法实现
根据《数据结构》课本所给出的Floyd算法进行实现分析并根据题目所需进行优化。最终实现多源最短路径的实现。
Flody算法主要为对矩阵的处理，第一部分为对算法所要利用的矩阵A（值代表路径长度）权值以及矩阵path（代表两点最短路径的中间点编号）进行初始化，初始化的结果为将连通节点的权值赋予A的对应点，不连通的点赋予INF，相同的点赋予0。将非相同且连接的两点path矩阵对应值设为路径起点的值，对于不满足条件的点设为-1（代表无中间点）。
初始化结束后对path进行进一步处理，对每个顶点k，和任一顶点对(i,j)，i!=j，k!=i，k!=j，如果A[i][j]>A[i][k]+A[k][j]，则将A[i][j]更新为A[i][k]+A[k][j]的值，并且将path[i][j]改为k。通过这套算法，将最短路径距离全部赋予矩阵A中，通过调用A的值得到最短距离。
之后通过函数Dispath对path矩阵进行筛选，将路径存储到apath数组中，从而得到最短路径。

