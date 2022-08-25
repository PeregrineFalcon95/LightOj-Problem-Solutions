/*
Ref: https://lightoj.com/problem/curious-robin-hood
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
            treeData [ node ] = treeData [ node*2 ] + treeData [ node*2+1 ];
        }
    }    
    void update(int node, int le, int ri, int pos, int val, vector < int >& treeData){
        if ( le == ri ){
            if ( !val ){
                cout<<treeData [ node ]<<"\n";
                treeData [ node ] = 0;
            }
            else treeData [ node ] += val;
        }else {
            int mid = (le+ri)>>1;
            if ( pos <= mid )update(node*2, le, mid, pos, val, treeData);
            else update(node*2+1, mid+1, ri, pos, val, treeData);
            treeData [ node ] = treeData [ node*2 ] + treeData [ node*2+1 ];
        }
    }
    int query(int node, int le, int ri, int lRange, int rRange, vector<int>& treeData){
        if ( lRange > rRange)return 0;
        if ( lRange == le && rRange == ri )return treeData [ node ];
        int mid = ( le+ri )>>1;
        return query(node*2, le, mid, lRange, min(rRange, mid), treeData) + query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, treeData); 
    }
public:
    void inputAndPerform(){
        int n,q;
        cin>>n>>q;
        vector < int > money( n ), treeData ( n * 4, 0 );
        n--;
        for ( int i = 0; i <= n; i++ )cin>>money [ i ];
        build(1,0,n, money,treeData);
        cout<<"Case "<<++cases<<":\n";
        while( q-- ){
            int type;
            cin>>type;
            if ( type == 1 ){
                //Give all money from position, print inside update function
                int pos;
                cin>>pos;
                update(1,0,n, pos,0, treeData);
            }
            else if ( type == 2 ){
                //Add value to position
                int pos, val;
                cin>>pos>>val;
                update(1,0,n, pos,val, treeData);
            }
            else {
                //Range Query
                int le, ri;
                cin>>le>>ri;
                cout<<query(1,0,n, le, ri, treeData)<<"\n";
            }

        }
    }
};
int main(){
    fast
    segmentTree obj;
    cin>>t;
    while( t-- )
        obj.inputAndPerform();
    return 0;
}