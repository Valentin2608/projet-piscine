#include <iostream>
#include "graphe.h"

int main()
{
    std::string id;
    graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    //g.prim();

    auto tab=g.bruteForce(5,24);
   /* for(auto a:tab)
    {
        std::cout<<a[0]<<a[1]<<a[2]<<a[3]<<a[4]<<std::endl;
    }
    /*auto tab1=g.creerGraphes(tab);
    for (auto b:tab1)
    {
        b.afficher();
    }*/





    return 0;
}
