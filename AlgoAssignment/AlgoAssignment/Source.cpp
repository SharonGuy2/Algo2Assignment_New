#include <iostream>
#include <time.h>
#include <stdlib.h> 
//#include <algorithm>
using namespace std;
#include <vector>
#include <list>
#include <fstream>
double pThresh1[10] = { 0.0048,0.0053,0.0059,0.0065,0.0069,0.0072,0.008,0.009,0.01,0.01401 };	//for 1000 vertices
double pThresh2[10] = { 0.091,0.1,0.103,0.115,0.1175,0.12,0.125,0.13,0.135,0.14 };	 //for 1000 vertices
void printCSV(int option, double* connectedArr, double* isolatedArr, double* diameterArr);
void calcFunc(int option, int ver, int amount);



class Graph {
	int vertices;
	vector<vector<int>> myGraph;
public:
	Graph(int ver) {
		myGraph.resize(ver);
		this->vertices = ver;
	}

	Graph() {
		myGraph.resize(1000);
	}

	~Graph() {
		myGraph.clear();
		//need to delete the graphs (delete the "New"!)
	}

	void graph_random_build(double prob);
	void addEdge(int v, int w);
	bool isIsolated(Graph& graph);
	int diameter(Graph& graph);
	bool BFS(int s, int numOfV,int* distances);
	bool connectGraph(int numOfV);
	int getVertices() { return this->vertices; }
	void setVer(int ver) { this->vertices = ver; }
	void clearGraph() {
		for (int i = 0; i < this->vertices; i++)
			myGraph[i].clear();
	}
};

void Graph::graph_random_build(double prob) {
	int randomNum;
	double randNum;
	for (int i = 0; i < this->vertices; i++)
		for (int j = i; j < this->vertices; j++) {
			randomNum = rand() % RAND_MAX + 1;
			randNum = (double)randomNum / RAND_MAX;
			if (randNum < prob) {
				addEdge(i, j);
			}
		}
}

void Graph::addEdge(int v, int w) {
	myGraph[v].push_back(w); // Add w to v’s list.
	myGraph[w].push_back(v); // Add v to w’s list
}

bool Graph::connectGraph(int numOfV) {
	int* distances = new int[numOfV];
	bool isConnected = BFS(0, numOfV, distances);
	delete[]distances;
	return isConnected;
}

bool Graph::BFS(int src, int numOfV, int* distances)
{
	list<int> queue;	// Create a queue for BFS
	bool* visited = new bool[numOfV];
	// Mark all the vertices as not visited
	//bool* visited = new bool[s];
	//initiliaze:
	for (int i = 0; i < numOfV; i++) {
		visited[i] = false;
		distances[i] = -1;
	}

	// Mark the current node as visited and enqueue it
	visited[src] = true;
	distances[src] = 0;
	queue.push_back(src);

	// 'i' will be used to get all adjacent
	// vertices of a vertex
	list<int>::iterator i;

	while (!queue.empty())
	{
		int s = queue.front();
		queue.pop_front();
		for (auto i : myGraph[s])
		{
			if (!visited[i])
			{
				visited[i] = true;
				distances[i] = distances[s] + 1;
				queue.push_back(i);
			}
		}
	}
	for (int i = 0; i < numOfV; i++) {
		if (visited[i] == 0) {
			delete[]visited; return 0;
		}
	}
	delete[]visited;
	return 1;
}

bool Graph::isIsolated(Graph& graph) {
	const int ver = graph.getVertices();
	for (int i = 0; i < ver; i++) {
		if (myGraph[i].size() == 0)
			return true;
	}
	return false;
}

int Graph::diameter(Graph& graph) {
	int diam = 0, edgeDistance = 0;
	const int V = graph.getVertices();
	int* distances = new int[V];

	if (graph.BFS(0, V, distances)) {
		for (int i = 0; i < V; i++) {
			if (distances[i] > diam)
				diam = distances[i];
		}
		for (int i = 1; i < V; i++) {
			graph.BFS(i, V, distances);
			for (int j = 0; j < V; j++) {
				if (distances[j] > diam)
					diam = distances[j];
			}
		}
	}
	else {
		diam = 999999999;
	}
	delete[]distances;
	return diam;
}

void printCSV(int option, double* connectedArr, double* isolatedArr, double* diameterArr) {
	ofstream resultFile;
	resultFile.open("results.csv");
	switch (option) {
	case 1:
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh1[i] << ",";
		resultFile << endl;
		resultFile << "Connected graphs" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)connectedArr[i] << ",";
		resultFile << endl;
		break;

	case 2:
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh2[i] << ",";
		resultFile << endl;
		resultFile << "Diameter=2" << ",";
		for (int i = 0; i < 10; i++) {
			resultFile << (double)diameterArr[i] << ",";
		}
		break;

	case 3:
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh1[i] << ",";
		resultFile << endl;
		resultFile << "Isolated vertices" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)isolatedArr[i] << ",";
		resultFile << endl;
		break;

	case 4:
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh1[i] << ",";
		resultFile << endl;
		resultFile << "Connected graphs" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)connectedArr[i] << ",";
		resultFile << endl;

		resultFile << "Isolated vertices" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)isolatedArr[i] << ",";
		resultFile << endl << endl;

		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh2[i] << ",";
		resultFile << endl;

		resultFile << "Diameter=2" << ",";
		for (int i = 0; i < 10; i++) {
			resultFile << (double)diameterArr[i] << ",";
		}
		break;
	}
	resultFile.close();
	cout << endl << endl << "Results were printed to a CSV file for your reference." << endl;
}

void calcFunc(int option, int ver, int amount) {
	cout << endl << "Calculating";
	int cntConnected = 0, cntDiameter = 0, cntIsolated = 0;
	double connectedArr[10], isolatedArr[10], diameterArr[10];
	Graph graph1(ver);
	if (option == 1) {
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh1[i]);
				cntConnected = cntConnected + graph1.connectGraph(ver);
				graph1.clearGraph();
			}
			cout << ".";
			connectedArr[i] = (double)cntConnected / (double)amount;
			cntConnected = 0;
		}
		printCSV(1, connectedArr, isolatedArr, diameterArr);
	}
	else if (option == 2) {
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh2[i]);
				if (graph1.diameter(graph1) <= 2)
					cntDiameter++;
				graph1.clearGraph();
			}
			cout << ".";
			diameterArr[i] = (double)cntDiameter / (double)amount;
			cntDiameter = 0;
		}
		printCSV(2, connectedArr, isolatedArr, diameterArr);
	}
	else if (option == 3) {
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh1[i]);
				cntIsolated = cntIsolated + graph1.isIsolated(graph1);
				graph1.clearGraph();
			}
			cout << ".";
			isolatedArr[i] = (double)cntIsolated / (double)amount;
			cntIsolated = 0;
		}
		printCSV(3, connectedArr, isolatedArr, diameterArr);
	}
	else if (option == 4) {
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh1[i]);
				cntConnected = cntConnected + graph1.connectGraph(ver);
				cntIsolated = cntIsolated + graph1.isIsolated(graph1);
				graph1.clearGraph();
			}

			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh2[i]);
				if (graph1.diameter(graph1) <= 2)
					cntDiameter++;
				graph1.clearGraph();
			}
			cout << ".";
			connectedArr[i] = (double)cntConnected / (double)amount;
			isolatedArr[i] = (double)cntIsolated / (double)amount;
			diameterArr[i] = (double)cntDiameter / (double)amount;
			cntConnected = 0;
			cntIsolated = 0;
			cntDiameter = 0;
		}
		printCSV(4, connectedArr, isolatedArr, diameterArr);
	}
}

void main() {
	srand(time(NULL));

	int ver, amount, option;
	cout << "###############################################################################################################" << endl;
	cout << "    **************************** Welcome to the Erdos - Renyi Graph Generator: ****************************    " << endl;
	cout << "###############################################################################################################" << endl << endl;
	cout << "Select amount of graph vertices:";
	cin >> ver;
	cout << "Select amount of graphs to generate:";
	cin >> amount;
	cout << endl;
	cout << "###############################################################################################################" << endl;
	cout << "The probabilities were calculted according to 1000 vertices graph" << endl;
	cout << "Probabilities for Connectivity & Isolated: 0.0048,0.0053,0.0059,0.0065,0.0069,0.0072,0.008,0.009,0.01,0.01401" << endl;
	cout << "Probabilities for Diameter: 0.091,0.1,0.103,0.115,0.1175,0.12,0.125,0.13,0.135,0.14" << endl;
	cout << "###############################################################################################################" << endl << endl;
	cout << "Choose an option:" << endl;
	cout << "1) Connectivity " << endl;
	cout << "2) Diameter" << endl;
	cout << "3) Isolated Vertex" << endl;
	cout << "4) All options in order" << endl << endl;
	cout << "Your choice:";
	cin >> option;
	switch (option) {
	case 1:
		calcFunc(1, ver, amount);
		break;
	case 2:
		calcFunc(2, ver, amount);
		break;
	case 3:
		calcFunc(3, ver, amount);
		break;
	case 4:
		calcFunc(4, ver, amount);
		break;
	default:
		cout << endl << "Wrong input" << endl;
	}
}
