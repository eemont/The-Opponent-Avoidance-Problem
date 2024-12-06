#include <iostream>
#include <vector>

using namespace std;

//Define countPaths function
int countPaths(vector<vector<char>>& grid) {

    int rows = grid.size(); 
    int cols = grid[0].size();

    // Create a 2D array to store the number of paths to each cell
    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    // Initialize the top-left cell
    dp[0][0] = (grid[0][0] == '.') ? 1 : 0;

    // Initialize the first row
    for (int col = 1; col < cols; col++) {
        if (grid[0][col] == '.') {
            dp[0][col] = dp[0][col - 1];
        }
    }

    // Initialize the first column
    for (int row = 1; row < rows; row++) {
        if (grid[row][0] == '.') {
            dp[row][0] = dp[row - 1][0];
        }
    }

    // Fill in the DP array
    for (int row = 1; row < rows; row++) {
        for (int col = 1; col < cols; col++) {
            if (grid[row][col] == '.') {
                dp[row][col] = dp[row - 1][col] + dp[row][col - 1];
            }
        }
    }

    // The result is stored in the bottom-right cell
    return dp[rows - 1][cols - 1];
}

int main() {
    int rows, cols; //Declare variables

    cin >> rows >> cols; //Input rows and columns

    vector<vector<char>> grid(rows, vector<char>(cols)); //Define a vector

    //Iterate through grid
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cin >> grid[row][col]; //Input the grid values
        }
    }

    int result = countPaths(grid); //Function call

    cout << result << endl; //Display the result
    cout << result << endl; //Display the result
    cout << result << endl; //Display the result
    cout << result << endl; //Display the result

    /*
    ......X.X
    
    */
    

    return 0;
}