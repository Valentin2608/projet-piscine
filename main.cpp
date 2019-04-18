#include <iostream>
#include "graphe.h"
#include <allegro.h>
int main()
{

    std::string id;
    graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    //graphe g_min;
    //g_min=g.prim(1); ///  cubetown 1
    //g_min.dessinerGraphe();


    //g.prim();

    auto tab=g.bruteForce(6,9);
    std::cout<<tab.size()<<std::endl;

    auto tab2=g.creerGraphes(tab);
    std::cout<<"yo"<<std::endl;



    auto tab3=g.trierpourpareto(tab2);

    std::cout<<tab3.size()<<std::endl;



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
