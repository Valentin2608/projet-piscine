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
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string,std::string);
        graphe();
        ~graphe();
        void afficher() const;
        ///lance un parcours en largeur � partir du sommet d'identifiant id
        void parcoursBFS(std::string) const;
        ///lance et affiche le parcours en largeur � partir du sommet d'identifiant id
        void afficherBFS(std::string) const;
         ///lance un parcours en profondeur � partir du sommet d'identifiant id
        void parcoursDFS(std::string) const;
        ///lance et affiche le parcours en profondeur � partir du sommet d'identifiant id
        void afficherDFS(std::string) const;
        ///recherche et affiche les composantes connexes
        ///retourne le nombre de composantes connexes
        int rechercher_afficherToutesCC() const;
        graphe prim();
        void ajouterSommet(Sommet *s);
        void ajouterArete(Arete *s);
        std::vector<Sommet*> getSommets();

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;///stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::vector<Arete*> m_aretes; /// cl�= id de l'arete, valeur = pointeur sur arete
};

#endif // GRAPHE_H
