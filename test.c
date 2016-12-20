#define INFINITY      10000       /*无穷大*/
#define MAX_VERTEX_NUM      40
#define MAX 40

#include<stdlib.h>    //头文件
#include<stdio.h>
#include<conio.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

int visited[MAX_VERTEX_NUM];  //定义数组

typedef struct ArcCell//对弧的定义

{
    int adj;    //路径长度
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //一个二维数组,数组里元素类型为整型


typedef struct   //图中顶点表示主要景点，存放景点的编号、名称、简介等信息。
{
    char name[30];
    int num;
    char introduction[100];//简介
} infotype;   //数据域

typedef struct {
    infotype vexs[MAX_VERTEX_NUM];   //顶点的数据域
    AdjMatrix arcs;   //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
} MGraph;

MGraph b;  //全局变量

MGraph InitGraph(void);

void Menu(void);

void Browser(MGraph *G);

void ShortestPath_DIJ(MGraph *G);

void Floyd(MGraph *G);

void Search(MGraph *G);

void print(MGraph *G);

void DFSTraverse(MGraph *G);

void DFS(MGraph *G, int v);


int main() {
    system("color f2");
    system("mode con: cols=100 lines=40");
    int i;
    b = InitGraph();
    MGraph G;
    Menu();
    scanf("%d", &i);
    while (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7) {
        switch (i) {
            case 1:
                system("cls");
                Browser(&b);
                Menu();
                break;   //system("cls");作用是清屏
            case 2:
                system("cls");
                print(&b);
                Menu();
                break;
            case 3:
                system("cls");
                Search(&b);
                Menu();
                break;
            case 4:
                system("cls");
                Floyd(&b);
                Menu();
                break;
            case 5:
                system("cls");
                ShortestPath_DIJ(&b);
                Menu();
                break;
            case 6:
                system("cls");
                DFSTraverse(&b);
                break;
            case 7:
                exit(1);
                break;
            default:
                break;   //每次显示选择的一项后，会继续显示主菜单menu（）
        }

        scanf("%d", &i);   //输入的值d赋给i
    }
    return 0;
}

//DFSTraverse(&b);
MGraph InitGraph(void)//采用邻接矩阵表示法，构造无向网G
{
    MGraph G;
    int i, j;
    G.vexnum = 10;   //10个顶点
    G.arcnum = 14;   //14条弧
    for (i = 0; i < G.vexnum; i++)
        G.vexs[i].num = i;    //构造顶点向量，第i个景点的编号为i
    strcpy(G.vexs[0].name, "学校正门");   //strcpy的头文件是string.h
    strcpy(G.vexs[0].introduction, "位于学校东侧");
    strcpy(G.vexs[1].name, "文管教学楼");
    strcpy(G.vexs[1].introduction, "包含文法学院、马克思学院、管理学院，位于西门附近");
    strcpy(G.vexs[2].name, "信息教学楼");
    strcpy(G.vexs[2].introduction, "包含计算机学院、软件学院，位于东南侧");
    strcpy(G.vexs[3].name, "建筑教学楼");
    strcpy(G.vexs[3].introduction, "包含江河建筑学院，位于西南侧");
    strcpy(G.vexs[4].name, "生科教学楼");
    strcpy(G.vexs[4].introduction, "包含中荷医学工程学院、生命学院，位于东门附近");
    strcpy(G.vexs[5].name, "食堂");
    strcpy(G.vexs[5].introduction, "三层建筑，其中包括超市和浴池");
    strcpy(G.vexs[6].name, "风雨操场");
    strcpy(G.vexs[6].introduction, "体育馆，包括羽毛球、篮球、网球i等场地及众多健身器材");
    strcpy(G.vexs[7].name, "篮球场");
    strcpy(G.vexs[7].introduction, "西门附近");
    strcpy(G.vexs[8].name, "学生西侧宿舍群");
    strcpy(G.vexs[8].introduction, "包括学生一舍二舍三舍");
    strcpy(G.vexs[9].name, "学生东侧宿舍群");
    strcpy(G.vexs[9].introduction, "包括学生四舍五舍");
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
            G.arcs[i][j].adj = INFINITY;//初始化邻接矩阵//
    G.arcs[0][1].adj = 80;//弧<v,w>的权值
    G.arcs[0][2].adj = 50;
    G.arcs[1][3].adj = 40;
    G.arcs[1][4].adj = 50;
    G.arcs[2][4].adj = 30;
    G.arcs[3][5].adj = 100;
    G.arcs[4][5].adj = 120;
    G.arcs[4][8].adj = 200;
    G.arcs[5][6].adj = 140;
    G.arcs[5][7].adj = 20;
    G.arcs[6][7].adj = 50;
    G.arcs[7][8].adj = 150;
    G.arcs[7][9].adj = 240;
    G.arcs[8][9].adj = 150;
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
            G.arcs[j][i].adj = G.arcs[i][j].adj;  //置<v,w>的对称弧<w,v>，构成无向网
    return G;
}//InitGraph end


void Menu()   //定义主菜单
{


    printf("\n\n\t\t\t\t\t***校园导游系统***");

    printf("\n\t\t\t\t*************************************\n\n");

    printf("\t\t\t\t\t1. 浏览校园全景\n\n");

    printf("\t\t\t\t\t2. 显示此图的邻接矩阵\n\n");

    printf("\t\t\t\t\t3. 查看各地标信息\n\n");

    printf("\t\t\t\t\t4. 查找两地标间最短路径\n\n");

    printf("\t\t\t\t\t5. 查看各地标所有到达路线\n\n");

    printf("\t\t\t\t\t6. 遍历全部地标时间最省的路线\n\n");

    printf("\t\t\t\t\t7. 退出\n\n");

    printf("\n\t\t\t\t************************************\n\n");

    printf("选择功能:\n ");


}

void Browser(MGraph *G) {
    int v;
    printf("┏━━┳━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃编号┃地标名称        ┃简介                                                    ┃\n");
    for (v = 0; v < G->vexnum; v++)
        printf("┃%-4d┃%-16s┃%-56s┃\n", G->vexs[v].num, G->vexs[v].name, G->vexs[v].introduction);
    printf("┗━━┻━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

// 迪杰斯特拉算法来计算出起点到各个顶点之间的最短路径,v0为起点
void ShortestPath_DIJ(MGraph *G) {
    int v, w, i, min, t = 0, x, flag = 1, v0;   //flag=1保证输入编号有效
    int final[20], D[20], p[20][20];
//用迪杰斯特拉算法求网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]
//若P[v][w]为1，则w是从v0到v当前求得最短路径上的顶点
//final[v]为1当且仅当v属于s(s是已求得最短路径的终点的集合)，即已经求得从v0到v的最短路径
    while (flag) {
        printf("请输入一个起始地标编号:");
        scanf("%d", &v0);   //输入一个值赋给v0
        if (v0 < 0 || v0 > G->vexnum) {
            printf("地标编号不存在!请重新输入地标编号:");
            scanf("%d", &v0);
        }
        if (v0 >= 0 && v0 < G->vexnum)
            flag = 0;
    }
    for (v = 0; v < G->vexnum; v++) {
        final[v] = 0;  //v不属于s，即v顶点还没有走过
        D[v] = G->arcs[v0][v].adj;    //v0到v的弧权值
        for (w = 0; w < G->vexnum; w++)
            p[v][w] = 0;        //设置空路径
        if (D[v] < INFINITY) {
            p[v][v0] = 1;
            p[v][v] = 1;   //v0是从v0到v的顶点，v是从v0到v的顶点
        }
    }
    D[v0] = 0;
    final[v0] = 1;    //初始化，v0到v0的带权路径长度为0，最短路径,v0顶点属于s集
    //开始主循环，每次求得v0到某个v顶点的最短路径，并加v到s集
    for (i = 1; i < G->vexnum; i++)   //其余G.vexnum-1个顶点
    {
        min = INFINITY;   //当前所知离v0顶点的最近距离
        for (w = 0; w < G->vexnum; w++)
            if (!final[w])    //w顶点在v-s中
                if (D[w] < min) {
                    v = w;
                    min = D[w];
                }   //w顶点离v0顶点更近
        final[v] = 1;      //离v0顶点最近的v加入s集
        for (w = 0; w < G->vexnum; w++)    //更新当前的最短路径及距离
            if (!final[w] && (min + G->arcs[v][w].adj < D[w]))   //修改D[w]和P[w]，w属于v-s
            {
                D[w] = min + G->arcs[v][w].adj;
                for (x = 0; x < G->vexnum; x++)
                    p[w][x] = p[v][x];
                p[w][w] = 1;
            }
    }  //用来更新到每一个顶点的最短路径
    for (v = 0; v < G->vexnum; v++) {
        if (v0 != v) printf("%s", G->vexs[v0].name);  //输出字符串
        for (w = 0; w < G->vexnum; w++) {
            if (p[v][w] && w != v0) printf("-->%s", G->vexs[w].name);
            t++;
        }
        if (t > G->vexnum - 1 && v0 != v)printf("       总路线长%dm\n\n", D[v]);
    }
}//ShortestPath_DIJ  end


void Floyd(MGraph *G)
//用Floyd算法求图中各对顶点v和w之间的最短路径P[v][w]及其
//带权长度D[v][w]。若P[v][w][u]为1，则u是从v到w当前求得最短
//路径上的顶点。
{
    int v, u, i, w, k, j, flag = 1, p[10][10][10], D[10][10];
    for (v = 0; v < G->vexnum; v++)  //各对结点之间初始已知路径及距离
        for (w = 0; w < G->vexnum; w++) {
            D[v][w] = G->arcs[v][w].adj;
            for (u = 0; u < G->vexnum; u++)
                p[v][w][u] = 0;
            if (D[v][w] < INFINITY) {
                p[v][w][v] = 1;
                p[v][w][w] = 1;
            }
        }
    for (u = 0; u < G->vexnum; u++)
        for (v = 0; v < G->vexnum; v++)
            for (w = 0; w < G->vexnum; w++)
                if (D[v][u] + D[u][w] < D[v][w])   //从v经u到w的一条路径更短
                {
                    D[v][w] = D[v][u] + D[u][w];   //修改权值
                    for (i = 0; i < G->vexnum; i++)
                        p[v][w][i] = p[v][u][i] || p[u][w][i];
                }

    while (flag) {
        printf("请输入出发点和目的地的编号:");
        scanf("%d%d", &k, &j);
        if (k < 0 || k > G->vexnum || j < 0 || j > G->vexnum) {
            printf("地标编号不存在!请重新输入出发点和目的地的编号:");
            scanf("%d%d", &k, &j);
        }
        if (k >= 0 && k < G->vexnum && j >= 0 && j < G->vexnum)
            flag = 0;
    }
    printf("%s", G->vexs[k].name);
    for (u = 0; u < G->vexnum; u++)
        if (p[k][j][u] && k != u && j != u)
            printf("-->%s", G->vexs[u].name);
    printf("-->%s", G->vexs[j].name);
    printf(" 总路线长%dm\n", D[k][j]);
}//Floyd end


void Search(MGraph *G) {
    int k, flag = 1;
    while (flag) {
        printf("请输入要查询的地标编号:");
        scanf("%d", &k);
        if (k < 0 || k > G->vexnum) {
            printf("地标编号不存在!请重新输入景点编号:");
            scanf("%d", &k);
        }
        if (k >= 0 && k < G->vexnum)
            flag = 0;
    }
    printf("┏━━┳━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃编号┃景点名称        ┃简介                                                    ┃\n");
    printf("┃%-4d┃%-16s┃%-56s┃\n", G->vexs[k].num, G->vexs[k].name, G->vexs[k].introduction);
    printf("┗━━┻━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

}//Search end


void print(MGraph *G) {
    int v, w, t = 0;
    printf("图的邻接矩阵为：\n");
    for (v = 0; v < G->vexnum; v++)
        for (w = 0; w < G->vexnum; w++) {
            if (G->arcs[v][w].adj == INFINITY)
                printf("∞      ");
            else printf("%-7d", G->arcs[v][w].adj);
            t++;
            if (t % G->vexnum == 0)
                printf("\n");
        }
}
//int visited[MAX_VERTEX_NUM]

/*int FirstAdjVex(MGraph G,int v)
{
   int i ;
  for(i = 0; i<G.vexnum; i++)
       if( G.arcs[v][i].adj ) return i;
  if(i == (G.vexnum  -1)) return -1;
 return -1;

}*/


//邻接矩阵的深度优先递归算法
void DFS(MGraph *G, int i)   //采用邻接矩阵存储法表示的从第n个顶点出发递归地深度优先搜索无向图G
{
    visited[i] = TRUE;
    printf("This node is;%d\n", G->vexs[i]);
    int j;
    //printf("%c-->" ,G->vexs[i].name);  //打印顶点
    for (j = 0; j < G->vexnum; j++)
        //if(!visited[j]&&G->arcs[i][j]==1)
        DFS(G, j);
}


//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph *G) //对图G做深度优先遍历
{
    int i;
    for (i = 0; i < G->vexnum; i++)
        visited[i] = FALSE;  //初始化所有顶点状态都是未访问过状态
    for (i = 0; i < G->vexnum; i++)
        if (!visited[i]) //对未访问过的定点调用DFS，若是连通图，只会执行一次
            DFS(G, i);
}

