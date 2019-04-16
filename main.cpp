#include <iostream>
#include "graphe.h"

int main()
{
    std::string id;
    graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    g.afficher();
    g.dessinerGraphe();



    return 0;
}
