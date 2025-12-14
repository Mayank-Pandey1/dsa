#include <bits/stdc++.h>
using namespace std;

class SGTree {
    vector<int> seg;
    
    public: 
    SGTree(int n) {
        seg.resize(4*n+1);
    }
    void build(int ind, int l, int r, int arr[]) {
        if(l == r) {
            seg[ind] = arr[l];
            return;
        }
        
        int mid = (l + r) >> 1;
        build(2*ind+1, l, mid, arr);
        build(2*ind+2, mid+1, r, arr);
        
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }
    
    int query(int ind, int l, int r, int low, int high) {
        
        //no overlap
        if(high < l || low > r) return INT_MAX;
        
        //complete overlap - is the node segment[l->r] completely inside query range[low -> high]
        if(low <= l && high >= r) {
            return seg[ind];
        }
        
        //partial overlap
        int mid = (l+r) >> 1;
        int left = query(2*ind+1, l, mid, low, high);
        int right = query(2*ind+2, mid+1, r, low, high);
        
        return min(left, right);
    }
    
    void update(int ind, int low, int high, int i, int val) {
        if(low == high) {
            seg[ind] = val;    //this ingle index will be updated in segment tree
            return;
        }
        int mid = (low + high) >> 1;
        if(i <= mid) update(2*ind+1, low, mid, i, val);
        else update(2*ind+2, mid+1, high, i, val);
        
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }
};

int main() {
	// your code goes here
    int n;
    cin >> n;
    int arr[n];
    SGTree s(n);
    
    for(int i = 0; i < n; i++) cin >> arr[i];
    s.build(0, 0, n-1, arr);
    
    int t;
    cin >> t;
    while(t--) {
        int type;
        cin >> type;
        if(type == 1) {
            int i, val;
            cin >> i >> val;
            s.update(0, 0, n-1, i, val);
            arr[i] = val;
        } else {
            int low, high;
            cin >> low >> high;
            int mini = s.query(0, 0, n-1, low, high);
            cout << mini << endl;
        }
    }
}
