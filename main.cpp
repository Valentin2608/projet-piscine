#include <iostream>
#include "graphe.h"

int main()
{
    std::string id;
    graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    //g.prim();

    auto tab=g.bruteForce(3,5);
    std::cout<<tab.size()<<std::endl;

    auto tab2=g.creerGraphes(tab);


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
}
