#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        string s;
        cin >> s;

        int cuts = 0;
        int max_depth = 0;
        int ans = 0;
        int current_depth = 0;
        
        vector<int> st;
        st.reserve(n);

        for (char c : s) {
            if (c == '1') {
                cuts++;
                if (current_depth + 1 > max_depth) {
                    max_depth = current_depth + 1;
                    ans = cuts;
                }
                st.push_back(current_depth + 1);
                current_depth++;
            } else {
                if (!st.empty()) {
                    current_depth = st.back();
                    st.pop_back();
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}