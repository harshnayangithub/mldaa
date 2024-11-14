#include <iostream>
#include <vector>
using namespace std;

int temp[102][1002];

void showSelectedItems(int items, int capacity, vector<int> &wt){
    int i = items;  // number of items
    int j = capacity; // maximum capacity of knapsack

    // while number of items are > 0 and capacity > 0
    while(items > 0 && capacity > 0){
        // if value of the current row and its above row are same
        if(temp[items][capacity] == temp[items-1][capacity]){
            items--; // that object isn't considered as its taken from the above row
        }
        else{
            // if value of current and above row are different
            cout << items << " "; // that item is selected
            capacity = capacity - wt[i-1];  // capacity is reduced by weight of the selected item
            items--; // reduce number of items
        }
    }
    cout << endl;
}

void knapsack(vector<int> &weight, vector<int> &profit, int n, int maxWeight){

    // the 0th row and 0th column is filled with 0s
    for(int i=0; i<=n; i++){
        for(int j=0; j <= maxWeight; j++){
            if(i == 0 || j == 0){
                temp[i][j] = 0;
            }
        }
    }

    //
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= maxWeight; j++){
            // if the weight of item is less than jth column weight value
            if(weight[i-1] <= j){
                // max of (profit[object] + temp[above row][weight of column - weight of object]) & (value of above row of same column) 
                // profit[i-1] is done as indexing of array starts at 0, but the for loop iterator starts at 1
                // weight[i-1]: The weight of item i, also indexed by i-1 in the weight array.
                temp[i][j] = max((profit[i-1] + temp[i-1][j-weight[i-1]]), temp[i-1][j]);
            }
            else{
                // copy value from above row of same column
                temp[i][j] = temp[i-1][j];
            }
        }
    }

    cout << "\nTabulation of 0/1 Knapsack Using Dynamic Programming" << endl;
    for(int i = 0; i <= n; i++){
        for(int w = 0; w <= maxWeight; w++){
            cout << temp[i][w] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Items selected: " << endl;
    showSelectedItems(n,maxWeight,weight);

    cout << "Maximum profit obtained using 0/1 knapsack(DP) is: " << temp[n][maxWeight] << endl;


}

int main(){
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weight;
    vector<int> profit;

    cout << "Enter the weight of items: " << endl;
    for(int i = 0; i < n; i++){
        cout << "Enter weight of " << i+1 << " item: ";
        int x;
        cin >> x;
        weight.push_back(x);
    }
    cout << endl;

    cout << "Enter the profit of items: " << endl;
    for(int i = 0; i < n; i++){
        cout << "Enter profit of " << i+1 << " item: ";
        int x;
        cin >> x;
        profit.push_back(x);
    }
    cout << endl;

    int maxWeight;
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> maxWeight;

    knapsack(weight, profit, n, maxWeight);
    return 0;
}