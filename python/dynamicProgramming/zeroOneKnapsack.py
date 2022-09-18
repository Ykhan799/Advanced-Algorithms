# Given a list of N items, and a backpack with a
# limited capacity, return the maximum total profit that 
# can be contained in the backpack. The i-th item's profit
# is profit[i] and it's weight is weight[i]. Assume you can
# only add each item to the bag at most one time. 

# Brute force Solution
# Time: O(2^n), Space: O(n)
# Where n is the number of items.
def dfs(profit, weight, capacity):
    return dfsHelper(0, profit, weight, capacity)

def dfsHelper(i, profit, weight, capacity):
    if i == len(profit):
        return 0

    maxProfit = dfsHelper(i + 1, profit, weight, capacity)
    newCap = capacity - weight[i]
    if newCap >= 0:
        p = profit[i] + dfsHelper(i + 1, profit, weight, newCap)
        maxProfit = max(maxProfit, p)
    return maxProfit


# Memoization Solution
# Time: O(n * m), Space: O(n * m)
# Where n is the number of items & m is the capacity.
def memoization(profit, weight, capacity):
    # A 2d array, with N rows and M colums
    N, M = len(profit), capacity
    cache = [[-1] * (M + 1) for _ in range(N)]
    return memoHelper(0, profit, weight, capacity, cache)

def memoHelper(i, profit, weight, capacity, cache):
    if i == len(profit) or capacity < 0:
        return 0
    if cache[i][capacity] != -1:
        return cache[i][capacity]

    # Skip item i
    cache[i][capacity] = dfsHelper(i + 1, profit, weight, capacity)
    
    # Include item i
    newCap = capacity - weight[i]
    p = profit[i] + dfsHelper(i + 1, profit, weight, newCap)
    
    # Return the maximum
    cache[i][capacity] = max(cache[i][capacity], p)
    return cache[i][capacity]


# Memoization Solution
# Time: O(n * m), Space: O(n * m)
# Where n is the number of items & m is the capacity.
def dp(profit, weight, capacity):
    N, M = len(profit), capacity
    dp = [[0] * (M + 1) for _ in range(N)]

    # Fill the first column and row to reduce edge cases
    for i in range(N):
        dp[i][0] = 0
    for c in range(M + 1):
        if weight[0] <= c:
            dp[0][c] = profit[0] 

    for i in range(1, N):
        for c in range(1, M + 1):
            skip = dp[i-1][c]
            include = 0
            if c - weight[i] >= 0:
                include = profit[i] + dp[i-1][c - weight[i]]
            dp[i][c] = max(include, skip)
    return dp[N-1][M]


profit = [4, 4, 7, 1]
weight = [5, 2, 3, 1]
capacity = 8

# Result should be 12
print(dfs(profit, weight, capacity))
print(memoization(profit, weight, capacity))
print(dp(profit, weight, capacity))