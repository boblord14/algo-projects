//
// Created by ncabr on 7/16/26.
//
#include <iostream>
#include <vector>

using namespace std;

static vector<int> get_longest_subsequence_three(
        const vector<int>& a,
        const vector<int>& b,
        const vector<int>& c)
{
    const size_t p = a.size();
    const size_t q = b.size();
    const size_t r = c.size();

    // DP table
    vector<vector<vector<int>>> dp(
        p + 1,
        vector<vector<int>>(q + 1,
        vector<int>(r + 1, 0)));

    // Fill DP table
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= q; j++) {
            for (int k = 1; k <= r; k++) {

                if (a[i - 1] == b[j - 1] &&
                    a[i - 1] == c[k - 1]) {

                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                }
                else {
                    int option_one = dp[i - 1][j][k];
                    int option_two = dp[i][j - 1][k];
                    int option_three = dp[i][j][k - 1];

                    dp[i][j][k] = max(option_one, max(option_two, option_three));
                }
            }
        }
    }

    // Reconstruct the subsequence
    size_t i = p;
    size_t j = q;
    size_t k = r;

    const int length = dp[p][q][r];
    vector<int> answer(length);

    int index = length - 1;

    while (i > 0 && j > 0 && k > 0) {

        if (a[i - 1] == b[j - 1] &&
            a[i - 1] == c[k - 1]) {

            answer[index] = a[i - 1];
            index--;

            i--;
            j--;
            k--;
            }
        else if (dp[i][j][k - 1] == dp[i][j][k])
            k--;
        else if (dp[i][j - 1][k] == dp[i][j][k])
            j--;
        else
            i--;
    }

    return answer;
}

int main() {

    int p, q, r;
    cin >> p >> q >> r;

    vector<int> a(p);
    vector<int> b(q);
    vector<int> c(r);

    for (int i = 0; i < p; i++)
        cin >> a[i];

    for (int i = 0; i < q; i++)
        cin >> b[i];

    for (int i = 0; i < r; i++)
        cin >> c[i];

    const vector<int> subsequence = get_longest_subsequence_three(a, b, c);

    cout << subsequence.size() << endl;

    for (const int x : subsequence)
        cout << x << " ";

    cout << endl;

    return 0;
}