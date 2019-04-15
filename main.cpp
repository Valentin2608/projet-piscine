#include <iostream>
#include "graphe.h"

int main()
{
    std::string id;
    graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    g.afficher();
    /// Saisir identifiant
    std::cout << "saisissez id que vous souhaitez :";
    std::cin >> id;
    ///
    g.afficherBFS(id);
    g.afficherDFS(id);
    int ncc=g.rechercher_afficherToutesCC();
    std::cout << "nb cc :" << ncc << std::endl;
    if(ncc==1)
    {
    int eul=g.isEulerien();
    if(eul==0)
        std::cout<<"Le graphe n'a rien d'eulerien"<<std::endl<<std::endl;
    if(eul==1)
        std::cout<<"Le graphe admet une chaine eulerienne"<<std::endl<<std::endl;
    if(eul==2)
        std::cout<<"Le graphe admet un cycle eulerien"<<std::endl<<std::endl;
    }
    else
        std::cout<<"Le graphe n'est pas connexe, il n'a donc rien d'eulerien"<<std::endl<<std::endl;
    return 0;
}
