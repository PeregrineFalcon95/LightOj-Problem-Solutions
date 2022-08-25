/*
Ref: https://lightoj.com/problem/array-queries
Category: Segment Tree
*/
#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
struct Data {
    int sum = 0, prefix = 0, suffix = 0, ans = 0;
};
int t, cases;
class segmentTree{
private:
    void build(int node, int le, int ri, vector <int>& money, vector <int>& treeData){
        if ( le == ri )treeData [ node ] = money [ le ];
        else {
            int mid = (le+ri)>>1;
            build(node*2, le, mid, money, treeData);
            build(node*2+1, mid+1, ri, money, treeData);
            treeData [ node ] = min(treeData [ node*2 ], treeData [ node*2+1 ]);
        }
    }    
    
    int query(int node, int le, int ri, int lRange, int rRange, vector<int>& treeData){
        if ( lRange > rRange)return 1000000;
        if ( lRange == le && rRange == ri )return treeData [ node ];
        int mid = ( le+ri )>>1;
        return min(query(node*2, le, mid, lRange, min(rRange, mid), treeData), query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, treeData)); 
    }
public:
    void inputAndPerform(){
        int n,q;
        cin>>n>>q;
        vector < int > money( n + 1 ), treeData ( n * 4, 0 );
        for ( int i = 1; i <= n; i++ )cin>>money [ i ];
        build(1,1,n, money,treeData);
        cout<<"Case "<<++cases<<":\n";
        
        while( q-- ){
            //Range Query
            int le, ri;
            cin>>le>>ri;
            cout<<query(1,1,n, le, ri, treeData)<<"\n";
        }
    }
};
int main(){
    segmentTree obj;
    cin>>t;
    while( t-- )
        obj.inputAndPerform();
    return 0;
}