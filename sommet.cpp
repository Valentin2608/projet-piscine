#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
void Sommet::afficherVoisins() const
{
    std::cout<<" voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

Sommet::~Sommet()
{
    //dtor
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue<const Sommet*> file;
    file.push(this);
    const Sommet* s;
    while(!file.empty())
    {
        s=file.front();
        file.pop();
        for(size_t i=0; i<s->m_voisins.size(); ++i)
        {
            if((l_pred.find(s->m_voisins[i]->m_id)==l_pred.end()) && s->m_voisins[i]!=this)
            {
                file.push(s->m_voisins[i]);
                l_pred.insert({s->m_voisins[i]->m_id,s->m_id});
            }
        }
    }

    file.push(this);


    return l_pred;
}
std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::stack<const Sommet*> pile;
    pile.push(this);
    const Sommet* s;
    while(!pile.empty())
    {
        s=pile.top();
        pile.pop();
        for(size_t i=0; i<s->m_voisins.size(); ++i)
        {
            if((l_pred.find(s->m_voisins[i]->m_id)==l_pred.end()) && s->m_voisins[i]!=this)
            {
                pile.push(s->m_voisins[i]);
                l_pred.insert({s->m_voisins[i]->m_id,s->m_id});
            }
        }
    }

    pile.push(this);
    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC()
{
    std::unordered_set<std::string> file;
    std::unordered_map<std::string,std::string> l_pred=this->parcoursBFS();
    file.insert(m_id);
    for(auto s:l_pred)
    {
        file.insert(s.first);

        std::pair<std::string,std::string> pred=s;
        while(pred.second!=m_id)
        {
                    pred=*l_pred.find(pred.second);
                    file.insert(pred.first);
        }
    }
    return file;
}

int Sommet::PairOuImpair() const
{
    int nb,i;

    while(nb<m_voisins.size())
    {
        nb++;
    }
    if(nb%2==0)
        i=0;
    else
        i=1;

    return i;
}


