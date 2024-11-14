#include <iostream>
#include <vector>
using namespace std;

void printDistances(int V, vector<int> dist){
    cout << "\nVertex \t Distance From Source" << endl;
    for(int i = 0; i < V; i++){
        // condition to check if distance is INT_MAX print infinite else convert int to string and print
        cout << V << " \t " << (dist[i] == INT_MAX ? "Infinite" : to_string(dist[i])) << endl;
    }
}

void bellmanFord(int V, int n_edges, vector<vector<int> > &edges, int source){
    vector<int> dist(V,INT_MAX);  // initialize the vector with INT_MAX
    dist[source] = 0;  // initialize source, in this code 0, with 0

    // relaxation cycle for v-1 cycles
    for(int i = 0; i < V-1; i++){
        for(int j = 0;j < n_edges; j++){
            int u = edges[j][0] - 1;  // indexing the input edge from 0 ( at the moment starts with 1)
            int v = edges[j][1] - 1;  // indexing the input edge from 0
            int weight = edges[j][2];  // edge weight

            // the first vertex should not be infinite + the condition
            if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u]+weight;  // update dist of 2nd vertex
            }
        }
    }

    // check for negative cycle
    bool negativeCycle = false;
    // one more cycle after v-1 iterations
    // represents the v iteration
    // if any vertex gets updated in this iteration, the graph has negative cycle
    for(int j = 0; j < n_edges; j++){
        int u = edges[j][0] - 1;
        int v = edges[j][1] - 1;
        int weight = edges[j][2];

        if(dist[u] != INT_MAX && dist[v] > dist[u] + weight){
            negativeCycle = true;  //  graph has negative cycle
            break;
        } 
    }
    // end the function if it has negative cycle
    if(negativeCycle){
        cout << "\nNegative Cycle Found.\nNO MEANINGFUL SHORTEST PATH WILL BE FOUND" << endl;
        return;
    } 
    // print distance if it has no negative cyclef
    printDistances(V, dist);
}

int main(){
    int v;
    cout << "Enter number of vertices in the graph: ";
    cin >> v;

    int e;
    cout << "Enter number of edges in the graph: ";
    cin >> e;

    // vector<vector<int>>(num_row, vector<int> (num_col, 0)) initializes a 2D vector with num_row rows and num_col columns, where each element is set to 0. 
    vector<vector<int> > edges(e, (vector<int>(3,0)));
    cout << "\nEnter edges in format(vertex1 vertex2 edgeWeight): " << endl;
    for(int i = 0; i < e; i++){
        cout << "Enter for edge " << i+1 << " : ";
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    bellmanFord(v,e,edges, 0);
}