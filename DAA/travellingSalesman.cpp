#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 4  // 4 cities
#define INF INT_MAX

// Represents each node in the search tree
struct Node
{
    vector<pair<int, int> > path;  // stores the path taken so far as a lost of city-to-city edges
    int matrix_reduced[N][N];  // stores a reduced cost matrix
    int cost; // represents the cost of reaching this node
    int vertex;  // stores current city reprented by the node
    int level;  // tracks how many cities have been visited so far
};

// function for creating a node
// helps create a new node based on given matrix and path
Node *newNode(int matrix_parent[N][N], vector<pair<int, int> > const &path, int level, int i, int j)
{
    Node* node = new Node;
    node->path = path;  // path vector assigned to node

    if( level != 0){
        node->path.push_back(make_pair(i,j));
    }

     // copies the contents of the matrix_parent into the new node's matrix_reduced
    // memcpy(node->matrix_reduced, matrix_parent, sizeof(node->matrix_reduced));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            node->matrix_reduced[i][j] = matrix_parent[i][j];
        }
    }

    for(int k = 0; level!=0 && k < N; k++){
        node->matrix_reduced[i][k] = INF;
        node->matrix_reduced[k][j] = INF;
    }

    node->matrix_reduced[j][0] = INF;
    node->level = level;
    node->vertex = j;

    return node;   
}

void rowreduction(int matrix_reduced[N][N], int row[N])
{
    // row - used to store the min value found in each row of the matrix

    // initializes the row array to infinity
    fill_n(row, N, INF);
    for(int i = 0; i < N; i++){  // row iterator
        for(int j = 0; j < N; j++){  // column iterator
            if(matrix_reduced[i][j] < row[i]){
                row[i] = matrix_reduced[i][j];
            }
        }
    }

    //subtract min value of each row from all elements in that row
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(matrix_reduced[i][j] != INF && row[i] != INF){
                matrix_reduced[i][j] -= row[i];
            }
        }
    }
}

void colreduction(int matrix_reduced[N][N], int col[N])
{
    // col - used to store the min value found in each col of the matrix

    // initializes the col array to infinity
    fill_n(col, N, INF);
    for(int i = 0; i < N; i++){  // row iterator
        for(int j = 0; j < N; j++){  // column iterator
            if(matrix_reduced[i][j] < col[i]){
                col[i] = matrix_reduced[i][j];
            }
        }
    }

    //subtract min value of each col from all elements in that col
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(matrix_reduced[i][j] != INF && col[i] != INF){
                matrix_reduced[i][j] -= col[i];
            }
        }
    }
}

// function to print the matrix
void printMatrix(int matrix_reduced[N][N]){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (matrix_reduced[i][j] == INF){
                cout<<"INF"<<" ";
            }else{
                cout<<matrix_reduced[i][j]<<" ";
            }
        }
        cout<<"\n";
    }

}

int costCal(int matrix_reduced[N][N])
{
    int cost = 0;
    
    // An integer array row[N] is created to store the minimum values found in each row during the row reduction step.
    int row[N];
    rowreduction(matrix_reduced, row);

    // An integer array col[N] is created to store the minimum values found in each col during the col reduction step.
    int col[N];
    colreduction(matrix_reduced,col);

    // This step accumulates the total cost from both the row and column reductions
    for(int i = 0; i < N; i++){
        cost += (row[i] != INT_MAX) ? row[i] : 0;
        cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    cout << "\nReduced Matrix: \n" << endl;
    printMatrix(matrix_reduced);

    return cost;
}

void pathTaken(vector<pair<int, int> > const &list){
    cout << "Path Taken : " << endl;
    cout << endl;
    for(int i = 0; (unsigned)i < list.size(); i++){
        cout << list[i].first + 1 << "->" << list[i].second + 1 << endl;
    }
}

struct comp{
    // custom comparator
    // overloaded function call operator
    // operator() allows objects of comp struct to behave like a function
    bool operator()(const Node* lhs, const Node* rhs) const{
        return lhs->cost > rhs->cost;  // This return value will dictate the order in which elements are arranged in the priority queue
    }
};

int TSP(int costMatrix[N][N])
{
    // priority_queue<...> pq;
    // priority_queue(T, Container, compare);
    // T - Type of elements stored in the queue
    // container - used to store elements of queue
    // compare - comparator used to order elements
    priority_queue<Node*, vector<Node*>, comp > pq;

    // empty vector of pairs representing current path 
    vector<pair< int, int> > v;

    //starting point for TSP
    // initially it has no path
    Node* root = newNode(costMatrix, v, 0, -1, 0);

    root->cost = costCal(root->matrix_reduced);

    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();

        int i = min->vertex;

        if(min->level==N-1){
            min->path.push_back(make_pair(i,0));
            pathTaken(min->path);
            return min->cost;
        }

        for(int j = 0; j < N; j++)
        {
            if(min->matrix_reduced[i][j] != INF)
            {
                Node* child = newNode(min->matrix_reduced, min->path, min->level+1, i, j);
                child->cost = costCal(child->matrix_reduced) + min->cost + min->matrix_reduced[i][j];
                pq.push(child);
            }
        }
    }
    return 0;
}

int main(){
    int costMatrix[N][N], result;

    cout << "Enter the cost matrix: " << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i==j){
                costMatrix[i][j] = INF;
            }
            else{
                cout << "Enter the cost of edge " << i+1 << "->" << j+1 << " : ";
                cin >> costMatrix[i][j];
            }
        }
    }

    result = TSP(costMatrix);
    cout << "\nTotal Cost :: " << result << endl;
    return 0;
}