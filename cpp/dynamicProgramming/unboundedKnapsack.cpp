#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>

using std::vector;
using std::unordered_map;
using std::max;
using namespace std;

// Given a list of N items, and a backpack with a
// limited capacity, return the maximum total profit that 
// can be contained in the backpack. The i-th item's profit
// is profit[i] and it's weight is weight[i]. Assume you can
// have an unlimited number of each item available. 


// Brute force Solution
// Time: O(2^m), Space: O(m)
// Where m is the capacity.
int dfs(vector<int>& profit, vector<int>& weight, int capacity) {
    return dfsHelper(0, profit, weight, capacity);
}

int dfsHelper(int i, vector<int>& profit, vector<int>& weight, int capacity) {
    if (i == profit.size()) {
        return 0;
    }

    // Skip item i
    int maxProfit = dfsHelper(i + 1, profit, weight, capacity);

    // Include item i
    int newCap = capacity - weight[i];
    if (newCap >= 0) {
        int p = profit[i] + dfsHelper(i, profit, weight, newCap);
        // Compute the max
        maxProfit = max(maxProfit, p);
    }
    return maxProfit;
} 

// Memoization Solution
// Time: O(n * m), Space: O(n * m)
// Where n is the number of items & m is the capacity.
int memoization(vector<int>& profit, vector<int>& weight, int capacity) {
    // A 2d array, with N rows and M + 1 columns, init with -1's
    int N = profit.size(), M = capacity;
    vector<vector<int>> cache(N, vector<int>(M + 1, -1));
    return memoHelper(0, profit, weight, capacity, cache);
}

int memoHelper(int i, vector<int>& profit, vector<int>& weight, 
    int capacity, vector<vector<int>>& cache) {
    if (i == profit.size()) {
        return 0;
    }
    if (cache[i][capacity] != -1) {
        return cache[i][capacity];
    }

    // Skip item i
    cache[i][capacity] = memoHelper(i + 1, profit, weight, capacity, cache);

    // Include item i
    int newCap = capacity - weight[i];
    if (newCap >= 0) {
        int p = profit[i] + memoHelper(i, profit, weight, newCap, cache);
        // Compute the max
        cache[i][capacity] = max(cache[i][capacity], p);
    }
    return cache[i][capacity];
} 


// Dynamic Programming Solution
// Time: O(n * m), Space: O(n * m)
// Where n is the number of items & m is the capacity.
int dp(vector<int>& profit, vector<int>& weight, int capacity) {
    int N = profit.size(), M = capacity;
    vector<vector<int>> dp(N, vector<int>(M + 1, 0));

    // Fill the first column and row to reduce edge cases
    for (int i = 0; i < N; i++) {
        dp[i][0] = 0;
    }
    for (int c = 0; c <= M; c++) {
        if (weight[0] <= c) {
            dp[0][c] = (c / weight[0]) * profit[0];
        } 
    }

    for (int i = 1; i < N; i++) {
        for (int c = 1; c <= M; c++) {
            int skip = dp[i-1][c];
            int include = 0;
            if (c - weight[i] >= 0) {
                include = profit[i] + dp[i][c - weight[i]];
            }
            dp[i][c] = max(include, skip);
        }
    }
    return dp[N-1][M];
}


// Memory optimized Dynamic Programming Solution
// Time: O(n * m), Space: O(m)
int optimizedDp(vector<int>& profit, vector<int>& weight, int capacity) {
    int N = profit.size(), M = capacity;
    vector<int> dp(M + 1, 0);

    for (int i = 1; i < N; i++) {
        vector<int> curRow(M + 1, 0);
        for (int c = 1; c <= M; c++) {
            int skip = dp[c];
            int include = 0;
            if (c - weight[i] >= 0) {
                include = profit[i] + curRow[c - weight[i]];
            }
            curRow[c] = max(include, skip);
        }
        dp = curRow;
    }
    return dp[M];
}

int main() {
    vector<int> p = {4, 4, 7, 1};
    vector<int> w = {4, 4, 7, 1};
    int c = 8;

    cout << dfs(p, w, c) << endl;
    cout << memoization(p, w, c) << endl;
    cout << dp(p, w, c) << endl;
    cout << optimizedDp(p, w, c) << endl;
}