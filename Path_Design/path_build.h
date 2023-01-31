//
// Created by Jack Ji on 2021/10/4.
//

#ifndef PATH_DESGIN_PATH_BUILD_H
#define PATH_DESGIN_PATH_BUILD_H

#endif //PATH_DESGIN_PATH_BUILD_H

#include "malloc.h"
#include <stdio.h>
#include "string"

#define MAXV 10
#define INF 32767

//建立点的相关信息
struct Point {
    int no;//城市序号
    const char *city_name;//城市名称
};
//建立邻接矩阵结构
struct MatGraph {
    double edges[MAXV][MAXV];
    int n, e;
    Point p[MAXV];
};

//建立完备邻接矩阵
void CreateMat(MatGraph *&m, double A[MAXV][MAXV], int n, int e) {
    int i, j;
    for (i = 0; i < MAXV; i++) {
        m->p[i].no = i;
    }
    for (i = 0; i < MAXV; i++)
        for (j = 0; j < MAXV; j++)
            m->edges[i][j] = A[i][j];
    m->n = n;
    m->e = e;
}

//输出邻接矩阵
void DispMatG(MatGraph *m) {
    int i, j;
    for (i = 0; i < MAXV; i++)
        for (j = 0; j < MAXV; j++) {
            if (m->edges[i][j] != INF && m->edges[i][j] != 0) {
                printf("%6s-->%6s:%3.1f\n", m->p[i].city_name, m->p[j].city_name, m->edges[i][j]);
            }
        }
}


//进行路径计算，q->起点,z->终点--Floyd算法
void Dispath(MatGraph *g, double A[][MAXV], int path[][MAXV], int q, int z) {
    int i, j, k, s;
    i=q;j=z;
    int apath[MAXV], d;
    if (A[i][j] != INF && i != j) {
        printf("从%5s到%5s的路径为:", g->p[i].city_name, g->p[j].city_name);
        k = path[i][j];
        d = 0;
        apath[d] = j;
        while (k != -1 && k != i) {
            d++;
            apath[d] = k;
            k = path[i][k];
        }
        d++;
        apath[d] = i;
        printf("%5s", g->p[apath[d]].city_name);
        for (s = d - 1; s >= 0; s--) {
            printf(",%5s", g->p[apath[s]].city_name);
        }
        printf("\n\t路径长度为:%3.1f千米\n", A[i][j]*100.0);
        printf("\t花销为:%4.2f元\n",A[i][j]*100.0*0.74);
        printf("\t所需时间为为:%3.2f小时\n", A[i][j]/2.5);
    }
}
void Floyd_Mat(MatGraph *g, int q, int z) {
    double A[MAXV][MAXV];
    int path[MAXV][MAXV];
    int i, j, k;
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->edges[i][j];
            if (i != j && g->edges[i][j] < INF)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }

    }
    Dispath(g, A, path, q, z);
}
