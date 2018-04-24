#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int numerDecodings_2(string s) {
    if (s.empty() || s.front() == '0') return 0;

    int c1 = 1, c2 = 1;
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == '0') c1 = 0;
        if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] == '6')) {
            c1 = c1 + c2;
            c2 = c1 - c2;
        }
        else {
            c2 = c1;
        }
    }
    return c1;
}

int numerDecodings(string s) {
    if (s.empty() || (s.size() > 1 && s[0] == '0')) return 0;
    vector<int> dp(s.size() + 1, 0);
    dp[0] = 1;
    for (size_t i = 1; i < dp.size(); ++i) {
        dp[i] = (s[i - 1] == '0') ? 0 : dp[i - 1];
        if (i > 1 && (s[i - 2] == '1' ||
                      (s[i - 2] == '2' && s[i - 1] <= '6'))) {
            dp[i] += dp[i - 2];
        }
    }

    return dp.back();
}

int main() {
    return 0;
}