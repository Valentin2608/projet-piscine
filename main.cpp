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
    std::cout<<tab.size()<<std::endl;




   //tab=
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
}END_OF_MAIN();
