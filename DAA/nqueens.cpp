#include <iostream>
#include <vector>
using namespace std;

void print_solution(vector<int> &queens){
    int n = queens.size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // if for that row, the column queen is placed in and the iteration column matches, print Q
            if(queens[i] == j){
                cout << "Q ";
            }
            else{
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool is_safe(vector<int> &queens, int row, int col)
{
    for(int i = 0; i < row; i++){
        // no queen is in same column or in same diagonal
        // as queens[i] represent column for that row -> if any col for that row equals column we are checking then we cant place queen in that col
        // 
        if(queens[i] == col || abs(queens[i] - col) == abs(i-row)){
            return false;
        }
    }
    return true;
}

// &count - because we want to change that varible only not it's copy
void solve_recursive(vector<int> &queens, int row, int &count)
{
    // queens vector - gives column position of queen in a row
    int n = queens.size();

    // solution found as queen have been safely placed in all rows
    if(row == n){
        ++count;
        cout << "Solution " << count << " : " << endl;
        print_solution(queens);
        return;
    }

    // recursive case
    for(int col = 0; col < n; col++){     // loop over each column in current row
        // if placing a queen is safe
        // the algorithm never advances to the next row unless the current row’s queen is safely placed.
        // is_safe will return false, and the solve_recursive function will not be called for the next row. Instead, the algorithm:
            // Moves to the next column in the current row to try another position.
            // If no column in the current row is safe, the algorithm backtracks to the previous row.
        if(is_safe(queens, row, col)){
            queens[row] = col;  // temporarily places the queen of that row in that column
            solve_recursive(queens, row+1, count); // calls again with the next row
            // After the recursive call returns, it resets queens[row] = -1 to remove the queen and explore other column placements.
            // algorithm needs to remove the queen from the current row to explore other possible placements in that row. To find other solutions
            queens[row] = -1;  
            // queens[row]= -1 the code allows the next iteration of the for loop to try placing the queen in a different column within the same row.
        }
    }
}

void solve_n_queens(int n){
    // -1 indicates no queen is placed
    // each index in queens corresponds to row on the board
    // value at each index represents column in row where queen is placed
    //  if queens[i] = j, it means that in row i, a queen is placed in column j.
    vector<int> queens(n,-1);

    // count is number of solutions found
    int count = 0;

    // start from 0th row
    solve_recursive(queens,0,count);
    if(count == 0){
        cout << "No solutions found" << endl;
    }
}

int main(){
    int n;
    cout << "Enter number of queens (n): ";
    cin >> n;

    solve_n_queens(n);
    return 0;
}