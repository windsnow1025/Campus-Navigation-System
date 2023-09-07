#include <stdio.h>
#include <stdlib.h>
#define I 999999 // INF
#define R 21 // Routes
#define N 13 // Nodes

#pragma warning(disable : 4996)

void printPath(int prev[], int i, char* names[]) {
    if (i == -1) {
        return;
    }
    printPath(prev, prev[i], names);
    if (prev[i] != -1) {
		printf(" -> ");
	}
    printf("%s", names[i]);
}

void printDepartments(char* names[N]) {
    printf("部门:\n");
    for (int i = 0; i < N; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
}

void routeToGraph(int route[R][3], int graph[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            graph[i][j] = I;
        }
    }
    for (i = 0; i < R; i++) {
        int u = route[i][0];
        int v = route[i][1];
        int w = route[i][2];
        graph[u][v] = w;
        graph[v][u] = w;
    }
}

void dijkstra(int graph[N][N], int start, char* names[N]) {
    int dist[N];
    int prev[N];
    int visited[N] = { 0 };
    int i, j;
    for (i = 0; i < N; i++) {
        dist[i] = I;
        prev[i] = -1;
    }
    dist[start] = 0;
    for (i = 0; i < N; i++) {
        int minDist = I;
        int minIndex;
        // Find the vertex with the minimum distance
        for (j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1;
        // Update the distance of the adjacent vertices
        for (j = 0; j < N; j++) {
            if (!visited[j] && graph[minIndex][j] && dist[minIndex] + graph[minIndex][j] < dist[j]) {
                dist[j] = dist[minIndex] + graph[minIndex][j];
                prev[j] = minIndex;
            }
        }
    }
    printf("%-24s\t距离\t\t路径\n", "顶点");
    for (i = 0; i < N; i++) {
        printf("%-24s\t%d\t\t", names[i], dist[i]);
        printPath(prev, i, names);
        printf("\n");
    }
}

int main() {
    int route[R][3] = {
        {0, 1, 2},
        {0, 2, 6},
        {0, 9, 1},
        {1, 2, 5},
        {2, 3, 3},
        {2, 4, 3},
        {2, 5, 4},
        {2, 7, 5},
        {3, 4, 1},
        {3, 5, 2},
        {4, 5, 2},
        {5, 6, 1},
        {5, 7, 5},
        {7, 8, 2},
        {7, 11, 8},
        {7, 12, 8},
        {8, 9, 5},
        {9, 10, 4},
        {10, 11, 4},
        {10, 12, 4},
        {11, 12, 1}
    };
    // int graph[N][N] = {
    //     {0, 2, 6, I, I, I, I, I, I, 1, I, I, I},
    //     {2, 0, 5, I, I, I, I, I, I, I, I, I, I},
    //     {6, 5, 0, 3, 3, 4, I, 5, I, I, I, I, I},
    //     {I, I, 3, 0, 1, 2, I, I, I, I, I, I, I},
    //     {I, I, 3, 1, 0, 2, I, I, I, I, I, I, I},
    //     {I, I, 4, 2, 2, 0, 1, 5, I, I, I, I, I},
    //     {I, I, I, I, I, 1, 0, I, I, I, I, I, I},
    //     {I, I, 5, I, I, 5, I, 0, 2, I, I, 8, 8},
    //     {I, I, I, I, I, I, I, 2, 0, 5, I, I, I},
    //     {1, I, I, I, I, I, I, I, 5, 0, 4, I, I},
    //     {I, I, I, I, I, I, I, I, I, 4, 0, 4, 4},
    //     {I, I, I, I, I, I, I, 8, I, I, 4, 0, 1},
    //     {I, I, I, I, I, I, I, 8, I, I, 4, 1, 0}
    // };
    int graph[N][N];
    routeToGraph(route, graph);
    char* names[N] = { "580门", "五教", "光电楼", "图书馆", "计算中心", "三公寓", "五食堂", "毛像", "一教", "516门", "334门", "操场", "思餐厅" };

    int choice;
    while (1) {
        system("cls");
        printf("菜单:\n1. 查询部门信息\n2. 获取校门到各部门的最佳路线\n3. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch (choice) {
        case 1:
            printDepartments(names);
            break;
        case 2:
            printf("1. 580门, 2. 516门, 3. 334门\n选择校门: ");
            int gate;
            scanf("%d", &gate);
            while ((getchar()) != '\n');
            switch (gate) {
            case 1:
                dijkstra(graph, 0, names); // 580 Gate
                break;
            case 2:
                dijkstra(graph, 9, names); // 516 Gate
                break;
            case 3:
                dijkstra(graph, 10, names); // 334 Gate
                break;
            default:
                printf("无效的选择. 请重新输入.\n");
            }
            break;
        case 3:
            return 0;
        default:
            printf("无效的选择. 请重新输入.\n");
        }
        system("pause");
    }
    return 0;
}