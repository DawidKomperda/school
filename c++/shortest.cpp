#include <iostream>
#include <limits> // Add this at the top for infinity

using namespace std;

struct weightedEdge
{
    int s;
    int t;
    double w; // waga krawędzi
};

class WeightedGraph
{
private:
    double **adjWeightMatrix;
    int n; // liczba węzłów
    bool directed;

public:
    WeightedGraph()
    {
        this->n = 6;
        this->directed = true;

        // Fix: Allocate double** instead of int**
        adjWeightMatrix = new double *[n];

        for (int i = 0; i < n; i++)
            adjWeightMatrix[i] = new double[n]{0.0}; // Initialize with 0.0

        adjWeightMatrix[0][4] = 1;
        adjWeightMatrix[0][5] = 9;
        adjWeightMatrix[1][0] = 2;
        adjWeightMatrix[1][2] = 7;
        adjWeightMatrix[1][4] = 4;
        adjWeightMatrix[2][1] = 4;
        adjWeightMatrix[2][3] = 1;
        adjWeightMatrix[2][4] = 9;
        adjWeightMatrix[3][2] = 7;
        adjWeightMatrix[3][5] = 1;
        adjWeightMatrix[4][0] = 2;
        adjWeightMatrix[4][1] = 4;
        adjWeightMatrix[4][3] = 5;
        adjWeightMatrix[5][3] = 2;
        adjWeightMatrix[5][4] = 3;
    }

    // Placeholder for Dijkstra implementation
    void Dijkstra(int s)
    {
        // 1. Use double* because your weights are double
        // 2. Fix pointer syntax (double* dist)
        double *dist = new double[n];
        bool *visited = new bool[n];

        // 3. Initialize arrays manually with a loop
        for (int i = 0; i < n; i++)
        {
            dist[i] = numeric_limits<double>::infinity(); // Represents "Infinity"
            visited[i] = false;
        }

        dist[s] = 0; // Distance to start node is always 0

        cout << "Dijkstra starting at " << s << endl;

        // ... rest of algorithm ...

        // Don't forget to clean up later!
        delete[] dist;
        delete[] visited;
    }

    friend ostream &operator<<(ostream &out, WeightedGraph &g)
    {
        out << "Adjacency Weight Matrix:" << endl;
        for (int i = 0; i < g.n; i++)
        {
            for (int j = 0; j < g.n; j++)
            {
                out << g.adjWeightMatrix[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    ~WeightedGraph()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] adjWeightMatrix[i];
        }
        delete[] adjWeightMatrix;
    }
};

int main()
{
    WeightedGraph g;
    cout << g;
    g.Dijkstra(0);
    return 0;
}