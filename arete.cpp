#include "arete.h"

Arete::Arete(std::string id,float cout1,float cout2,std::string id1,std::string id2):m_id{id},m_c1{cout1},m_c2{cout2},m_id_sommet1{id1},m_id_sommet2{id2}
{
    //ctor
}

Arete::Arete(std::string id,float cout1,float cout2):m_id{id},m_c1{cout1},m_c2{cout2}
{
    m_id_sommet1='0';
    m_id_sommet2='0';
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

std::string Arete::getId_sommet1() const
{
    return m_id_sommet1;
}
std::string Arete::getId_sommet2() const
{
    return m_id_sommet2;
}
float Arete::getC1()const
{
    return m_c1;

}
float Arete::getC2()const
{
    return m_c2;

}
Arete::~Arete()
{
    //dtor
}
