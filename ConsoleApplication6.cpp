#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <queue>
#include <stack>

int** G;
std::queue<int> Q;
std::stack<int> S;

int** gen(int size) {
	int temp = 0;
	int** arr;
	arr = new int* [size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[size] {0};

	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int k = i + 1; k < size; k++) {
			temp = rand() % 2;
			arr[i][k] = temp;
			arr[k][i] = temp;
		}
	return arr;
}

void print(int** graph, int size) {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			printf("%d  ", graph[i][k]);
		}
		printf("\n");
	}
}

void BFSD(int v, int size) {
	clock_t t1, t2;
	t1 = clock();

	int* dist = new int[size];
	for (int i = 0; i < size; i++)
		dist[i] = -1;
	dist[v] = 0;
	Q.push(v);

	while (!Q.empty()) {
		v = Q.front();
		Q.pop();

		printf("%d  ", v + 1);
		for (int i = 1; i < size; i++)
			if (G[v][i] == 1 && dist[i] == -1) {
				Q.push(i);
				dist[i] = dist[v] + 1;
			}
	}
	printf("\n\nРасстояния:  ");
	for (int i = 0; i < size; i++)
		printf("%d  ", dist[i]);
	t2 = clock();
	double seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("\nВремя: %0.3f\n\n\n", seconds);
}

void check(int i, int size, int* dist) {
	for (int k = 0; k < size; k++)
		if (G[i][k] == 1 && dist[k] != -1)
			if (dist[i] >= dist[k] + 1)
				dist[i] = dist[k] + 1;
}

void DFS(int v, int* dist, int size) {
	printf("Обход в глубину: ");
	S.push(v);
	dist[v] = 0;
	while (!S.empty()) {
		v = S.top();
		S.pop();
		printf("%d  ", v + 1);
		for (int i = size; i > 0; i--) {
			if (G[v][i] == 1 && dist[i] == -1) {
				dist[i] = dist[v] + 1;
				check(i, size, dist);
				S.push(i);
			}
		}
	}

}

void InDep(int size) {
	int v = 0;

	BFSD(v, size);

	clock_t t1, t2;
	t1 = clock();

	int* dist = new int[size];
	for (int i = 0; i < size; i++)
		dist[i] = -1;
	dist[v] = 0;

	DFS(v, dist, size);

	printf("\n\n Расстояния (в ширину):  ");
	for (int i = 0; i < size; i++)
		printf("%d  ", dist[i]);
	t2 = clock();
	double seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("\nВремя: %0.3f\n\n", seconds);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = 0;

	while (1) {
		printf("Введите кол-во вершин графа: ");
		scanf("%d", &size);
		G = gen(size);
		print(G, size);

		printf("\n\n");
		printf("Обход в ширину: ");
		InDep(size);
		printf("\n\n");

		system("pause");
		system("cls");
	}
	return 0;
}
