#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
vector<int> A;

struct segtree {
    int size;
    vector<long long> mins;

    void build(vector<int>& nums) {
        size = 1;
        while (size < nums.size()) size *= 2;
        mins.assign(2 * size, 1e15);
        build(nums, 0, 0, size);
    }

    void build(vector<int>& nums, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < nums.size()) {
                mins[x] = nums[lx];
            }
        } else {
            int m = (lx + rx) / 2;
            build(nums, 2 * x + 1, lx, m);
            build(nums, 2 * x + 2, m, rx);
            mins[x] = min(mins[2 * x + 1], mins[2 * x + 2]);
        }
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            mins[x] = v;
        } else {
            int m = (lx + rx) / 2;
            if (i < m) {
                set(i, v, 2*x+1, lx, m);
            } else {
                set(i, v, 2*x+2, m, rx);
            }
            mins[x] = min(mins[2*x+1], mins[2*x+2]);
        }
    }

    long long min_q(int l, int r) {
        return min_q(l, r, 0, 0, size);
    }

    long long min_q(int l, int r, int x, int lx, int rx) {
        if (r <= lx) return 1e15;
        if (l >= rx) return 1e15;
        if (lx >= l && rx <= r) return mins[x];
        int m = (lx + rx) / 2;
        long long m1 = min_q(l, r, 2*x+1, lx, m);
        long long m2 = min_q(l, r, 2*x+2, m, rx);
        return min(m1 , m2);
    }
};


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, m; cin >> n >> m;
    A.resize(n);
    for(int i=0; i<n; i++)
        cin >> A[i];
    segtree st;
    st.build(A);
    while(m--) {
        int q; cin >> q;
        if(q == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }else {
            int l, r; 
            cin >> l >> r;
            cout << st.min_q(l, r) << "\n";
        }
    }
}