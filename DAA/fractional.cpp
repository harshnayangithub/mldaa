#include <iostream>
#include <vector>
using namespace std;

// convert int type of profit and wt vectors to float
void knapsack(vector<int> &wt, vector<int> &profit, int n, int maxWeight){
    vector<pair<float, pair<int,int> > > v;
    // v.first -> profit/weight ratio
    // v.second.first -> profit
    // v.second.second -> weight

    for(int i = 0; i < n; i++){
        float pw_ratio = (float)profit[i]/wt[i];
        v.push_back(make_pair(pw_ratio,make_pair(profit[i],wt[i])));
        // v.push_back({pw_ratio,{profit[i],wt[i]}});
    }

    // sorting in descending order
    // rbegin and rend are reverse iterators - starting from end of the vector to the start
    sort(v.rbegin(), v.rend());

    cout << endl;
    cout << "--------Data in descending order of P/W ratio-----------\n" << endl;
    cout << "Profit:\t";
    for(int i = 0; i < n; i++){
        cout << v[i].second.first << "\t";
    }
    cout << endl;

    cout << "Weight:\t";
    for(int i = 0; i < n; i++){
        cout << v[i].second.second << "\t";
    }
    cout << endl;

    cout << "P/W Ratio:\t";
    for(int i = 0; i < n; i++){
        cout << v[i].first << "\t";
    }
    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    // to calculate final profit of knapsack
    double finalProfit = 0;
    int currentWeight = maxWeight;

    vector<pair<int, int> > knapsackInclude;

    for(int i = 0; i < n; i++){
        if(currentWeight > 0 && v[i].second.second <= currentWeight){
            cout << "Weight Taken: " << v[i].second.second << endl;
            cout << "Profit Added: " << v[i].second.first << endl;
            cout << "-----------------" << endl;
            knapsackInclude.push_back(make_pair(v[i].second.second, v[i].second.first));
            currentWeight -= v[i].second.second;
            finalProfit += v[i].second.first;
        }
        else if(currentWeight > 0 && v[i].second.second > currentWeight){
            // fractional conditional of knapsack
            // Take ratio of the remaining part -> remaining part * remaining weight
            // that will be new profit for the remaining part
            cout << "Weight Taken: " << v[i].second.second << endl;
            // fraction profit = p/w * remaining weight = p * (remaining weight/total weight of that object)
            double fractionalProfit = v[i].first * currentWeight;
            cout << "Profit Added: " << v[i].second.first << endl;
            cout << "-----------------" << endl;
            knapsackInclude.push_back(make_pair(fractionalProfit, currentWeight));
            finalProfit += fractionalProfit;
            currentWeight = 0;
        }
    }

    cout << endl;
    cout << "----------------------Items included in Knapsack-------------------------" << endl;
    cout << "Profit:   " ;
    for(int i = 0; i < n; i++){
        cout << knapsackInclude[i].first << "\t";
    }
    cout << endl;
    cout << "Weight:   " ;
    for(int i = 0; i < n; i++){
        cout << knapsackInclude[i].second << "\t";
    }
    cout << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Maximum Profit obtained: " << finalProfit << endl;

}

int main(){
    cout << "Enter number of items in knapsack: ";
    int n;
    cin >> n;

    cout << "Enter maximum capacity of knapsack: ";
    int w;
    cin >> w;

    vector<int> weight, profit;

    cout << "Enter profits of all items(one by one): " << endl;
    for(int i = 0; i < n; i++){
        int p;
        cout << "Enter profit of " << i+1 << " item: "; 
        cin >> p;
        profit.push_back(p);
    }
    cout << endl;

    cout << "Enter weights of all items(one by one): " << endl;
    for(int i = 0; i < n; i++){
        int wt;
        cout << "Enter weight of " << i+1 << " item: "; 
        cin >> wt;
        weight.push_back(wt);
    }
    cout << endl;

    cout << "------------Given Data--------------------" << endl;
    cout << "Profit:\t";
    // can also use 
    // for(auto it:profit)
    //     cout << it << "\t";
    for(int i = 0; i < n; i++)  {
        cout << profit[i] << "\t";
    }
    cout << endl;

    for(int i = 0; i < n; i++){
        cout << weight[i] << "\t";
    }
    cout << endl;

    cout << "-----Fractional Knapsack maximizing the profit-----" << endl;
    knapsack(weight, profit, n, w);

    return 0;
}