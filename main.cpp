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

///Prim este un algoritm care rezolva problema arborelui minim de acoperire( dandu-se un graf conex, cu costuri pe muchii,
///alegeti muchiile astfel incat sa se alcatuiasca un arbore cu cost minim )
///Acest algoritm aplica aceeasi idee ca si la Dikjstra, avand aceeasi complexitate


///Lista de adiacenta este retinuta intr-un vector de vectori de pair-uri
vector<pair<int, int>> adj_list[maxi];

///Vector de vizitare - se retine nodurile care au fost sau nu cucerite.
///Construirea vectorului sub forma visited(maxi,0) inseamna ca acestui vector i se creeaza 200002 elemente de valoare 0.
vector<int> visited(maxi,0);

///Vector de perechi pentru căi - se retin muchiile care alcatuiesc arborele sub forma nod sursa - nod destinatie.
vector<pair<int, int>> way;
int n, m, x, y, c;

///In functia PrimAlgorithm ne folosim de un priority_queue. Acesta, prin definire, este un max_heap( pe pozitia primului element
///se afla cel mai mare element din container. Pentru ca noua ne trebuie un min_heap, trebuie sa facem overload de
///operator( "vector<tuple<int,int,int>>, greater<tuple<int,int,int>>" )
///"tuple<int, int, int>"  - este tipul de data: un tuplu format din 3 intregi, care reprezinta: cost -- nod pornire -- nod sosire
priority_queue<tuple<int, int, int> , vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> tail;


///Functia are ca parametru nodul de plecare
long int PrimAlgorithm( int startNode ){

    ///Prima data adaugam toate nodurile cu care se invecineaza nodul de plecare. Pentru asta ne uitam in lista lui
    ///de adiacenta si formam tupluri pentru a le adauga in tail.
    for( auto it = adj_list[startNode].begin() ; it != adj_list[startNode].end() ; it++ )
    {
        int cost_ = it -> second;
        int nod_sosire_ = it -> first;
        tail.push( make_tuple( cost , startNode , nod_sosire_ ) );
    }

    ///sum reprezinta variabila in care o sa stocam costul total al arborelui.
    long int sum = 0;

    ///Cat timp coada noastra nu este goala, noi cautam alte noduri pe care sa le cucerim
    while( !tail.empty() )
    {
        int nodPlecare, nodSosire, cost;

        ///Pentru ca ne folosim de un priority_queue min, functia  top() o sa returneze primul si cel mai mic element din tail.
        ///functia tie() alipeste variabilele pentru a putea lua valori din tuplu
        ///Dupa ce am extras prima muchie, o scoatem din coada.

        tie( cost, nodPlecare , nodSosire ) = tail.top();
        tail.pop();


        ///Daca nodul de sosire a fost vizitat( a fost cucerit), nu ne mai intereseaza. Folosim continue pentru a reveni la while().
        if( visited[nodSosire] == 1 )
            continue;

        ///Marcam ambele noduri ca fiind vizitate si adunam la suma costul muchiei adaugate. De asemenea, o adaugam in vectorul de
        ///căi sub forma - nod pornire - nod sosire.
        visited[nodPlecare] = 1;
        visited[nodSosire] = 1;
        sum += cost;
        way.push_back( make_pair(nodPlecare , nodSosire) );


        ///Iteram prin lista de adiacenta a nodului de sosire pentru a adauga alte varfuri necucerie( visited == 0 )
        for( auto it = adj_list[nodSosire].begin() ; it != adj_list[nodSosire].end() ; it++ )
        {
            if( visited[it -> first] == 0 )
            {
                int cost_ = it -> second;
                int nod_sosire_ = it -> first;

                ///acum nodul nodSosire joaca rolul de nod de plecare.
                tail.push( make_tuple( cost_ , nodSosire, nod_sosire_  ));
            }
        }
    }

    ///returnam costul total al muchiilor
    return sum;
}

int main()
{

    ///Input-ul se citeste din fisier. Pentru rapiditatea rezolvarii, am folosit metodele de citire din C
    freopen( "apm.in", "r", stdin );
	freopen( "apm.out", "w", stdout );

    ///n reprezinte numarul de noduri, iar m numarul de muchii
    scanf( "%d %d\n", &n, &m );

    ///Citim cele m muchii date sub forma : nod sursa - nod destinatie - cost;
    for( int i = 0 ; i < m ; i++ )
    {
        scanf( "%d %d %d\n", &x, &y, &c );
        ///Folosim vectorul de vector de pair-uri  pentru a tine lista de adiacenta
        ///Deoarece graful este neorientat, adaugam marginea si la nodul sursa si la nodul destinatie
        adj_list[x].push_back( make_pair( y , c ));
        adj_list[y].push_back( make_pair( x , c ));
    }

    ///Apleam functia , avand parametru startNode = 1 ( plecam din nodul 1 )
    ///Putem pleca din orice nod al grafului
    long int sum = PrimAlgorithm(1);

    ///Afisam urmatoarele:
    ///-suma muchiilor ce alcatuiesc arborele minim de acoperire
    ///-cate muchii alcatuiesc arborele minim de acoperire( din definitia arborelui, aceasta este egala cu n - 1 )
    ///-care sunt muchiile( afisate in arice ordine, in orice sens )
    printf( "%d\n", sum );
    printf( "%d\n" , way.size() );
    for( auto it : way )
    {
        printf( "%d %d\n" , it.first , it.second );
    }
    return 0;
}
