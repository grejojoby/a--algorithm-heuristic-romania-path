//Grejo Joby    Roll no 17  BE Comps

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#define VERTEX 13
using namespace std;

struct Node {
	int id;
	Node *parent;
	Node() :
		id(-1), parent(NULL) {}
	Node(int id) :
		id(id), parent(NULL) {}
	Node(int id, Node *parent) :
		id(id), parent(parent) {}
};

struct AdjacencyMatrix {
	string vertex[VERTEX];
	int edges[VERTEX][VERTEX];
	int direct[VERTEX];

	Node openlist[VERTEX];
	Node closelist[VERTEX];
	int fvalue[VERTEX];

	int isTraversed[VERTEX] = { 0 };
	vector<int> path;
};
class Solution {
public:
	void createGraph(AdjacencyMatrix &graph) {
		//							  00  01  02  03  04  05  06  07  08  09  10  11  12
		int map[VERTEX][VERTEX] = { {  0, 75, -1,118, -1, -1, -1,140, -1, -1, -1, -1, -1 },//0
									{ -1,  0, 71, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },//1
									{ -1, -1,  0, -1, -1, -1, -1,151, -1, -1, -1, -1, -1 },//2
									{ -1, -1, -1,  0,111, -1, -1, -1, -1, -1, -1, -1, -1 },//3
									{ -1, -1, -1, -1,  0, 70, -1, -1, -1, -1, -1, -1, -1 },//4
									{ -1, -1, -1, -1, -1,  0, 75, -1, -1, -1, -1, -1, -1 },//5
									{ -1, -1, -1, -1, -1, -1,  0, -1, -1,120, -1, -1, -1 },//6
									{ -1, -1, -1, -1, -1, -1, -1,  0, 80, -1, 99, -1, -1 },//7
									{ -1, -1, -1, -1, -1, -1, -1, -1,  0,146, -1, 97, -1 },//8
									{ -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1,138, -1 },//9
									{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1,211 },//10
									{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,101 },//11
									{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0 } //12
		};
		for (int i = 0; i < VERTEX; i++)
			for (int j = 0; j < VERTEX; j++)
				if (map[i][j] != -1)
					map[j][i] = map[i][j];
		memcpy(graph.edges, map, sizeof(map));
		graph.vertex[0] = "Arad"; graph.direct[0] = 366;
		graph.vertex[1] = "Zerind"; graph.direct[1] = 374;
		graph.vertex[2] = "Oradea"; graph.direct[2] = 380;
		graph.vertex[3] = "Timisoara"; graph.direct[3] = 329;
		graph.vertex[4] = "Lugoj"; graph.direct[4] = 244;
		graph.vertex[5] = "Mehadia"; graph.direct[5] = 241;
		graph.vertex[6] = "Drobeta"; graph.direct[6] = 242;
		graph.vertex[7] = "Sibiu"; graph.direct[7] = 253;
		graph.vertex[8] = "Rimnicu-Vilcea"; graph.direct[8] = 193;
		graph.vertex[9] = "Craiova"; graph.direct[9] = 160;
		graph.vertex[10] = "Fagaras"; graph.direct[10] = 176;
		graph.vertex[11] = "Pitesti"; graph.direct[11] = 100;
		graph.vertex[12] = "Bucharest"; graph.direct[12] = 0;
	}
	// void outputGraph(AdjacencyMatrix &graph) {
	// 	for (int i = 0; i < VERTEX; i++)
	// 		for (int j = 0; j < VERTEX; j++)
	// 			if (graph.edges[i][j] > 0)
	// 				// cout << graph.vertex[i] << " -> " << graph.vertex[j] << " : " << graph.edges[i][j] << endl;
	// }
	inline int computeF(AdjacencyMatrix graph, Node node) {
		if (node.parent == NULL)
			return graph.direct[node.id];
		return graph.edges[node.parent->id][node.id] + graph.direct[node.id];
	}
	Node minimumF(AdjacencyMatrix graph) {
		int Fmin = 99999999;
		int Findex = 0;
		int F;//F = G + H, G is cost, H is estimated value.
		for (int index = 1; index < VERTEX; index++)
			if (graph.openlist[index].id != -1 && graph.closelist[index].id == -1
					&& (F = graph.fvalue[index]) < Fmin) {
				Fmin = F;
				Findex = index;
			}
		return graph.openlist[Findex];
	}
	int nextOutdegree(AdjacencyMatrix graph, int interrupt, int loc) {
		for (int index = interrupt + 1; index < VERTEX; index++) {
			if (graph.edges[loc][index] > 0 && graph.isTraversed[index] == 0)
				return index;
		}
		return -1;
	}
	bool extendOpenList(AdjacencyMatrix &graph, int id) {
		graph.closelist[id] = graph.openlist[id];
		int current = 0;
		if (id == VERTEX - 1)
			return false;
		while ((current = nextOutdegree(graph, current, id)) != -1) {
			graph.openlist[current].id = current;
			graph.openlist[current].parent = &graph.closelist[id];
			graph.isTraversed[current] = 1;
			graph.fvalue[current] = computeF(graph, graph.openlist[current]);
		}
		return true;
	}
	void AstarSearch(AdjacencyMatrix &graph, int start, int end) {
		Node root = { start, NULL };
		graph.openlist[start] = root;
		graph.isTraversed[start] = 1;
		graph.fvalue[start] = computeF(graph, root);
		while (extendOpenList(graph, root.id)) {
			cout << root.id << "   ";
			root = minimumF(graph);
		}
		root = graph.closelist[end];
		cout << root.id << endl;
		Node *p = &root;
		while (p != NULL) {
			 graph.path.push_back(p->id);//Reverse
			p = p->parent;
		}
	}
};
int main(int argc, char *argv[]) {
	int start = 0, end = 12;
	AdjacencyMatrix graph;
	Solution sol;
	sol.createGraph(graph);
	// sol.outputGraph(graph);
	sol.AstarSearch(graph, start, end);
    float sum = 0;
	cout << endl << "So, path: ";
	for (int cur = graph.path.size() - 1; cur > 0; cur--)
		{
            cout << graph.vertex[graph.path[cur]] << " -> ";
            sum += graph.edges[graph.path[cur]][graph.path[cur-1]];
        }
	cout << graph.vertex[graph.path[0]] << endl;
    cout << "Total Cost: "<< sum <<endl;
	vector<int>().swap(graph.path);
	system("pause");
	return 0;
}