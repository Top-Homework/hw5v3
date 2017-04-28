#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include "ArgumentManager.h"

using namespace std;

// This class represents a directed graph using adjacency list representation
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // Pointer to an array containing adjacency lists
	int source;

  public:
	// Constructor
	Graph(int V, int source) {
		this->V = V;
		adj = new list<int>[ V + 1 ];
		this->source = source;
	}

	// function to add an edge to graph
	void addEdge(int v, int w) {
		adj[v].push_back(w); // Add w to v's list.
	}

	// prints BFS traversal from a given source s
	void BFS(int s) {
		// Mark all the vertices as not visited
		bool *visited = new bool[V + 1];
		for (int i = 0; i <= V; i++)
			visited[i] = false;

		// Create a queue for BFS
		list<int> queue;

		// Mark the current node as visited and enqueue it
		visited[s] = true;
		queue.push_back(s);

		// 'i' will be used to get all adjacent vertices of a vertex
		list<int>::iterator i;

		list<int> vertices;
		while (!queue.empty()) {
			// Dequeue a vertex from queue and print it
			s = queue.front();
			if (s != source) {
				vertices.push_back(s);
				//cout << s << " ";
			}
			queue.pop_front();

			// Get all adjacent vertices of the dequeued vertex s
			// If a adjacent has not been visited, then mark it visited
			// and enqueue it
			for (i = adj[s].begin(); i != adj[s].end(); ++i) {
				if (!visited[*i]) {
					visited[*i] = true;
					queue.push_back(*i);
				}
			}
		}

		// Sort the list in ascending order
		vertices.sort();
		for (list<int>::iterator it = vertices.begin(); it != vertices.end(); it++) {
			cout << *it << " ";
		}
	}
	
};

int main(int argc, char *argv[]) {
    if(argc < 2) {
        //cerr("Usage: reachability \"E=input.txt;source=num\"\n");
        return 1;
    }
    ArgumentManager am(argc, argv);
    string filename = am.get("E");
    int source = stoi(am.get("source"));
    ifstream ifs;
    ifs.open(filename);

    // Used for debugging on Visual Studio
    // string filename = ("4.txt");
    // ifstream ifs;
    // ifs.open(filename);
    // int source = 1;

    // The result of the read is placed in here
    // In C++, we use a vector like an array but vectors can dynamically grow
    // as required when we get more data.
    vector<vector<int>> data;
    string line;
    // Read one line at a time into the variable line:
    while (getline(ifs, line)) {
        vector<int> lineData;
        stringstream lineStream(line);
        int value;
        // Read an integer at a time from the line
        while (lineStream >> value) {
            // Add the integers from a line to a 1D array (vector)
            lineData.push_back(value);
        }
        // When all the integers have been read, add the 1D array
        // into a 2D array (as one line in the 2D array)
        data.push_back(lineData);
    }
	ifs.close();
	int size = 0;
	size = data.back().at(0); // Retrieves size from last elemnt
	data.pop_back(); //Deletes last line of vector

    Graph g(size, source);

	for (int i = 0; i < data.size(); i++) {
		g.addEdge(data[i][0], data[i][1]);
		// cout << "\t" << data[i][0] << " " << data[i][1] << endl;
	}
	// cout << endl;

    // cout << "\tFollowing is Breadth First Traversal (starting from vertex n) \n";
    g.BFS(source);
    // cout << endl;
	// getchar();
    return 0;
}
