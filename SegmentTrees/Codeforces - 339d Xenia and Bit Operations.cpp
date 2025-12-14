#include <bits/stdc++.h>
using namespace std;

class SGTree {
    public:
    vector<int> seg;
    
    public: 
    SGTree(int n) {
        seg.resize(4*n+1);
    }
    void build(int ind, int l, int r, int arr[], int op) {
        if(l == r) {
            seg[ind] = arr[l];
            return;
        }
        
        int mid = (l + r) >> 1;
        build(2*ind+1, l, mid, arr, !op);
        build(2*ind+2, mid+1, r, arr, !op);
        
        if(op) seg[ind] = seg[2*ind+1] | seg[2*ind+2];
        else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2];
    }
    
    void update(int ind, int low, int high, int i, int val, int op) {
        if(low == high) {
            seg[ind] = val;    //this ingle index will be updated in segment tree
            return;
        }
        int mid = (low + high) >> 1;
        if(i <= mid) update(2*ind+1, low, mid, i, val, !op);
        else update(2*ind+2, mid+1, high, i, val, !op);
        
        if(op) seg[ind] = seg[2*ind+1] | seg[2*ind+2];
        else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    int size = 1 << n;
    SGTree st(size);
    
    int arr[size];
    
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    if(n%2) st.build(0, 0, size-1, arr, 1);
    else st.build(0, 0, size-1, arr, 0);
    
    while(m--) {
        int i, val;
        cin >> i >> val;
        i--;   //queries are 1-based
        int op = 0;
        if(n%2) op = 1;
        st.update(0, 0, size-1, i, val, op);
        cout << st.seg[0] << endl;
    }
}

int main() {
	// your code goes here
    // int n;
    // cin >> n;
    // int arr[n];
    // SGTree s(n);
    
    // for(int i = 0; i < n; i++) cin >> arr[i];
    // s.build(0, 0, n-1, arr);
    
    // int t;
    // cin >> t;
    // while(t--) {
    //     int type;
    //     cin >> type;
    //     if(type == 1) {
    //         int i, val;
    //         cin >> i >> val;
    //         s.update(0, 0, n-1, i, val);
    //         arr[i] = val;
    //     } else {
    //         int low, high;
    //         cin >> low >> high;
    //         int mini = s.query(0, 0, n-1, low, high);
    //         cout << mini << endl;
    //     }
    // }
    solve();
    return 0;
}
