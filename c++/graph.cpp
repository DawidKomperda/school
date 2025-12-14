#include <iostream>
#include <queue>

using namespace std;

// Szablon rozwiązania:
struct edge
{
    int s;
    int t;
};
class Graph
{
private:
    int **adjMatrix;
    int n;                            // liczba węzłów
    bool directed;                    // true - graf skierowany, false - graf nieskierowany
    void dfs(int s, int *visited) {
        visited[s] = 1;
        cout << s << " ";
        
        for (int i = 0; i < n; i++) {
            if (adjMatrix[s][i] == 1 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }; // wykonuje przeszukiwanie i wyświetla węzły w porządku odwiedzenia
public:
    // Graph(int n, int m, edge edges[], bool directed);    //tworzy graf w oparciu o podaną listę krawędzi
    Graph()
    { // konstruktor domyślny z predefiniowanym grafem testowym
        this->n = 6;
        this->directed = true;
        adjMatrix = new int *[n];

        for (int i = 0; i < n; i++)
            adjMatrix[i] = new int[n]{0};

        adjMatrix[0][4] = 1;
        adjMatrix[0][5] = 1;
        adjMatrix[1][0] = 1;
        adjMatrix[1][2] = 1;
        adjMatrix[1][4] = 1;
        adjMatrix[2][1] = 1;
        adjMatrix[2][3] = 1;
        adjMatrix[2][4] = 1;
        adjMatrix[3][2] = 1;
        adjMatrix[3][5] = 1;
        adjMatrix[4][0] = 1;
        adjMatrix[4][1] = 1;
        adjMatrix[4][3] = 1;
        adjMatrix[5][3] = 1;
        adjMatrix[5][4] = 1;
    }
    //   Graph(int n, int m, bool directed);    //tworzy losowy graf o n węzłach i m krawędziach, skierowany lub nieskierowany
    void bfs(int s)
    {
        bool *visited = new bool[n]{false};
        queue<int> q;

        visited[s] = true;
        q.push(s);

        cout << " BFS :";
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v = 0; v < n; v++)
            {
                if (adjMatrix[u][v] == 1 && !visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;     // Add newline for clean output
        delete[] visited; // Fix memory leak

    }; // wykonuje przeszukiwanie i wyświetla węzły w porządku odwiedzenia
    void dfs(int s)
    {
        int* visited = new int[n]{0}; // 0 for unvisited, 1 for visited
        cout << "DFS: ";
        dfs(s, visited);
        cout << endl;
        delete[] visited;
    }; // metoda pomocnicza dla dfs - tworzy tabelę visited i wywołuję metodę prywatną dfs
    friend ostream &operator<<(ostream &out, Graph &g)
    {
        out << "Adjecency matrix" << endl;
        for (int i = 0; i < g.n; i++)
        {
            for (int j = 0; j < g.n; j++)
            {
                out << g.adjMatrix[i][j] << " ";
            }
            out << endl;
        }
        return out; // Required: return the stream object
    }; // wyświetla graf
    ~Graph()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

int main()
{

    //   int n = 6, m =15;
    //   edge directedGraph[]={{0,4},{0,5},{1,0},{1,2},{1,4},{2,1},{2,3},{2,4},{3,2},{3,5},{4,0},{4,1},{4,3},{5,3},{5,4}};  //przykładowy graf
    //   Graph g(n,m,directedGraph,true);       // jeśli używany jest konstruktor pozwalający wprowadzić graf

    Graph g; // jeśli używany jest konstruktor domyślny z predefiniowanym grafem testowym
    cout << g;
    g.bfs(0);
    g.dfs(0);
    // testowanie np. dla różnych węzłów źródłowych, dla innych grafów
}
