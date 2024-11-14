#include <iostream>
#include <vector>
using namespace std;

void findSubsets(vector<int> &set, int targetSum, vector<int> &currentSubset, int index)
{
    // if targetSum becomes 0 -> sum is found
    if(targetSum == 0){
        cout << endl;
        cout << endl;
        cout << "------------------------------------" << endl;
        cout << "Found Subset with targetted sum : " << endl;
        cout << "------------------------------------" << endl;
        for(int num: currentSubset){
            cout << num << " ";
        }
        cout << endl;
        cout << "-------------------------------------" << endl;
        cout << endl;
        return;
    }

    // we have reached the end of the array or sum becomes negative
    if(index == set.size() || targetSum < 0){
        return;
    }

    cout << "Adding " << set[index] << " to current subset" << endl;
    currentSubset.push_back(set[index]);
    findSubsets(set, targetSum - set[index], currentSubset, index+1);

    cout << "Removing " << set.back() << " from current subset" << endl;
    currentSubset.pop_back();
    cout << endl;

    cout << endl;
    cout << "Started to backtrack" << endl;
    findSubsets(set, targetSum, currentSubset, index+1);
}

int main()
{
    cout << "Enter the size of the array: ";
    int n;
    cin >> n;

    cout << "Enter elements of array: " << endl;
    vector<int> set(n);  // default value set to 0
    for(int i = 0; i < n; i++)
    {
        cout << "Element "<< i+1 << " : ";
        int x;
        cin >> x;
        set[i] = x;
    }

    cout << "Enter target sum: ";
    int targetSum;
    cin >> targetSum;

    vector<int> currentSubset;
    findSubsets(set, targetSum,currentSubset, 0);
    return 0;
}