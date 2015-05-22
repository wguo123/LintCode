// Time:  O(n^2)
// Space: O(n^2)

class Solution {
public:
    /**
     * @param values: a vector of integers
     * @return: a boolean which equals to true if the first player will win
     */
    bool firstWillWin(vector<int> &values) {
        // Even number case;
        if (values.size() % 2 == 0) {
            if (firstWinEvenCoins(values)) {
                return true;
            }
        }
        
        // P[i][j] = max(values[i] + min(P[i + 2][j], P[i + 1][j - 1]),
        //               values[j] + min(P[i + 1][j - 1], P[i][j - 2]))
        vector<vector<int>> P(values.size(), vector<int>(values.size(), 0));
        int sum = 0;
        for (int i = 0; i < values.size(); ++i) {
            sum += values[i];
            for (int m = 0, n = i; n < values.size(); ++m, ++n) {
                int a = m + 2 <= values.size() - 1 ? P[m + 2][n] : 0;
                int b = m + 1 <= values.size() - 1  && n - 1 >= 0 ? P[m + 1][n - 1] : 0;
                int c = n - 2 >= 0 ? P[m][n - 2] : 0;
                P[m][n] = max(values[m] + min(a, b),
                              values[n] + min(b, c));
            }
        }
        return P[0][values.size() - 1] > sum - P[0][values.size() - 1];
    }
    
    // Time: O(n), Space: O(1)
    // Odd / even numbered strategy for even numbered coins
    bool firstWinEvenCoins(const vector<int>& values) {
        int sum = 0;
        int odd_sum = 0;
        int even_sum = 0;
        for (int i = 0; i < values.size(); ++i) {
            sum += values[i];
            if (i % 2 == 0) {
                odd_sum += values[i];
            } else {
                even_sum += values[i];
            }
        }
        
        return odd_sum != even_sum;
    }
};