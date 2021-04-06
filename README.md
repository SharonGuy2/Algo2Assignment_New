# Algo2Assignment_New
Algo2Assignment_New

1st assignment in Algo2 course

// BFS algorithm in C++

#include #include

using namespace std;

class Graph { int numVertices; list* adjLists; bool* visited;

public: Graph(int vertices); void addEdge(int src, int dest); void BFS(int startVertex); };

// Create a graph with given vertices, // and maintain an adjacency list Graph::Graph(int vertices) { numVertices = vertices; adjLists = new list[vertices]; }

// Add edges to the graph void Graph::addEdge(int src, int dest) { adjLists[src].push_back(dest); adjLists[dest].push_back(src); }

// BFS algorithm void Graph::BFS(int startVertex) { visited = new bool[numVertices]; for (int i = 0; i < numVertices; i++) visited[i] = false;

list queue;

visited[startVertex] = true; queue.push_back(startVertex);

list::iterator i;

while (!queue.empty()) { int currVertex = queue.front(); cout << "Visited " << currVertex << " "; queue.pop_front();

for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
  int adjVertex = *i;
  if (!visited[adjVertex]) {
    visited[adjVertex] = true;
    queue.push_back(adjVertex);
  }
}
} }

int main() { Graph g(4); g.addEdge(0, 1); g.addEdge(0, 2); g.addEdge(1, 2); g.addEdge(2, 0); g.addEdge(2, 3); g.addEdge(3, 3);

g.BFS(2);

return 0; }



**Adding Working Source.cpp content as README text for Backup:**

#include <iostream>
#include <time.h>
#include <stdlib.h> 
#include <algorithm>
using namespace std;

#include <list>
#include <fstream>
//#define p1 0.02   //double prob;	

class Graph {
	int vertices;
	double prob;
	list <int>* myGraph;
	bool* visited;  /* = new bool[vertices];*/
	int* distances;
	//int diam;

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
			return -1;
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
		//cout << "\n11 = " << distances[11];
		//cout << "\n visited = " << visited[11];
		//cout << "\n1 = " << distances[1];
		//cout << "\n visited = " << visited[1] << "\n";
	}
	//
	bool connectGraph() {
		BFS(0);
		for (int i = 0; i < this->vertices; i++)
			if (!this->visited[i])
				return false;
		return true;
	}
	Graph(int ver/*, double p*/) {
		this->vertices = ver;
		//this->prob = p;
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
		cout << " v=" << v << " to " << w << "\n";
		cout << " w=" << w << " to " << v << "\n";
	}
	void setProb(double p) { this->prob = p; }

};

//Graph::graph_random_build(){}
//Graph::BFS(int source) {}
//Graph::bool connectGraph(){}
//Graph::void diameter(){}
//Graph::bool isIsolated(){}







void main() {
	//int randomNum;
	srand(time(NULL));
	//	randomNum = rand() % 10000 + 1;
	//	for (int i = 0; i < 1000; i++) {
		//	randomNum = rand() % 10000 + 1;
			//cout << randomNum << "\n";

	//	}
	//double p;
	//int ver;
	//cout << "Wellcome to Erdos - Renyi Graph Generator: \n";
	//cout << "set a probabilty to graph:";
	//cin >> p;
	//cout << "set a graph verticies:";
	//cin >> ver;

	//Graph test(ver);
	//test.setProb(p);
	//test.graph_random_build();

	Graph test(11);
	test.addEdge(0, 2);
	test.addEdge(0, 4);
	test.addEdge(4, 5);
	test.addEdge(4, 6);
	test.addEdge(4, 5);
	test.addEdge(5, 7);
	test.addEdge(7, 6);
	test.addEdge(2, 8);
	test.addEdge(8, 9);
	test.addEdge(8, 10);
	test.addEdge(9, 10);
	test.addEdge(2, 3);
	test.addEdge(1, 9); //..
	test.addEdge(6, 8);
	//test.addEdge(12, 11);//insolating test
	//test.diameter();
	//cout << "the diameter is " << test.diameter();
	//test.addEdge(3, 11); //connectivity... example.
	//test.BFS(0);
	//cout << "\nThe connectivity is " << test.connectGraph() << "\n";
	//cout << "\nDo we have insolated vertex " << test.isIsolated() << "\n";

	Graph test2(1000);
	cout << "\nThe connectivity is " << test2.connectGraph() << "\n";
	cout << "the diameter is " << test2.diameter();

	////////ofstream testFile;
	////////testFile.open("testDoc.csv");
	////////testFile << "0.002,0.003,0.004,0.005\n";
	//////////testFile << "Connectivity,";
	////////testFile << "1,0,1,1\n";
	//////////testFile << "Diameter,";
	////////testFile << "3,2,5,3\n";
	//////////testFile << "IsIsolated,";
	////////testFile << "1,0,0,1\n";
	//////////testFile << test.connectGraph() << endl;
	//////////testFile << test.isIsolated();
	////////testFile.close();
}



/*
		printf ("First number: %d\n", rand()%100);
		 srand (time(NULL));
		 http://www.cplusplus.com/reference/cstdlib/srand/
		 https://www.cplusplus.com/reference/cstdlib/rand/
*/
