#ifndef ARETE_H
#define ARETE_H

#include <iostream>
#include <string>
#include <vector>


class Arete
{
    public:
        Arete(std::string id,float cout1,float cout2,std::vector<std::string> id_s);
        Arete(std::string id,float cout1,float cout2);
        void AjouterSommets(std::string s1,std::string s2);
        void AfficherArete() const;
        virtual ~Arete();
        std::vector<std::string> getSommets() const;
        float getCout1() const;
        bool getBool();
        bool getSelection();
        void utiliser();
        void selectionner();
       std::string getId() const;
       std::string getId_sommet2();
       std::string getId_sommet1();



    protected:

    private:
        bool m_utiliser=0,m_selectionner=0;
        std::string m_id; /// num�ro du sommet
        float m_c1,m_c2; /// les deux co�ts
        std::vector<std::string> m_id_sommet; /// les deux num�ro ID des sommets qui sont reli�s par l'ar�te
};

#endif // ARETE_H
