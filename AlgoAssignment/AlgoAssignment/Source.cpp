#include <iostream>
#include <time.h>
#include <stdlib.h> 
#include <algorithm>
using namespace std;

#include <list>
#include <fstream>
double pThresh1[10] = { 0.0059,0.0061,0.0063,0.0067,0.0069,0.0072,0.0075,0.0079,0.0081,0.0084 };
double pThresh2[10] = { 0.1165,0.1167,0.1170,0.1173, 0.1175,0.1179,0.1183,0.1186,0.1192,0.1195 };
class Graph {
	int vertices;
	double prob;
	list <int>* myGraph;
	bool* visited;  /* = new bool[vertices];*/
	int* distances;


public:
	void graph_random_build() {
		int randomNum;
		for (int i = 0; i < this->vertices; i++)
			for (int j = i; j < this->vertices; j++) {
				randomNum = rand() % 10000 + 1;
				if ((double)randomNum / 10000.0 < this->prob)
					addEdge(i, j);
			}
	}
	int diameter() {
		int diam = 0;
		bool connectCheck = connectGraph();
		if (!connectCheck) {
			return 999;
		}

		int* lastVertex = max_element(distances, distances + vertices);
		if (*lastVertex > diam) diam = *lastVertex;
		for (int i = 1; i < this->vertices; i++) {
			BFS(i);
			lastVertex = max_element(distances, distances + vertices);
			if (*lastVertex > diam) diam = *lastVertex;
		}
		return diam;
	}
	bool isIsolated() {
		int a;
		for (int i = 0; i < this->vertices; i++) {
			a = this->myGraph[i].size();
			if (this->myGraph[i].size() == 0)
				return true;
		}
		return false;

	}
	void BFS(int s)
	{
		// Mark all the vertices as not visited
		//bool* visited = new bool[s];
		for (int i = 0; i < this->vertices; i++) {
			this->visited[i] = false;
			this->distances[i] = -1;
		}

		// Create a queue for BFS
		list<int> queue;

		// Mark the current node as visited and enqueue it
		this->visited[s] = true;
		this->distances[s] = 0;
		queue.push_back(s);

		// 'i' will be used to get all adjacent
		// vertices of a vertex
		list<int>::iterator i;

		while (!queue.empty())
		{
			// Dequeue a vertex from queue and print it
			s = queue.front();
			//cout << s << " ";
			queue.pop_front();

			// Get all adjacent vertices of the dequeued
			// vertex s. If a adjacent has not been visited,
			// then mark it visited and enqueue it
			for (i = myGraph[s].begin(); i != myGraph[s].end(); ++i)
			{
				if (!this->visited[*i])
				{
					this->visited[*i] = true;
					this->distances[*i] = distances[s] + 1;
					//cout << "\ndistance of i = " << *i << " is " << distances[*i];
					//cout << "\n visited = " << visited[*i];
					queue.push_back(*i);
				}
			}

		}
	}
	//
	bool connectGraph() {
		BFS(0);
		for (int i = 0; i < this->vertices; i++)
			if (!this->visited[i])
				return false;
		return true;
	}
	Graph(int ver, double p) {
		this->vertices = ver;
		this->prob = p;
		myGraph = new list <int>[vertices]; //list in size "V".
		//diam = 0;
		visited = new bool[vertices];
		distances = new int[vertices];
	}
	~Graph() {
		//need to delete the graphs (delete the "New"!)
	}
	void addEdge(int v, int w)
	{
		myGraph[v].push_back(w); // Add w to v’s list.
		myGraph[w].push_back(v); // Add v to w’s list
		//cout << " v=" << v << " to " << w << "\n";
		//cout << " w=" << w << " to " << v << "\n";
	}
	

};







void main() {
	srand(time(NULL));

	int ver,amount;
	cout << "Welcome to the Erdos - Renyi Graph Generator: \n";
	cout << "Select amount of graph vertices:";
	cin >> ver;
	cout << "Select amount of graphs to generate:";
	cin >> amount;

	////////Graph test(11, 0.44);
	////////test.addEdge(0, 2);
	////////test.addEdge(0, 4);
	////////test.addEdge(4, 6);
	////////test.addEdge(4, 5);
	////////test.addEdge(5, 7);
	////////test.addEdge(7, 6);
	////////test.addEdge(2, 8);
	////////test.addEdge(8, 9);
	////////test.addEdge(8, 10);
	////////test.addEdge(9, 10);
	////////test.addEdge(2, 3);
	////////test.addEdge(1, 9); //..
	////////test.addEdge(6, 8);
	////////cout << "\n diamter is " << test.diameter() << "\n";
	//test.addEdge(12, 11);//insolating test
	//test.diameter();
	//cout << "the diameter is " << test.diameter();
	//test.addEdge(3, 11); //connectivity... example.
	//test.BFS(0);
	//cout << "\nThe connectivity is " << test.connectGraph() << "\n";
	//cout << "\nDo we have insolated vertex " << test.isIsolated() << "\n";
	ofstream resultFile;
	resultFile.open("results.csv");
	double connectedArr[10];
	double isolatedArr[10];
	double diameterArr[10];

	int cntConnected = 0;
	int cntDiameter = 0;
	int cntIsolated = 0;
	resultFile << "Probability" << ",";
	for (int i = 0; i < 10; i++)
		resultFile << pThresh1[i] << ",";
	resultFile << endl;
	for (int i = 0; i < 10; i++) {
		for (int g = 0; g < amount; g++) {
			Graph graph1(ver, pThresh1[i]);
			graph1.graph_random_build();
			cntConnected = cntConnected + graph1.connectGraph();
			cntIsolated = cntIsolated + graph1.isIsolated();
			//cout << "\nThe connectivity is " << test2.connectGraph() << "\n";
			//cout << "Do we have insolated vertex " << test2.isIsolated() << "\n";
			//cout << "The diameter is " << test2.diameter() << "\n";

		}
		connectedArr[i] = (double)cntConnected / (double)amount;
		isolatedArr[i] = (double)cntIsolated / (double)amount;
		cntConnected = 0;
		cntIsolated = 0;

		for (int g = 0; g < amount; g++) {
			Graph graph2(ver, pThresh2[i]);
			graph2.graph_random_build();
			if (graph2.diameter() == 2)
				cntDiameter++;			
		}
		diameterArr[i] = (double)cntDiameter / (double)amount;
		cntDiameter = 0;
	}
	
	resultFile << "Connected graphs"<<",";
	for (int i = 0; i < 10; i++) 
		resultFile << connectedArr[i] << ",";
	resultFile << endl;

	resultFile << "Isolated vertices" << ",";
	for (int i = 0; i < 10; i++)
		resultFile << isolatedArr[i] << ",";
	resultFile << endl << endl;
	
	resultFile << "Probability" << ",";
	for (int i = 0; i < 10; i++)
		resultFile << pThresh2[i] << ",";
	resultFile << endl;

	resultFile << "Diameter=2" << ",";
	for (int i = 0; i < 10; i++) {
		resultFile << diameterArr[i] << ",";
	}
	
	resultFile.close();
	cout << "\nResults were printed to a CSV file for your reference.";

}
