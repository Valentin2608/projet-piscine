#ifndef ARETE_H
#define ARETE_H

#include <iostream>
#include <string>
#include <vector>


class Arete
{
    public:
        Arete(int id,float cout1,float cout2,std::vector<int> id_s);
        Arete(int id,float cout1,float cout2);
        void AjouterSommets(int s1,int s2);
        void AfficherArete() const;
        virtual ~Arete();
        std::vector<int > getSommets() const;
        float getCout1();
        float getCout2();
        bool getBool();
        bool getSelection();
        void utiliser();
        void selectionner();
       int  getId() const;
       int getId_sommet2();
       int  getId_sommet1();



    protected:

    private:
        bool m_utiliser=0,m_selectionner=0;
        int m_id; /// num�ro du sommet
        float m_c1,m_c2; /// les deux co�ts
        std::vector<int> m_id_sommet; /// les deux num�ro ID des sommets qui sont reli�s par l'ar�te
};

#endif // ARETE_H
