#include <iostream>
#include <vector>
#include <chrono> // For measuring time
using namespace std;
using namespace std::chrono;

// Function to input the grid
vector<vector<char>> inputGrid()
{
    int r, c;
    cout << "\nEnter the number of rows: \n\n";
    cin >> r;
    cout << "\nEnter the number of columns: \n\n";
    cin >> c;

    vector<vector<char>> grid(r, vector<char>(c));
    cout << "\nEnter the grid row by row (use '.' for passable and 'X' for impassable cells):\n"
         << endl;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> grid[i][j];
        }
    }
    return grid;
}

// Helper function to check if the path is valid
bool isValidPath(const vector<vector<char>> &grid, const vector<int> &path, int r, int c)
{
    int x = 0, y = 0;
    for (int move : path)
    {
        if (move == 0)
            y++; // Move right
        else
            x++; // Move down
        if (x >= r || y >= c || grid[x][y] == 'X')
            return false;
    }
    return (x == r - 1 && y == c - 1);
}

// Exhaustive search function
int exhaustive_search(const vector<vector<char>> &grid)
{
    int r = grid.size();
    int c = grid[0].size();
    int len = r + c - 2;
    int maxPaths = 1 << len; // Total number of binary combinations
    int counter = 0;

    for (int bits = 0; bits < maxPaths; ++bits)
    {
        vector<int> path;
        for (int k = 0; k < len; ++k)
        {
            if ((bits >> k) & 1)
                path.push_back(1); // Down
            else
                path.push_back(0); // Right
        }
        if (isValidPath(grid, path, r, c))
            counter++;
    }
    return counter;
}

// Dynamic programming function
int dynamic_programming(const vector<vector<char>> &grid)
{
    int r = grid.size();
    int c = grid[0].size();
    if (grid[0][0] == 'X' || grid[r - 1][c - 1] == 'X')
        return 0;

    vector<vector<int>> dp(r, vector<int>(c, 0));
    dp[0][0] = 1;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (grid[i][j] == 'X')
                continue;
            if (i > 0)
                dp[i][j] += dp[i - 1][j]; // From above
            if (j > 0)
                dp[i][j] += dp[i][j - 1]; // From left
        }
    }
    return dp[r - 1][c - 1];
}

int main()
{
    // Input the grid
    vector<vector<char>> grid = inputGrid();

    // Measure time for exhaustive search
    auto start_exhaustive = high_resolution_clock::now();
    int exhaustive_result = exhaustive_search(grid);
    auto end_exhaustive = high_resolution_clock::now();
    auto duration_exhaustive = duration_cast<microseconds>(end_exhaustive - start_exhaustive);

    // Display result and time for exhaustive search
    cout << "\nExhaustive Search Result: " << exhaustive_result << endl;
    cout << "Time taken by Exhaustive Search: " << duration_exhaustive.count() << " microseconds\n"
         << endl;

    // Measure time for dynamic programming
    auto start_dp = high_resolution_clock::now();
    int dp_result = dynamic_programming(grid);
    auto end_dp = high_resolution_clock::now();
    auto duration_dp = duration_cast<microseconds>(end_dp - start_dp);

    // Display result and time for dynamic programming
    cout << "Dynamic Programming Result: " << dp_result << endl;
    cout << "Time taken by Dynamic Programming: " << duration_dp.count() << " microseconds\n"
         << endl;

    return 0;
}