#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <algorithm>
#include "sommet.h"
#include "arete.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        graphe();
        ~graphe();
        void afficher() const;
       // void dessinerGraphe();
        std::vector<std::vector<int>>bruteForce(int a,int b);
        //std::vector<graphe>creerGraphes(std::vector<std::vector<int>>tab);
        void ajouterSommet(Sommet *s);
        void ajouterArete(Arete *s);
        std::vector<Sommet*> getSommets();

    protected:

    private:
        int nb_sommets,nb_aretes;
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;///stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::vector<Arete*> m_aretes; /// clé= id de l'arete, valeur = pointeur sur arete
};

#endif // GRAPHE_H
