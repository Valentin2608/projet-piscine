#include <iostream>
#include "graphe.h"
#include <allegro.h>
int main()
{

    std::string id;
    graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    graphe g_min;
    g_min=g.prim(1); ///  cubetown 1
    g_min.dessinerGraphe();




    return 0;
}END_OF_MAIN();
