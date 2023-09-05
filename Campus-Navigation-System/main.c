#include <stdio.h>
#define I 999999 // INF
#define N 13

#pragma warning(disable : 4996)

void printPath(int prev[], int i, char* names[]) {
    if (i == -1) {
        return;
    }
    printPath(prev, prev[i], names);
    printf("%s", names[i]);
    if (i != -1) {
        printf(" -> ");
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
                prev[j] = minIndex;
            }
        }
    }
    printf("%-24s\tDistance\t\tPath\n", "Vertex");
    for (i = 0; i < N; i++) {
        printf("%-24s\t%d\t\t", names[i], dist[i]);
        printPath(prev, i, names);
        printf("\n");
    }
}

void printDepartments(char* names[N]) {
    printf("Departments:\n");
    for (int i = 0; i < N; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
}

int main() {
    int graph[N][N] = {
        {0, 2, 6, I, I, I, I, I, I, 1, I, I, I},
        {2, 0, 5, I, I, I, I, I, I, I, I, I, I},
        {6, 5, 0, 3, 3, 4, I, 5, I, I, I, I, I},
        {I, I, 3, 0, 1, 2, I, I, I, I, I, I, I},
        {I, I, 3, 1, 0, 2, I, I, I, I, I, I, I},
        {I, I, 4, 2, 2, 0, 1, 5, I, I, I, I, I},
        {I, I, I, I, I, 1, 0, I, I, I, I, I, I},
        {I, I, 5, I, I, 5, I, 0, 2, I, I, 8, 8},
        {I, I, I, I, I, I, I, 2, 0, 5, I, I, I},
        {1, I, I, I, I, I, I, I, 5, 0, 4, I, I},
        {I, I, I, I, I, I, I, I, I, 4, 0, 4, 4},
        {I, I, I, I, I, I, I, 8, I, I, 4, 0, 1},
        {I, I, I, I, I, I, I, 8, I, I, 4, 1, 0}
    };
    char* names[N] = { "580 Gate", "Building 5", "Optoelectronics Building", "Library", "Computing Center", "Dormitory 3", "Cafeteria 5", "Mao Statue", "Building 1", "516 Gate", "334 Gate", "Playground", "Si Cafeteria" };

    int choice;
    while (1) {
        system("cls");
        printf("Menu:\n1. Query department information\n2. Get the best route from the school gate to each department\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printDepartments(names);
            break;
        case 2:
            printf("Choose the gate:\n1. 580 Gate\n2. 516 Gate\n3. 334 Gate\n");
            int gate;
            scanf("%d", &gate);
            switch (gate) {
            case 1:
                dijkstra(graph, 0, names); // 580 Gate is at index 0
                break;
            case 2:
                dijkstra(graph, 9, names); // 516 Gate is at index 9
                break;
            case 3:
                dijkstra(graph, 10, names); // 334 Gate is at index 10
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
        system("pause");
    }
    return 0;
}