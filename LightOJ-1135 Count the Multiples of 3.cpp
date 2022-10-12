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

struct nodeData {
    int zero = 0, one = 0, two = 0, lazy = 0;
};

class solution{
private:
    void build(int node, int le, int ri, vector < nodeData >& treeData){
        if ( le == ri ){
            treeData [ node ].zero = 1;
            return;
        }
        int mid = (le+ri)>>1;
        build(node+node, le, mid, treeData);
        build(node+node+1, mid+1, ri, treeData);
        treeData [ node ].zero = treeData [ node + node ].zero + treeData [ node + node + 1 ].zero;
    }
    void push(int node, vector < nodeData >& treeData){
        if ( treeData [ node ].lazy ){
            treeData [ node + node ].lazy += treeData [ node ].lazy;
            treeData [ node + node + 1 ].lazy += treeData [ node ].lazy;
            updateNode(node+node, treeData [ node ].lazy, treeData);
            updateNode(node+node+1, treeData [ node ].lazy, treeData);
            treeData [ node ].lazy = 0;
        }
    }
    void updateNode(int node, int val,  vector < nodeData >& treeData){
        int one = treeData [ node ].one;
        int two = treeData [ node ].two;
        int zero = treeData [ node ].zero;
        if ( val % 3 == 1 ){
            treeData [ node ].zero = one; 
            treeData [ node ].one  = two;
            treeData [ node ].two  = zero;
        }
        else if ( val % 3 == 2 ){
            treeData [ node ].zero = two; 
            treeData [ node ].one  = zero;
            treeData [ node ].two  = one;
        }
    }
    void combine(int node, vector < nodeData >& treeData){
        treeData [ node ].zero = treeData [ node + node ].zero + treeData [ node + node + 1 ].zero;
        treeData [ node ].one = treeData [ node + node ].one + treeData [ node + node + 1 ].one;
        treeData [ node ].two = treeData [ node + node ].two + treeData [ node + node + 1 ].two;
    }
    int query(int node, int l, int r, int le, int ri, vector < nodeData >& treeData){
        if ( le > ri )return 0;
        if ( le == l && ri == r ){
            push(node,treeData);
            return treeData [ node ].zero;
        }
        int mid = (l+r)>>1;
        push(node, treeData);
        int sum = query(node+node, l, mid, le, min(ri,mid), treeData) + query(node+node+1, mid+1, r, max(le,mid+1), ri, treeData);
        combine(node, treeData);
        return sum;
    }
    void update(int node, int l, int r, int le, int ri, vector < nodeData >& treeData){
        if ( le > ri )return;
        if ( le == l && ri == r ){
            push(node, treeData);
            treeData [ node ].lazy++;
            updateNode(node, 1, treeData);
            return;
        }
        int mid = (l+r)>>1;
        push(node, treeData);
        update(node+node, l, mid, le, min(ri,mid), treeData);
        update(node+node+1, mid+1,r, max(le,mid+1), ri, treeData);
        combine(node, treeData);
    }
public:
    void brainfuck(){
        int n, q;
        cin>>n>>q;
        vector < nodeData > treeData ( n * 4 );
        build(1,0, n-1, treeData );
        cout<<"Case "<<++cases<<":\n";
        while( q-- ){
            int type, le, ri;
            cin>>type>>le>>ri;
            if ( !type ) update(1,0,n-1, le,ri, treeData);
            else cout<<query(1,0,n-1, le,ri,treeData)<<"\n";
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

