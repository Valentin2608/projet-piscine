#ifndef ARETE_H
#define ARETE_H

#include <iostream>
#include <string>


class Arete
{
    public:
        Arete(std::string id,float cout1,float cout2,std::string id1,std::string id2);
        Arete(std::string id,float cout1,float cout2);
        void AjouterSommets(std::string s1,std::string s2);
        void AfficherArete() const;
        virtual ~Arete();


    protected:

    private:
        std::string m_id; /// num�ro du sommet
        float m_c1,m_c2; /// les deux co�ts
        std::string m_id_sommet1, m_id_sommet2; /// les deux num�ro ID des sommets qui sont reli�s par l'ar�te
};

#endif // ARETE_H
