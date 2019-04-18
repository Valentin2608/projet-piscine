#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl
    << "selectionner : " << m_selectionner << std::endl;
}
void Sommet::afficherVoisins() const
{
    std::cout<<" voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

double Sommet::getX()
{
    return m_x;
}

double Sommet::getY()
{
    return m_y;
}

std::unordered_set<int> Sommet::rechercherCC ( ) const
{
	std::unordered_set<int> cc;
	std::stack<const Sommet*> stack;
	stack.push ( this );
	cc.insert ( m_id );
	while ( !stack.empty ( ) )
	{
		const Sommet* courant = stack.top ( );
		stack.pop ( );
		for ( const auto& a : courant->m_voisins )
		{
			if ( cc.find ( a->m_id ) == cc.end ( ) )
			{
				cc.insert ( a->m_id );
				stack.push ( a );
			}
		}
	}
	return cc;
}


void Sommet::selectionner(bool a)
{
    m_selectionner=a;
}
bool Sommet::getSelection()
{
    return m_selectionner;
}


int Sommet::getId() const
{
    return m_id;
}

std::vector<const Sommet*> Sommet::getVoisins() const
{
    return m_voisins;
}

Sommet::~Sommet()
{
    //dtor
}


