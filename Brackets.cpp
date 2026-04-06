#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Node structure for the segment tree
struct Node {
    int sum;
    int min_pref;
};

const int MAXN = 30005;
Node tree[4 * MAXN];
string s;

// Build the initial segment tree
void build(int node, int start, int end) {
    if (start == end) {
        if (s[start] == '(') {
            tree[node].sum = 1;
            tree[node].min_pref = 1;
        } else {
            tree[node].sum = -1;
            tree[node].min_pref = -1;
        }
        return;
    }
    
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    // Combine left and right children
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].min_pref = min(tree[2 * node].min_pref, tree[2 * node].sum + tree[2 * node + 1].min_pref);
}

// Point update: flip the bracket at index 'idx'
void update(int node, int start, int end, int idx) {
    if (start == end) {
        if (s[idx] == '(') {
            s[idx] = ')';
            tree[node].sum = -1;
            tree[node].min_pref = -1;
        } else {
            s[idx] = '(';
            tree[node].sum = 1;
            tree[node].min_pref = 1;
        }
        return;
    }
    
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx);
    } else {
        update(2 * node + 1, mid + 1, end, idx);
    }
    
    // Combine left and right children
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].min_pref = min(tree[2 * node].min_pref, tree[2 * node].sum + tree[2 * node + 1].min_pref);
}

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    // Process exactly 10 test cases as stated in the problem
    for (int tc = 1; tc <= 10; ++tc) {
        if (!(cin >> n)) break; // Graceful exit if EOF is reached early
        
        cin >> s;
        
        // Build the segment tree (0-indexed sequence array)
        build(1, 0, n - 1);
        
        cout << "Test " << tc << ":\n";
        
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int k;
            cin >> k;
            if (k == 0) {
                // Check operation: sum must be 0 and minimum prefix sum must be >= 0
                if (tree[1].sum == 0 && tree[1].min_pref >= 0) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            } else {
                // Replacement operation (convert to 0-based index)
                update(1, 0, n - 1, k - 1);
            }
        }
    }
    return 0;
}