#include <stdio.h>
#define I 999999 // INF
#define N 13

void dijkstra(int graph[N][N], int start) {
    int dist[N];
    int visited[N] = { 0 };
    int i, j;
    for (i = 0; i < N; i++)
        dist[i] = I;
    dist[start] = 0;
    for (i = 0; i < N; i++) {
        int minDist = I;
        int minIndex;
        for (j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1;
        for (j = 0; j < N; j++) {
            if (!visited[j] && graph[minIndex][j] && dist[minIndex] + graph[minIndex][j] < dist[j]) {
                dist[j] = dist[minIndex] + graph[minIndex][j];
            }
        }
    }
    printf("Vertex\t\tDistance from Source\n");
    for (i = 0; i < N; i++) {
        printf("%d\t\t%d\n", i, dist[i]);
    }
}

int main() {
    // 580门，五教，光电楼，图书馆，计算中心，三公寓，五食堂，毛像，一教，516门，334门，操场，思餐厅
    int graph[N][N] = {
        {0, 2, 6, I, I, I, I, I, I, 1, I, I, I}, // 580门
        {2, 0, 5, I, I, I, I, I, I, I, I, I, I}, // 五教
        {6, 5, 0, 3, 3, 4, I, 5, I, I, I, I, I}, // 光电楼
        {I, I, 3, 0, 1, 2, I, I, I, I, I, I, I}, // 图书馆
        {I, I, 3, 1, 0, 2, I, I, I, I, I, I, I}, // 计算中心
        {I, I, 4, 2, 2, 0, 1, 5, I, I, I, I, I}, // 三公寓
        {I, I, I, I, I, 1, 0, I, I, I, I, I, I}, // 五食堂
        {I, I, 5, I, I, 5, I, 0, 2, I, I, 8, 8}, // 毛像
        {I, I, I, I, I, I, I, 2, 0, 5, I, I, I}, // 一教
        {1, I, I, I, I, I, I, I, 5, 0, 4, I, I}, // 516门
        {I, I, I, I, I, I, I, I, I, 4, 0, 4, 4}, // 334门
        {I, I, I, I, I, I, I, 8, I, I, 4, 0, 1}, // 操场
        {I, I, I, I, I, I, I, 8, I, I, 4, 1, 0}  // 思餐厅
    };
    char* names[N] = { "580门", "五教", "光电楼", "图书馆", "计算中心", "三公寓", "五食堂", "毛像", "一教", "516门", "334门", "操场", "思餐厅" };
    dijkstra(graph, 0);
    return 0;
}