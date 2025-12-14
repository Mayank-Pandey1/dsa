#include <bits/stdc++.h>
using namespace std;

struct info {
    int open, close, full;
    info(int _open = 0, int _close = 0, int _full = 0) {
        open = _open;
        close = _close;
        full = _full;
    }
};

void build(int ind, int l, int r, vector<info> &seg, const string &s) {
    if(l == r) {
        seg[ind] = info(s[l] == '(', s[l] == ')', 0);
        return;
    }
    
    int mid = (l+r) >> 1;
    build(2*ind+1, l, mid, seg, s);
    build(2*ind+2, mid+1, r, seg, s);
    
    info left = seg[2*ind+1], right = seg[2*ind+2];
    
    int f = left.full + right.full + min(left.open, right.close);
    int o = left.open + right.open - min(left.open, right.close);
    int c = left.close + right.close - min(left.open, right.close);
    
    seg[ind] = info(o, c, f);
}

info query(int ind, int l, int r, int low, int high, vector<info> &seg) {
    
    //no overlap
    if(high < l || low > r) return info(0, 0, 0);
    
    //complete overlap - node segment is within the query segment
    else if(l >= low && r <= high) {
        return info(seg[ind].open, seg[ind].close, seg[ind].full);
    }
    
    int mid = (l+r) >> 1;
    info left = query(2*ind+1, l, mid, low, high, seg);
    info right = query(2*ind+2, mid+1, r, low, high, seg);
    
    
    int f = left.full + right.full + min(left.open, right.close);
    int o = left.open + right.open - min(left.open, right.close);
    int c = left.close + right.close - min(left.open, right.close);
    
    return info(o, c, f);
}

void solve() {
    string s;
    cin >> s;
    int m;
    cin >> m;
    
    int n = s.size();
    vector<info> seg(4*n);
    
    build(0, 0, n-1, seg, s);
    
    while(m--) {
        int low, high;
        cin >> low >> high;
        low--; high--;
        cout << 2 * query(0, 0, n-1, low, high, seg).full << endl;
    }
}
int main() {
	// your code goes here
    solve();
    return 0;
}
