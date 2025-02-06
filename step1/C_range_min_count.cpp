#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
#define int long long
vector<int> A;

struct segtree {
    int size;
    vector<pair<int, int>> mins; //{minimum value, count of min}

    void build(vector<int>& nums) {
        size = 1;
        while (size < nums.size()) size *= 2;
        mins.assign(2 * size, {1e15, 0});
        build(nums, 0, 0, size);
    }

    void build(vector<int>& nums, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < nums.size()) {
                mins[x] = {nums[lx], 1};
            }
        } else {
            int m = (lx + rx) / 2;
            build(nums, 2 * x + 1, lx, m);
            build(nums, 2 * x + 2, m, rx);
            merge_nodes(x);
        }
    }

    void merge_nodes(int x) {
        auto left = mins[2 * x + 1];
        auto right = mins[2 * x + 2];
        if (left.first < right.first) {
            mins[x] = left;
        } else if (right.first < left.first) {
            mins[x] = right;
        } else {
            mins[x] = {left.first, left.second + right.second};
        }
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            mins[x] = {v, 1};
        } else {
            int m = (lx + rx) / 2;
            if (i < m) {
                set(i, v, 2*x+1, lx, m);
            } else {
                set(i, v, 2*x+2, m, rx);
            }
            merge_nodes(x);
        }
    }

    pair<int, int> min_q(int l, int r) {
        return min_q(l, r, 0, 0, size);
    }

    pair<int, int> min_q(int l, int r, int x, int lx, int rx) {
        if (r <= lx || l >= rx) return {1e15, 0}; // Out of range
        if (lx >= l && rx <= r) return mins[x];   // Inside range
        int m = (lx + rx) / 2;
        auto left = min_q(l, r, 2*x+1, lx, m);
        auto right = min_q(l, r, 2*x+2, m, rx);
        if (left.first < right.first) return left;
        if (right.first < left.first) return right;
        return {left.first, left.second + right.second};
    }

    pair<int, int> cnt_min_q(int l, int r) {
        return min_q(l, r);
    }
};

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; 
    cin >> n >> m;
    A.resize(n);
    for(int i = 0; i < n; i++)
        cin >> A[i];

    segtree st;
    st.build(A);

    while(m--) {
        int q; 
        cin >> q;
        if(q == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r; 
            cin >> l >> r;
            auto mini = st.cnt_min_q(l, r);
             
            cout << mini.first << " " << mini.second << "\n";
        }
    }
}