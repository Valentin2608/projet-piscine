#include <iostream>
#include "graphe.h"
#include <allegro.h>
int main()
{

    std::string id;
    graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    graphe g_min;
    g_min=g.prim(2); /// cubetown 2, manhattan 1, triville 2
    //g_min.afficher();
    g.dessinerGraphe();



    return 0;
}END_OF_MAIN();
