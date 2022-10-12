#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long int
#define inf ( int )( 1e9 + 10 )
#define mxs (int)( 1e6 + 10 )
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
//#define md int mid = ( l + r )>>1;
int dx[]={+1,-1,+0,+0};///Four Directions
int dy[]={+0,+0,+1,-1};///Four directions
// int dx [] = {+1,-1,+0,+0,-1,-1,+1,+1};///Eight Directions
// int dy [] = {+0,+0,+1,-1,+1,-1,-1,+1};///Eight Directions
int t, cases;

struct nodeData{
    ll sum = 0, lazy = 0;
};

class solution{
private:
    void pushLazy(int node, int lSize, int rSize, vector < nodeData >& treeData){
        treeData [ node + node ].lazy += treeData [ node ].lazy;
        treeData [ node + node + 1 ].lazy += treeData [ node ].lazy;
        updateNode(node+node, treeData [ node ].lazy, lSize, treeData );
        updateNode(node+node+1, treeData [ node ].lazy, rSize, treeData);
        treeData [ node ].lazy = 0;
    }
    void updateNode(int node, ll val, ll range, vector<nodeData>& treeData){
        treeData [ node ].sum += range * val;
    }
    void combine(int node, vector <  nodeData >& treeData){
        treeData [ node ].sum = treeData [ node + node ].sum + treeData [ node + node + 1 ].sum;
    }
    void update(int node, int l, int r, int le, int ri, ll val, vector < nodeData >& treeData){
        if ( le > ri )return;
        if ( le == l && ri == r ){
            updateNode(node,val,r-l+1,treeData);
            treeData [ node ].lazy += val;
            return;
        }
        int mid = (l+r)>>1;
        pushLazy(node, mid-l+1, r-mid, treeData);
        update(node+node, l,mid, le,min(ri,mid), val, treeData);
        update(node+node+1, mid+1,r, max(le,mid+1),ri, val, treeData);
        combine(node, treeData);
    }
    ll query(int node, int l, int r, int le, int ri, vector < nodeData >& treeData){
        if ( le > ri )return 0;
        if ( le == l && ri == r ){
            int mid = (l+r)>>1;
            pushLazy(node, mid-l+1, r-mid, treeData);
            combine(node,treeData);
            return treeData [ node ].sum;
        }
        int mid = (l+r)>>1;
        pushLazy(node, mid-l+1, r-mid, treeData);
        ll sum = query(node+node, l, mid, le, min(ri, mid), treeData) + query(node+node+1, mid+1, r, max(mid+1,le), ri, treeData);
        combine(node,treeData);
        return sum;
    }
public:
    void brainfuck(){
        int n , q;
        cin>>n>>q;
        vector < nodeData > treeData (n*4);
        cout<<"Case "<<++cases<<":\n";
        while( q-- ){
            int type;
            cin>>type;
            if ( !type ){ //Update
                int le, ri, val;
                cin>>le>>ri>>val;
                update(1,0,n-1,le,ri,val,treeData);
            }
            else { //Query
                int le, ri;
                cin>>le>>ri;
                cout<<query(1,0,n-1,le,ri,treeData)<<"\n";
            }
        }
    }
    
    void clearPreviousData(){
        
    }
};

solution solve;
int main(){
    fast
    cin>>t;
    //t = 1;
    while( t-- )
    {
        solve.clearPreviousData();
        solve.brainfuck();
    }
    return 0;
}

