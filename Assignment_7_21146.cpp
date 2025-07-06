#include <iostream>
#include <map>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

class Graph {
    map<int, string> cities;
    int cost_arr[6][6] = { 
        {INF, 50, 450, INF, 450, 400},
        {50, INF, 500, 400, INF, INF},
        {450, 500, INF, 300, 700, INF},
        {INF, 400, 300, INF, 600, INF},
        {450, INF, 700, 600, INF, INF},
        {400, INF, INF, INF, INF, INF}
    };

public:
    void graph_entries() {
        cities = {
            {0, "Pune"}, {1, "Mumbai"}, {2, "Delhi"},
            {3, "Ahmedabad"}, {4, "Chennai"}, {5, "Bangalore"}
        };
    }
    
    void display_graph() {
        cout << "Telephone Line Costs Between Cities:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = i + 1; j < 6; j++) {
                if (cost_arr[i][j] != INF) {
                    cout << cities[i] << " -> " << cities[j] << " = " << cost_arr[i][j] << "\n";
                }
            }
        }
    }

    void prims_algo() {
        vector<bool> MST(6, false);
        vector<int> parent(6, -1);
        vector<int> key(6, INF);

        key[0]=0;
        int total_cost=0;

        for (int count=0; count<5; count++){
            int u=-1;
            for (int i = 0; i < 6; i++){
                if (!MST[i] && (u == -1 || key[i] < key[u])){
                    u = i;
                }
            }

            MST[u] = true;

            for (int v = 0; v < 6; v++) {
                if (cost_arr[u][v] != INF && !MST[v] && cost_arr[u][v] < key[v]) {
                    key[v] = cost_arr[u][v];
                    parent[v] = u;
                }
            }
        }
        cout << "\nEdges in MST:\n";
        for (int i = 1; i < 6; i++) {
            cout << cities[parent[i]] << " - " << cities[i] << " = " << cost_arr[i][parent[i]] << "\n";
            total_cost += cost_arr[i][parent[i]];
        }

        cout << "\nMinimum Cost = " << total_cost << endl;
    }
};

int main() {
    Graph g;
    g.graph_entries();
    g.display_graph();
    g.prims_algo();
    return 0;
}