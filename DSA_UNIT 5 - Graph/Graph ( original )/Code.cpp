#include <iostream>
#include <string>
using namespace std;

const int MAX = 20;

// Hyperlink (edge) in the adjacency list
struct Node
{
    int dest;
    Node* next;
};

// Graph of webpages
struct Graph
{
    int n;                  // number of webpages
    string name[MAX];       // webpage names
    Node* head[MAX];        // adjacency list heads
    bool visited[MAX];      // visited flags
    int order[MAX];         // DFS visitation order
    int count;              // number of pages visited
};

void initGraph(Graph &g, int n)
{
    g.n = n;
    g.count = 0;
    for (int i = 0; i < MAX; i++)
    {
        g.head[i] = NULL;
        g.visited[i] = false;
    }
}

// Add directed edge: from -> to
void addLink(Graph &g, int from, int to)
{
    Node* p = new Node;
    p->dest = to;
    p->next = NULL;

    if (g.head[from] == NULL)
    {
        g.head[from] = p;
    }
    else
    {
        Node* t = g.head[from];
        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = p;
    }
}

void dfs(Graph &g, int u)
{
    g.visited[u] = true;
    g.order[g.count++] = u;

    for (Node* p = g.head[u]; p != NULL; p = p->next)
    {
        if (!g.visited[p->dest])
        {
            dfs(g, p->dest);
        }
    }
}

void displayGraph(Graph &g)
{
    cout << "\nWebpages and their hyperlinks:\n";
    for (int i = 0; i < g.n; i++)
    {
        cout << i << " " << g.name[i] << " -> ";
        if (g.head[i] == NULL)
        {
            cout << "(no links)";
        }
        for (Node* p = g.head[i]; p != NULL; p = p->next)
        {
            cout << g.name[p->dest] << " ";
        }
        cout << endl;
    }
}

void freeGraph(Graph &g)
{
    for (int i = 0; i < g.n; i++)
    {
        Node* p = g.head[i];
        while (p != NULL)
        {
            Node* t = p;
            p = p->next;
            delete t;
        }
        g.head[i] = NULL;
    }
}

int main()
{
    Graph g;
    int n, e, start;

    cout << "Enter number of webpages (max " << MAX << "): ";
    cin >> n;

    if (n <= 0 || n > MAX)
    {
        cout << "Invalid number of webpages!\n";
        return 0;
    }

    initGraph(g, n);

    cout << "Enter names of webpages (no spaces):\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << ": ";
        cin >> g.name[i];
    }

    cout << "Enter number of hyperlinks: ";
    cin >> e;

    cout << "Enter hyperlinks as (from_index to_index):\n";
    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a >= 0 && a < n && b >= 0 && b < n)
        {
            addLink(g, a, b);
        }
        else
        {
            cout << "Invalid link, enter again.\n";
            i--;
        }
    }

    displayGraph(g);

    cout << "\nEnter starting page index: ";
    cin >> start;

    if (start < 0 || start >= n)
    {
        cout << "Invalid starting page!\n";
        freeGraph(g);
        return 0;
    }

    dfs(g, start);

    cout << "\nDFS Visitation Order:\n";
    for (int i = 0; i < g.count; i++)
    {
        cout << g.name[g.order[i]];
        if (i != g.count - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "\nPages reached from " << g.name[start] << ":\n";
    if (g.count == 1)
    {
        cout << "None (no outgoing path)\n";
    }
    for (int i = 1; i < g.count; i++)
    {
        cout << g.name[g.order[i]] << endl;
    }

    cout << "\nPages NOT visited:\n";
    bool any = false;
    for (int i = 0; i < n; i++)
    {
        if (!g.visited[i])
        {
            cout << g.name[i] << endl;
            any = true;
        }
    }
    if (!any)
    {
        cout << "None (all pages are reachable)\n";
    }

    freeGraph(g);
    return 0;
}
