#include "arete.h"

Arete::Arete(int id,float cout1[2],std::vector<int> id_s):m_id{id},m_c{cout1[2]},m_id_sommet{id_s}
{
    //ctor
}

Arete::Arete(int  id,float cout1[2]):m_id{id},m_c{cout1[2]}
{

}

std::vector<int> Arete::getSommets() const
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

int  Arete::getId_sommet2()
{
    return m_id_sommet[1];
}

int Arete::getId_sommet1()
{
    return m_id_sommet[0];
}

void Arete::selectionner()
{
    m_selectionner=1;
}


float* Arete::getCout()
{
    return m_c;
}

void Arete::AjouterSommets(int  s1,int s2)
{
    m_id_sommet.push_back(s1);
    m_id_sommet.push_back(s2);
}

void Arete::AfficherArete() const
{
    std::cout << "numero :" << m_id << std::endl
    << "Cout 1 : " << m_c[0] << "  Cout 2 : " << m_c[1] << std::endl
    << "l'arete depend des sommets numero " << m_id_sommet[0] << " et " << m_id_sommet[1] << std::endl
    << " selectionner " << m_selectionner << std::endl;
}

int Arete::getId() const
{
    return m_id;
}

Arete::~Arete()
{
    //dtor
}
