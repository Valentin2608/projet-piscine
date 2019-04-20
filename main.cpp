#include <iostream>
#include "graphe.h"
//#include <allegro.h>
int main()
{

    std::string id;
    graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};

    /// PARTIE 1
    graphe g_min1,g_min2;
    g_min1=g.prim(1);
    g_min2=g.prim(2);


    /// PARTIE 2
    auto tab1=g.bruteForce();
    appliquerPareto(tab1,1);


    /// PARTIE 3
    auto tab=g.multipleBruteForce();
    for(auto& t : tab)
    {
        t.appliquerDijkstra();
    }
    appliquerPareto(tab,0);



    return 0;

}END_OF_MAIN();
