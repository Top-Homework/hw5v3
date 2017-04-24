#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Graph {
    int V;
    vector<int> *adj;

  public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[ V ];
    }

    void addEdge(unsigned int v, int w) {
        adj[v].push_back(w);
    }

    void BFS(int s) {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }
        vector<int> queue;

        visited[s] = true;
        queue.push_back(s);

        vector<int>::iterator i = queue.begin();

        while (!queue.empty()) {
            s = queue.front();
            cout << s << " ";
            queue.erase(queue.begin());
            for (i = adj[s].begin(); i != adj[s].end(); ++i) {
                if (!visited[*i]) {
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
        }
    }

};

istream& ignoreline(ifstream& in, ifstream::pos_type& pos)
{
	pos = in.tellg();
	return in.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getsize(ifstream& in) {
    ifstream::pos_type pos = in.tellg();
	ifstream::pos_type first = in.tellg();

    ifstream::pos_type lastPos;
    while (in >> ws && ignoreline(in, lastPos)) {
        pos = lastPos;
    }
    in.clear();
    in.seekg(pos);

    string line;
    getline(in, line, ' ');
	int size = stoi(line);
	in.seekg(first);
    return size;
}

int main(int argc, char *argv[]) {
    // if(argc < 2) {
    //     //cerr("Usage: reachability \"E=input.txt;source=num\"\n");
    //     return 1;
    // }
    // ArgumentManager am(argc, argv);
    // string filename = am.get("E");
    // int source = stoi(am.get("source"));
    // ifstream ifs;
    // ifs.open(filename);
    // ofstream temp;
    // temp.open("temp.txt");

    // Used for debugging on Visual Studio
    string filename = ("1.txt");
    ifstream ifs;
    ifs.open(filename);
    ofstream temp;
    temp.open("temp.txt");
    int source = 2;

	int size = 0;
	if (ifs) {
		size = getsize(ifs);
	}

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
    cout << data[1][1] << endl;

    Graph g(size);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Following is Breadth First Traversal "
            << "(starting from vertex 2) \n";
    g.BFS(2);
    cout << endl;
	getchar();

    return 0;
}
