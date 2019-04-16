#include "arete.h"

Arete::Arete(std::string id,float cout1,float cout2,std::vector<std::string> id_s):m_id{id},m_c1{cout1},m_c2{cout2},m_id_sommet{id_s}
{
    //ctor
}

Arete::Arete(std::string id,float cout1,float cout2):m_id{id},m_c1{cout1},m_c2{cout2}
{

}

std::vector<std::string> Arete::getSommets() const
{
    return m_id_sommet;
}

bool Arete::getBool()
{
    return m_utiliser;
}

bool Arete::getSelection()
{
    return m_selectionner;
}

void Arete::utiliser()
{
    m_utiliser=1;
}

std::string Arete::getId_sommet2()
{
    return m_id_sommet[1];
}
void Arete::selectionner()
{
    m_selectionner=1;
}


float Arete::getCout1() const
{
    return m_c1;
}

void Arete::AjouterSommets(std::string s1,std::string s2)
{
    m_id_sommet.push_back(s1);
    m_id_sommet.push_back(s2);
}

void Arete::AfficherArete() const
{
    std::cout << "numero arete :" << m_id << std::endl
    << "Cout 1 : " << m_c1 << "  Cout 2 : " << m_c2 << std::endl
    << "l'arete depend des sommets numero " << m_id_sommet[0] << " et " << m_id_sommet[1] << std::endl;
}

std::string Arete::getId() const
{
    return m_id;
}

Arete::~Arete()
{
    //dtor
}
