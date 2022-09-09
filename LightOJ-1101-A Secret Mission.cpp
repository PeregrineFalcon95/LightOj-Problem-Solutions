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
struct node{
    int parent, cost = inf, level;
};
int sparse [ 2 ] [ 100001 ] [ 32 ];
class solution{
private:
    void MST(int n, vector < vector < pair < int, int > > >& graph, vector < node >& mst){
        priority_queue < pair < int, int > >pq;
        vector < bool > vis (n+1, false);
        pq.push( {0, 1} );
        mst [ 1 ].parent = 1;
        mst [ 1 ].cost = 0;
        mst [ 1 ].level = 0;

        while( !pq.empty() ){
            int node = pq.top().second;
            pq.pop();
            if ( vis [ node ] )continue;
            vis [ node ] = true;
            int sz = graph [ node ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ node ] [ i ].first;
                int cost = graph [ node ] [ i ].second;
                if ( !vis [ child ] && mst [ child ].cost > cost ){
                    pq.push( {-cost, child} );
                    mst [ child ].parent = node;
                    mst [ child ].level = mst [ node ].level + 1;
                    mst [ child ].cost = cost;
                }
            } 
        }
    }
    void bfs(int n, vector < vector < pair < int, int > > >& graph, vector < node >& mst){
        queue < int > qu;
        vector < bool > vis (n+1, false);
        vis [ 1 ] = true;
        mst [ 1 ].level = 0;
        qu.push(1);
        sparse [ 0 ] [ 1 ] [ 0 ] = 1; //0 idx for paren
        sparse [ 1 ] [ 1 ] [ 0 ] = 0; //1 idx for cost
        while( !qu.empty() ){
            int node = qu.front();
            qu.pop();
            int sz = graph [ node ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ node ] [ i ].first;
                int cost = graph [ node ] [ i ].second;
                if ( !vis [ child ] && mst [ child ].parent == node && mst [ child ].cost == cost ){
                    vis [ child ] = true;
                    qu.push(child);
                    sparse [ 0 ] [ child ] [ 0 ] = node;
                    sparse [ 1 ] [ child ] [ 0 ] = cost;
                    mst [ child ].level = mst [ node ].level + 1;
                }
            }
        }
    }
    void makeSparse(int n){
        for ( int i = 1; (1<<i) < n; i++ )
            for ( int j = 1; j <= n; j++ )
                if ( sparse [ 0 ] [ j ] [ i - 1 ] != -1 ){
                    sparse [ 0 ] [ j ] [ i ] = sparse [ 0 ] [ sparse [ 0 ] [ j ] [ i - 1 ] ] [ i - 1 ];
                    sparse [ 1 ] [ j ] [ i ] = max( sparse [ 1 ] [ j ] [ i - 1], sparse [ 1 ] [ sparse [ 0 ] [ j ] [ i - 1 ] ] [ i - 1 ] );
                }
    }
    int lca(int p, int q, int n, vector < node >& mst){
        int log = 1;
        int ans = 0;
        if ( mst [ p ].level < mst [ q ].level )swap(p,q);
        while( (1<<(log+1)) < n )log++;
        
        for ( int i = log; i >= 0; i-- )
            if ( sparse [ 0 ] [ p ] [ i ] != -1 && mst [ p ].level - ( 1<<i ) >= mst [ q ].level ){
                ans = max(ans, sparse [ 1 ] [ p ] [ i ]);
                p = sparse [ 0 ] [ p ] [ i ];
            }

        if ( p == q )return ans;
        for ( int i = log; i >= 0; i-- )
            if ( sparse [ 0 ] [ p ] [ i ] != -1 && sparse [ 0 ] [ p ] [ i ] != sparse [ 0 ] [ q ] [ i ] ){
                ans = max(ans, sparse [ 1 ] [ p ] [ i ] );
                ans = max(ans, sparse [ 1 ] [ q ] [ i ] );
                p = sparse [ 0 ] [ p ] [ i ];
                q = sparse [ 0 ] [ q ] [ i ];
            }
        ans = max( ans, sparse [ 1 ] [ p ] [ 0 ] );
        ans = max( ans, sparse [ 1 ] [ q ] [ 0 ] );
        return ans;
    }
public:
    void brainfuck(){
        int n, m, q;
        cin>>n>>m;
        vector < vector < pair < int, int > > > graph (n+1, vector<pair <int,int>> ());
        vector < node > mst (n+1);
        memset(sparse, -1, sizeof sparse);
        while(m--){
            int a,b,c;
            cin>>a>>b>>c;
            graph [ a ].push_back( {b,c} );
            graph [ b ].push_back( {a,c} );
        }
        MST(n, graph, mst);
        bfs(n, graph,mst); //BFS for make sparse table
        makeSparse(n);
        cin>>q;
        cout<<"Case "<<++cases<<":\n";
        while( q-- ){
            int a,b;
            cin>>a>>b;
            cout<<lca(a,b,n, mst)<<"\n";;
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

