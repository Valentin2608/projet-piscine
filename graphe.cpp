#include <fstream>
#include <iostream>
#include "graphe.h"

/// SAUVEGARDE EXTRAITE DU CODE DU TP2
graphe::graphe(std::string nomFichier, std::string nomFichier2)
{
        /// OUVERTURE DU FICHIER PONDERATION
    std::ifstream pfs{nomFichier2};
    if (!pfs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );
    int taille2;
    int ponderation;
    pfs >>  taille2;
    if ( pfs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string idd;
    float c1,c2;
    pfs>> ponderation;
    ///lecture des arrete
    for (int i=0; i< taille2; ++i)
    {

        if(pfs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        pfs>> idd;
        if(pfs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        pfs >> c1;
        if(pfs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        pfs >> c2;
        if(pfs.fail())
            throw std::runtime_error("Probleme lecture données arete1");
        m_aretes.insert({idd,new Arete{idd,c1,c2}});
    }

    /// OUVERTURE FICHIER
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id2,id_s1,id_s2;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        ///lecture des ids des deux extrémités

        ifs>>id2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet id");
        ifs>>id_s1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_s2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_aretes.find(id2))->second->AjouterSommets(id_s1,id_s2);
        (m_sommets.find(id_s1))->second->ajouterVoisin((m_sommets.find(id_s2))->second);
        (m_sommets.find(id_s2))->second->ajouterVoisin((m_sommets.find(id_s1))->second);

    }

}
void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<< "ordre : " << m_sommets.size() <<std::endl;
    for(auto s:m_sommets)
    {
        std::cout<<"sommet: ";
        (s.second)->afficherData();
        std::cout << std::endl;
    }

    for(auto s:m_aretes)
    {
        std::cout<<"arrete: ";
        (s.second)->AfficherArete();
        std::cout << std::endl;
    }
}


/// A enlever si on a plus besoin à la fin
void graphe::parcoursBFS(std::string id) const
{
    Sommet* s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const
{
    Sommet* s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const
{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> pred,cc;

    for(auto a:m_sommets)
    {
        if(i<3)
        {
        Sommet* s0=a.second;
        cc=s0->rechercherCC();
        if((cc!=pred))
        {
            i++;
            std::cout<< "   cc" << i << std::endl;
            for(auto s:cc)
            {
                std::cout<< "     " << s;
            }
            std::cout<< std::endl;
        }
        pred=cc;
        cc.clear();
        }
    }

    return i;
}
graphe::~graphe()
{
    //dtor
}
