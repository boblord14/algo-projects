//
// Created by ncabr on 7/16/26.
//
#include <iostream>
#include <vector>

using namespace std;

static void print_parenthesization(
        const int i,
        const int j,
        const vector<vector<int>>& split)
{
    if (i == j) {
        cout << "A" << i;
        return;
    }

    cout << "( ";

    print_parenthesization(i, split[i][j], split);

    cout << " x ";

    print_parenthesization(split[i][j] + 1, j, split);

    cout << " )";
}

int main() {

    int n;
    cin >> n;

    vector<int> dims(n + 1);

    for (int i = 0; i <= n; i++)
        cin >> dims[i];

    vector<vector<long long>> dp(
        n + 1,
        vector<long long>(n + 1, 0));

    vector<vector<int>> split(
        n + 1,
        vector<int>(n + 1, 0));

    for (int length = 2; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            const int j = i + length - 1;

            int k = i;

            dp[i][j] = dp[i][k]
                     + dp[k + 1][j]
                     + static_cast<long long>(dims[i - 1]) * dims[k] * dims[j];

            split[i][j] = k;

            for (k = i + 1; k < j; k++) {

                const long long cost =
                    dp[i][k]
                  + dp[k + 1][j]
                  + static_cast<long long>(dims[i - 1]) * dims[k] * dims[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << dp[1][n] << endl;

    print_parenthesization(1, n, split);

    cout << endl;

    return 0;
}