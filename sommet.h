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
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(int,double,double);
        ~Sommet();
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        ///m�thode de parcours en largeur du graphe � partir du sommet
        ///renvoie les pr�d�cesseurs sous forme d'une map (cl�=id du sommet,valeur=id de son pr�d�cesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///m�thode de parcours en profondeur du graphe � partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///m�thode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC();
        int getId() const;
        std::vector<const Sommet*> getVoisins() const;
        bool getSelection();
        void selectionner();
        double getX();
        double getY();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Donn�es sp�cifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
        bool m_selectionner=0;

};

#endif // SOMMET_H
