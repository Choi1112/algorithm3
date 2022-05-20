#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 5
#define INF 9999 //INFINITY

// edge 구조체 
typedef struct Edge {
	int weight;
	int v1; 
	int v2;
}edge;

int f_index = -1; // 인덱스 값 초기화

// dijkstra 알고리즘
void dijkstraAlg(int n, int(*W)[N + 1], edge* F) {
	int vnear; // 새로 추가된 vertex의 인덱스 값 
	edge e; // edge 구조체 
	int i, j;
	int touch[N + 1], length[N + 1]; 
	// touch[i] 시작점에서 특정 노드까지의 경로상에 놓인 노드중 가장 마지막에 touch한 노드의 인덱스
	// length[i] 출발점과 특정 노드까지의 가중치들의 합, 거리

	for (i = 2;i <= n;i++) {	// tocuh, length 초기화 (시작점 v1으로 설정)
		touch[i] = 1; // touch 초기화
		length[i] = W[1][i]; // v1부터 다른 노드들까지의 가중치 
	}

	while (1) {
		int minLen = INF; // 큰 값으로 초기화
		for (i = 2; i <= n;i++) { // 방문하지 않은 정점들 중에 시작점과 가장 가까운 정점의 인덱스 구한다.
			if (0 <= length[i] && length[i] <= minLen) {
				minLen = length[i]; // 시작점에서 정점까지의 거리 업데이트
				vnear = i;
			}
		}

		e.v1 = touch[vnear]; // 가장 가까운 정점에 도달하기 직전에 touch한 인덱스 predecessor
		e.v2 = vnear;	// 가장 가까운 정점 

		F[++f_index] = e; // edge, F 집합/배열에 추가 

		for (i = 2; i <= n;i++) {
			if (length[vnear] + W[vnear][i] < length[i]) {
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;
		
		if (f_index == n - 1) break; // while문 종료 조건 출발점 제외 n-1개의 정점이 있으므로 n-1번 수행 후 종료
	}

}

void main() {	
	// 그래프의 인접행렬 그래프 1
	//int W[N + 1][N + 1] = { {0,0,0,0,0,0 },
	//						{0,0,2,5,INF,3},
	//						{0,INF,0,INF,4,10},
	//						{0,INF,INF,0,6,2},
	//						{0,INF,INF,INF,0,INF},
	//						{0,INF,INF,1,2,0} };

	// 그래프의 인접행렬 그래프 2
	//int W[N + 1][N + 1] = { {0,0,0,0,0,0 },
	//					{0,0,1,INF,1,5},
	//					{0,9,0,3,2,INF},
	//					{0,INF,INF,0,4,INF},
	//					{0,INF,INF,2,0,3},
	//					{0,3,INF,INF,INF,0} };

	// 그래프의 인접행렬 그래프 3
	int W[N + 1][N + 1] = { {0,0,0,0,0,0 },
					{0,0,3,5,1,12},
					{0,3,0,3,1,8},
					{0,5,3,0,2,INF},
					{0,1,1,2,0,7},
					{0,12,8,INF,7,0} };
	edge F[N]; // edge 집합

	dijkstraAlg(N, W, F);


	// v1 노드로부터 각각의 나머지 노드들까지의 최소 path 출력
	printf("Shortest path(from v1)\n");
	for (int i = 0;i < f_index;i++) {
		for (int j = 0; j < i; j++) {
			if (F[j].v2 == F[i].v1) {
				printf("v%d --- ", F[j].v1);
			}
		}
		printf("v%d --- v%d ", F[i].v1, F[i].v2);
		printf("\n");
	}
}
