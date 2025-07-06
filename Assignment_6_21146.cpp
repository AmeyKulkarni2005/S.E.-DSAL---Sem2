// Represent a given graph using adjacency list to perform DFS and BFS. Use the map of 
// the area around the college as the graph. Identify the prominent land marks as nodes 
// and perform DFS and BFS on that.  

#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <list>
using namespace std;

class Graph{
    map<string, list<string>> adj_list;
public:
    void addedge(string u, string v){
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    void display_vert(){
        cout<<"The important landmarks are:"<<endl;
        for (auto &it:adj_list){
            cout<<"-> "<<it.first<<endl;
        }
    }

    void display_graph(){
        cout<<"Representation of Graph in Adjacency List Form: "<<endl;
        for (auto it:adj_list){
            cout<<it.first<<" -> ";
            auto temp = it.second;
            for (auto it2=temp.begin(); it2!=temp.end(); ++it2) {
                cout<<*it2;
                if (next(it2)!=temp.end())
                    cout<<" -> ";
            }
            cout<<endl;
        }
    }

    void DFS(string root){
        map<string, bool> visited;
        stack<string> s;
        s.push(root);

        cout<<"Depth First Search starting from your college i.e. "<<root<<": "<<endl;
        while (!s.empty()){
            string node = s.top();
            s.pop();

            if (!visited[node]){
                cout<<node<<" -> ";
                visited[node] = true;
            }

            for (auto it:adj_list[node]){
                if (!visited[it]){
                    s.push(it);
                }
            }
        }
        cout<<endl;
    }

    void BFS(string root){
        map<string, bool> visited;
        queue<string> q;
        q.push(root);
        visited[root] = true;

        cout<<"Breadth First Search starting from your college i.e. "<<root<<": "<<endl;
        while (!q.empty()){
            string node = q.front();
            q.pop();
            cout<<node<<" -> ";

            for (auto it:adj_list[node]){
                if (!visited[it]){
                    visited[it] = true;
                    q.push(it);
                }
            }
        }
        cout<<endl;
    }
};

int main(){
    Graph g;
    g.addedge("PICT", "Katraj Dairy");
    g.addedge("PICT", "Crazy Cheesy Cafe");
    g.addedge("Cosmos Bank", "PICT");
    g.addedge("Cosmos Bank", "Ambegaon");
    g.addedge("PICT", "Rajmudra Society");
    g.addedge("Mumbai - Pune Highway", "Pune - Satara Highway");
    g.addedge("Rajiv Gandhi Zoo", "Ambegaon");
    g.display_graph();
    g.BFS("PICT");
}