/*Assigned By:
Netanel Iluz, ID 205856354
Sharon Guy, ID 316582691
*/


#include <iostream>
#include <time.h>
#include <stdlib.h> 
#include <vector>
#include <list>
#include <fstream>
using namespace std;
double pThresh1[10] = { 0.0048,0.0053,0.0059,0.0065,0.0069,0.0072,0.008,0.009,0.01,0.01401 };	// For 1000 vertices connectivity
double pThresh2[10] = { 0.091,0.1,0.103,0.115,0.1175,0.12,0.125,0.13,0.135,0.14 };	 // For 1000 vertices diameter
double pThresh3[10] = { 0.0046,0.005343,0.005599,0.006631,0.00691,0.007231,0.0084,0.0093,0.0123,0.01469 }; // For 1000 vertices Isolated vertex
void printCSV(int option, int ver, int amount, double* connectedArr, double* isolatedArr, double* diameterArr);
void calcFunc(int option, int ver, int amount);

class Graph {
	int vertices;
	vector<vector<int>> myGraph;
public:
	Graph(int ver) {
		myGraph.resize(ver);
		this->vertices = ver;
	}
	~Graph() {
		myGraph.clear();
	}
	void graph_random_build(double prob);
	void addEdge(int v, int w);
	bool isIsolated(Graph& graph);
	int diameter(Graph& graph);
	bool BFS(int s, int numOfV, int* distances);
	bool connectGraph(int numOfV);
	int getVertices() { return this->vertices; }
	void setVer(int ver) { this->vertices = ver; }
	void clearGraph() {  // Clear all the edges in the graph
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
	myGraph[v].push_back(w); // Add w to v’s list
	myGraph[w].push_back(v); // Add v to w’s list
}
bool Graph::connectGraph(int numOfV) { // Check if the graph is connected
	int* distances = new int[numOfV];
	bool isConnected = BFS(0, numOfV, distances);
	delete[]distances;
	return isConnected;
}
bool Graph::BFS(int src, int numOfV, int* distances)
{
	list<int> queue;	// Create a queue for BFS
	bool* visited = new bool[numOfV]; // Mark all the vertices as not visited
	// BFS start values : initiliaze 
	for (int i = 0; i < numOfV; i++) {
		visited[i] = false;
		distances[i] = -1;
	}

	// Mark the current node as visited and enqueue it - Source node
	visited[src] = true;
	distances[src] = 0;
	queue.push_back(src);

	// 'i' will be used to get all adjacent
	// vertices of a vertex
	list<int>::iterator i;

	while (!queue.empty()) // Run until the queue is empty
	{
		int s = queue.front();
		queue.pop_front();
		for (auto i : myGraph[s])
		{
			if (!visited[i])
			{
				visited[i] = true; // Mark the vertex as visited
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
bool Graph::isIsolated(Graph& graph) { // Check if there is an isolated vertex in the graph
	const int ver = graph.getVertices();
	for (int i = 0; i < ver; i++) {
		if (myGraph[i].size() == 0)
			return true;
	}
	return false;
}

int Graph::diameter(Graph& graph) { // Calculate the graph's diameter
	int diam = 0, edgeDistance = 0;
	const int V = graph.getVertices();
	int* distances = new int[V];
	if (graph.BFS(0, V, distances)) { // First BFS to check if the graph is connected
		for (int i = 0; i < V; i++) {
			if (distances[i] > diam)
				diam = distances[i];
		}
		for (int i = 1; i < V; i++) { // Run BFS on every vertex in the graph
			graph.BFS(i, V, distances);
			for (int j = 0; j < V; j++) {
				if (distances[j] > diam)
					diam = distances[j]; // The diameter is the longest distance from the src vertex
			}
		}
	}
	else { // Diameter of an unconnected graph is infinity
		diam = 999999999;
	}
	delete[]distances;
	return diam;
}

void printCSV(int option, int ver, int amount, double* connectedArr, double* isolatedArr, double* diameterArr) {
	ofstream resultFile;
	resultFile.open("results.csv");
	resultFile << "Vertices" << "," << ver << endl;
	resultFile << "Amount of graphs for each probability" << "," << amount << endl << endl;
	switch (option) {
	case 1: // Connectivity
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh1[i] << ",";
		resultFile << endl;
		resultFile << "Connected graphs" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)connectedArr[i] << ",";
		resultFile << endl;
		break;

	case 2: //Diameter <=2
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh2[i] << ",";
		resultFile << endl;
		resultFile << "Diameter<=2" << ",";
		for (int i = 0; i < 10; i++) {
			resultFile << (double)diameterArr[i] << ",";
		}
		break;

	case 3: // Isolated vertices
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh3[i] << ",";
		resultFile << endl;
		resultFile << "Isolated vertices" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)isolatedArr[i] << ",";
		resultFile << endl;
		break;

	case 4: // All
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh1[i] << ",";
		resultFile << endl;
		resultFile << "Connected graphs" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)connectedArr[i] << ",";
		resultFile << endl << endl;
		resultFile << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh2[i] << ",";
		resultFile << endl;
		resultFile << "Diameter<=2" << ",";
		for (int i = 0; i < 10; i++) {
			resultFile << (double)diameterArr[i] << ",";
		}
		resultFile << endl << endl << "Probability" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << pThresh3[i] << ",";
		resultFile << endl;
		resultFile << "Isolated vertices" << ",";
		for (int i = 0; i < 10; i++)
			resultFile << (double)isolatedArr[i] << ",";
		resultFile << endl;
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
	if (option == 1) { // Connectivity probability
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
		printCSV(1, ver, amount, connectedArr, isolatedArr, diameterArr);
	}
	else if (option == 2) { // Diameter <=2 probability
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
		printCSV(2, ver, amount, connectedArr, isolatedArr, diameterArr);

	}
	else if (option == 3) { // Isolated vertices probability
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh3[i]);
				cntIsolated = cntIsolated + graph1.isIsolated(graph1);
				graph1.clearGraph();
			}
			cout << ".";
			isolatedArr[i] = (double)cntIsolated / (double)amount;
			cntIsolated = 0;
		}
		printCSV(3, ver, amount, connectedArr, isolatedArr, diameterArr);
	}
	else if (option == 4) { // All
		for (int i = 0; i < 10; i++) {
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh1[i]);
				cntConnected = cntConnected + graph1.connectGraph(ver);
				graph1.clearGraph();
			}

			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh2[i]);
				if (graph1.diameter(graph1) <= 2)
					cntDiameter++;
				graph1.clearGraph();
			}
			for (int g = 0; g < amount; g++) {
				graph1.graph_random_build(pThresh3[i]);
				cntIsolated = cntIsolated + graph1.isIsolated(graph1);
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
		printCSV(4, ver, amount, connectedArr, isolatedArr, diameterArr);
	}
}

void main() {
	srand(time(NULL));
	int ver, amount, option;
	cout << "#######################################################################################################################" << endl;
	cout << "        **************************** Welcome to the Erdos - Renyi Graph Generator: ****************************    " << endl;
	cout << "#######################################################################################################################" << endl << endl;
	cout << "Select amount of graph vertices:";
	cin >> ver;
	cout << "Select amount of graphs to generate for each probability:";
	cin >> amount;
	cout << endl;
	cout << "#######################################################################################################################" << endl;
	cout << "The probabilities were calculted according to 1000 vertices graph" << endl;
	cout << "Probabilities for Connectivity: 0.0048,0.0053,0.0059,0.0065,0.0069,0.0072,0.008,0.009,0.01,0.01401" << endl;
	cout << "Probabilities for Diameter: 0.091,0.1,0.103,0.115,0.1175,0.12,0.125,0.13,0.135,0.14" << endl;
	cout << "Probabilities for Isolated vertices: 0.0046,0.005343,0.005599,0.006631,0.00691,0.007231,0.0084,0.0093,0.0123,0.01469" << endl;
	cout << "#######################################################################################################################" << endl << endl;
	cout << "Choose an option:" << endl;
	cout << "1) Connectivity " << endl;
	cout << "2) Diameter" << endl;
	cout << "3) Isolated Vertices" << endl;
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
