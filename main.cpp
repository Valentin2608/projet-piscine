#include <iostream>
#include "graphe.h"
//#include <allegro.h>
int main()
{

    std::string id;
    graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};
    //graphe g_min;
    //g_min=g.prim(1); ///  cubetown 1
    //g_min.dessinerGraphe();


    //g.prim();

    auto tab=g.bruteForce();
    appliquerPareto(tab);






    return 0;
}END_OF_MAIN();
