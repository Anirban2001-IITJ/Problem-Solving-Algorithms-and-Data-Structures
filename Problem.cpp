#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int>& v, int K) {
    int days = 0;
    int N = v.size();
    vector<bool> solved(N, false);

    int remaining = N;

    while (remaining > 0) {
        vector<int> dp(N, 1);
        vector<int> parent(N, -1);

        for (int i = 0; i < N; ++i) {
            if (solved[i]) continue;
            for (int j = 0; j < i; ++j) {
                if (!solved[j] && v[i] != v[j] && abs(v[i] - v[j]) >= K) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        int len = 0, idx = -1;
        for (int i = 0; i < N; ++i) {
            if (!solved[i] && dp[i] > len) {
                len = dp[i];
                idx = i;
            }
        }
      
        int last_val = -1;
        vector<int> seq;
        for (int i = idx; i >= 0; --i) {
            if (!solved[i] && dp[i] == len && (seq.empty() || abs(v[seq.back()] - v[i]) >= K)) {
                seq.push_back(i);
                len--;
            }
        }

        for (int i : seq) {
            if (!solved[i]) {
                solved[i] = true;
                remaining--;
            }
        }

        days++;
    }

    return days;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> v(N);
        for (int i = 0; i < N; ++i)
            cin >> v[i];

        cout << solve(v, K) << endl;
    }
    return 0;
}
