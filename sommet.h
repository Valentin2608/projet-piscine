#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(int,double,double);
        ~Sommet();
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        ///méthode de parcours en largeur du graphe à partir du sommet
        ///renvoie les prédécesseurs sous forme d'une map (clé=id du sommet,valeur=id de son prédécesseur)
        std::unordered_set<int> rechercherCC()const ;
        int getId() const;
        std::vector<const Sommet*> getVoisins() const;
        bool getSelection();
        void selectionner(bool a);

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
        bool m_selectionner=0;

};

#endif // SOMMET_H
