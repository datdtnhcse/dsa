#include <iostream>
#include <list>
using namespace std;

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *DFS(int v)
    {
        Adjacency *trav = new Adjacency(this -> V);
        
        list<int> data;
        
        int appear[V];
        int len = 0;
        data.push_back(v);
        while (!data.empty()) {
            bool found = false;
            int back = data.back();
            data.pop_back();
            for (int i = 0; i < len; i++){
                if (appear[i] == back){
                    found = true;
                    break;
                }
            }
            if (found == true){
                continue;
            }
            appear[len] = back;
            len++;
            for (int i = adj[back].getSize() - 1; i >= 0; i--) {
                data.push_back(adj[back].getElement(i));
            }
            trav -> push(back);
        }
        return trav;
	}
};

int main() {
    int V = 8, visited = 0;

    Graph g(V);
    Adjacency *arr;
    int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
    for(int i = 0; i < 9; i++)
    {
    	g.addEdge(edge[i][0], edge[i][1]);
    }

    // g.printGraph();
    // cout << endl;
    arr = g.DFS(visited);
    arr->printArray();
    delete arr;
}