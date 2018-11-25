///https://infoarena.ro/problema/apm

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <fstream>
#include <stdio.h>
#define maxi 200002

using namespace std;

//ifstream fin( "apm.in" );
//ofstream fout( "apm.out" );

vector<pair<int, int>> adj_list[maxi];
vector<int> visited(maxi,0);
priority_queue<tuple<int, int, int> , vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> tail;
vector<pair<int, int>> way;
int n, m, x, y, c;

long int PrimAlgorithm( int startNode ){

    for( auto it = adj_list[startNode].begin() ; it != adj_list[startNode].end() ; it++ )
    {
        tail.push( make_tuple( it -> second , startNode , it -> first ) );
    }

    long int sum = 0;
    while( !tail.empty() )
    {
        int nodPlecare, nodSosire, cost;
        tie( cost, nodPlecare , nodSosire ) = tail.top();
        tail.pop();

        if( visited[nodSosire] == 1 )
            continue;

        visited[nodPlecare] = 1;
        visited[nodSosire] = 1;
        sum += cost;
        way.push_back( make_pair(nodPlecare , nodSosire) );

        for( auto it = adj_list[nodSosire].begin() ; it != adj_list[nodSosire].end() ; it++ )
        {
            if( visited[it -> first] == 0 )
            {
                tail.push( make_tuple( it -> second, nodSosire, it -> first ));
            }
        }
    }
    return sum;
}

int main()
{

    freopen( "apm.in", "r", stdin );
	freopen( "apm.out", "w", stdout );

    scanf( "%d %d\n", &n, &m );

    for( int i = 0 ; i < m ; i++ )
    {
        scanf( "%d %d %d\n", &x, &y, &c );
        adj_list[x].push_back( make_pair( y , c ));
        adj_list[y].push_back( make_pair( x , c ));
    }

    long int sum = PrimAlgorithm(1);

    printf( "%d\n", sum );
    printf( "%d\n" , way.size() );
    for( auto it : way )
    {
        printf( "%d %d\n" , it.first , it.second );
    }
    return 0;
}
