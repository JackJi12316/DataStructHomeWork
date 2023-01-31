
#include "path_build.h"


/*6.11 交通咨询系统
问题描述：设计一个交通咨询系统，用有向网表示10个城市的交通状况（飞机或动车），要求：能让旅客咨询从任一城市到另一个城市的最短路径、最短花费及最少时间等问题。
 * 0:长春
 * 1:沈阳
 * 2:大连
 * 3:呼和浩特
 * 4:北京
 * 5:天津
 * 6:太原
 * 7:石家庄
 * 8:济南
 * 9:青岛
 * 0->1:1
 * 1->2:1.5
 * 1->4:3
 * 1->5:3.5
 * 2->5:4
 * 3->4:2
 * 3->6:4.5
 * 4->5:0.5
 * 4->7:1
 * 5->7:1.5
 * 5->8:1
 * 6->7:1.5
 * 7->8:2
 * 8->9:1.5
 */


int main() {
    MatGraph *m;
    m = (MatGraph *) malloc(sizeof(MatGraph));
    int i, j;
    int start;
    int final;
    double X[MAXV][MAXV];

    //数据模块
    //初始化数据
    for (i = 0; i < MAXV; i++)
        for (j = 0; j < MAXV; j++) {
            X[i][j] = INF;
        }
    for (i = 0; i < MAXV; i++) {
        X[i][i] = 0;
    }

    //已知数据输入
    X[0][1] = 1;
    X[1][2] = 1.5;
    X[1][4] = 3;
    X[1][5] = 3.5;
    X[2][5] = 4;
    X[3][4] = 2;
    X[3][6] = 4.5;
    X[4][5] = 0.5;
    X[4][7] = 1;
    X[5][7] = 1.5;
    X[5][8] = 1;
    X[6][7] = 1.5;
    X[7][8] = 2;
    X[8][9] = 1.5;

    //城市名称赋值
    m->p[0].city_name = "长春";
    m->p[1].city_name = "沈阳";
    m->p[2].city_name = "大连";
    m->p[3].city_name = "呼和浩特";
    m->p[4].city_name = "北京";
    m->p[5].city_name = "天津";
    m->p[6].city_name = "太原";
    m->p[7].city_name = "石家庄";
    m->p[8].city_name = "济南";
    m->p[9].city_name = "青岛";

    //无向图转换为有向图
    for (i = 0; i < MAXV; i++)
        for (j = 0; j < MAXV; j++)
            if (X[i][j] != 0 && X[i][j] != INF) {
                X[j][i] = X[i][j];
            }

    //建立图
    CreateMat(m, X, MAXV, 14);

    //页面建立
    printf("\t***********************始发站站点表***********************\n");
    printf("\t说明:以高铁(G)为例,每公里价格约为0.74元,城市间的距离为估算,以平均时速250km/h计算\n\n");
    printf("0 for 长春\t1 for 沈阳\t2 for 大连\t3 for 呼和浩特  4 for 北京\n");
    printf("5 for 天津\t6 for 太原\t7 for 石家庄    8 for 济南\t9 for 青岛\n");
    printf("请选择始发站:");
    scanf("%d", &start);
    printf("\n请选择终点站:");
    scanf("%d", &final);

    //Floyd算法使用
    Floyd_Mat(m, start, final);

    /*//Test模块--测试矩阵的建立
    DispMatG(m);
*/
}
