#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <algorithm>
#include "sommet.h"
#include "arete.h"
#include <allegro.h>


class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        graphe();
        ~graphe();
        void afficher() const;

        graphe prim(int num);
        void ajouterSommet(Sommet *s);
        void ajouterArete(Arete *s);
        std::vector<Sommet*> getSommets();
        void ajouterSommets(std::vector<Sommet*> som);
        void ajouterAretes(std::vector<Arete*> som);
        void dessinerGraphe();
        void CalculPoidsTotaux();
        float getPoidsTotal1();
        float getPoidsTotal2();

        //std::vector<graphe> creerGraphes(std::vector<std::vector<int>> tab);
        std::vector<graphe>bruteForce();
        int rechercher_afficherToutesCC ( ) const;
        // std::vector<graphe> trierpourpareto(std::vector<graphe> grapheN);

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;///stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::vector<Arete*> m_aretes; /// clé= id de l'arete, valeur = pointeur sur arete
        float m_coutTot1=0;
        float m_coutTot2=0;
        int nb_sommets,nb_aretes;
};

#endif // GRAPHE_H
