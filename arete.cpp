#include "arete.h"

Arete::Arete(int id,float cout1,float cout2,std::string id1,std::string id2):m_id{id},m_c1{cout1},m_c2{cout2},m_id_sommet1{id1},m_id_sommet2{id2}
{
    //ctor
}

void Arete::AjouterSommets(std::string s1,std::string s2)
{
    m_id_sommet1=s1;
    m_id_sommet2=s2;
}

void Arete::AfficherArete() const
{
    std::cout << "numero arete :" << m_id << std::endl
    << "Cout 1 : " << m_c1 << "  Cout 2 : " << m_c2 << std::endl
    << "l'arete depend des sommets numero " << m_id_sommet1 << " et " << m_id_sommet2 << std::endl;
}

Arete::~Arete()
{
    //dtor
}
