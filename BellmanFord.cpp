#include <iostream>
#include <list>
#include <vector>
#define INF 2000000002
#define DEBUG

typedef std::vector<std::list<std::pair<int, int> > >::iterator vIterator;
typedef std::list<std::pair<int, int> >::iterator lIterator;

std::vector<std::list<std::pair<int, int> > > graph;
std::vector<int> distance;
std::vector<int> predecessor;

void initialize(int);
void insertNode(int, int, int);
void visit();
void bellmanFordAlgorithm();
int main() {
	int u, v, cost, vNum, eNum;

	while (std::cin >> vNum >> eNum) {
		// init
		initialize(vNum);

		// get input
		for (int k = 0; k < eNum; k++) {
			std::cin >> u >> v >> cost;
			insertNode(u, v, cost);
		}

		#ifdef DEBUG
		visit();
		#endif

		// find shortest paths
		bellmanFordAlgorithm();
	}

	return 0;
}

void initialize(int vNum) {
	graph.clear();
	graph.resize(vNum);

	distance.clear();
	for (int k = 0; k < vNum; k++)
		distance.push_back(INF);
	distance[0] = 0;

	predecessor.clear();
	for (int k = 0; k < vNum; k++)
		predecessor.push_back(-1);

	return;
}

void insertNode(int u, int v, int cost) {
	bool found = false;

	for (lIterator it = graph[u].begin(); it != graph[u].end(); it++) {
		if (it->first == v) {
			if (cost < it->second)
				it->second = cost;
			found = true;

			break;
		}
	}

	if (!found)
		graph[u].push_back(std::pair<int, int>(v, cost));

	return;
}

void visit() {
	int k = 0;

	for (vIterator itv = graph.begin(); itv != graph.end(); itv++, k++) {
		printf("%3d|", k);

		for (lIterator itl = itv->begin(); itl != itv->end(); itl++)
			printf(" -> (%d, %d)", itl->first, itl->second);
		puts("");
	}

	return;
}

void bellmanFordAlgorithm() {
	int to, cost;

	// (|V| - 1) times iterations
	for (int k = 1; k < graph.size(); k++) {

		for (int from = 0; from < graph.size(); from++) {
			for (lIterator itl = graph[from].begin(); itl != graph[from].end(); itl++) {
				to = itl->first;
				cost = itl->second;

				if (distance[from] + cost < distance[to]) {
					distance[to] = distance[from] + cost;
					predecessor[to] = from;
				}
			}
		}
	}

	#ifdef DEBUG
	std::cout << "\nDistance:\n      Index|";
	for (int k = 0; k < distance.size(); k++)
		printf("%3d ", k);
	std::cout << "\n   Distance|";
	for (int k = 0; k < distance.size(); k++)
		printf("%3d ", distance[k]);
	std::cout << "\n\nPredecessor:\n      Index|";
	for (int k = 0; k < predecessor.size(); k++)
		printf("%3d ", k);
	std::cout << "\nPredecessor|";
	for (int k = 0; k < predecessor.size(); k++)
		printf("%3d ", predecessor[k]);
	#endif

	return;
}