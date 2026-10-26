#include <iostream>
#include <string>
using namespace std;

const int MAX = 20;

// Hyperlink (directed edge) in the adjacency list
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
    int order[MAX];         // visitation order
    int level[MAX];         // BFS level of each page
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
        g.level[i] = -1;
    }
}

// Clear traversal data before every new traversal
void resetTraversal(Graph &g)
{
    g.count = 0;
    for (int i = 0; i < g.n; i++)
    {
        g.visited[i] = false;
        g.level[i] = -1;
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

// Depth First Search
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

// Breadth First Search (fills level[] for reachable pages)
void bfs(Graph &g, int start)
{
    int queue[MAX];
    int front = 0, rear = 0;

    g.visited[start] = true;
    g.level[start] = 0;
    queue[rear++] = start;

    while (front < rear)
    {
        int u = queue[front++];
        g.order[g.count++] = u;

        for (Node* p = g.head[u]; p != NULL; p = p->next)
        {
            if (!g.visited[p->dest])
            {
                g.visited[p->dest] = true;
                g.level[p->dest] = g.level[u] + 1;
                queue[rear++] = p->dest;
            }
        }
    }
}

int readStart(Graph &g)
{
    int s;
    cout << "Enter starting page index (0 to " << g.n - 1 << "): ";
    cin >> s;
    if (s < 0 || s >= g.n)
    {
        cout << "Invalid starting page!\n";
        return -1;
    }
    return s;
}

void showDFS(Graph &g)
{
    int s = readStart(g);
    if (s == -1)
    {
        return;
    }

    resetTraversal(g);
    dfs(g, s);

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

    cout << "\nPages reached from " << g.name[s] << ":\n";
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
    for (int i = 0; i < g.n; i++)
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
}

void showCount(Graph &g)
{
    int s = readStart(g);
    if (s == -1)
    {
        return;
    }

    resetTraversal(g);
    dfs(g, s);

    cout << "\nReachable pages from " << g.name[s] << " (excluding itself): "
         << g.count - 1 << endl;
    cout << "Unreachable pages: " << g.n - g.count << endl;
}

void showLevels(Graph &g)
{
    int s = readStart(g);
    if (s == -1)
    {
        return;
    }

    resetTraversal(g);
    bfs(g, s);

    int maxLevel = 0;
    for (int i = 0; i < g.n; i++)
    {
        if (g.level[i] > maxLevel)
        {
            maxLevel = g.level[i];
        }
    }

    cout << "\nBFS Levels from " << g.name[s] << ":\n";
    for (int l = 0; l <= maxLevel; l++)
    {
        cout << "Level " << l << ": ";
        for (int i = 0; i < g.n; i++)
        {
            if (g.level[i] == l)
            {
                cout << g.name[i] << " ";
            }
        }
        cout << endl;
    }

    cout << "Not reachable: ";
    bool any = false;
    for (int i = 0; i < g.n; i++)
    {
        if (!g.visited[i])
        {
            cout << g.name[i] << " ";
            any = true;
        }
    }
    if (!any)
    {
        cout << "None";
    }
    cout << endl;
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
    int n, e, choice;

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

    do
    {
        cout << "\n----- MENU -----\n";
        cout << "1. DFS traversal (order, reached, not visited)\n";
        cout << "2. Count reachable pages\n";
        cout << "3. Display BFS levels\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: showDFS(g);    break;
            case 2: showCount(g);  break;
            case 3: showLevels(g); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    freeGraph(g);
    return 0;
}
