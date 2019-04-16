#include <fstream>
#include <iostream>
#include "graphe.h"

/// SAUVEGARDE EXTRAITE DU CODE DU TP2
graphe::graphe()
{

}

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

void graphe::ajouterSommet(Sommet* s)
{
    m_sommets.insert({s->getId(),s});
}

void graphe::ajouterArete(Arete* s)
{
    m_aretes.insert({s->getId(),s});
}

std::unordered_map<std::string,Sommet*> graphe::getSommets()
{
    return m_sommets;
}

graphe graphe::prim()
{
    ///  Crée un graphe vide

    graphe G;

    std::string id="0",id_voisin;
    std::vector<Arete*> aretes;
    std::vector<float> cou;
    /// Selectionne un sommet et l'ajoute au graphe vide
    Sommet* s=(m_sommets.find(id))->second;
    G.ajouterSommet(s);
    /// Parcourir tous les sommets du graphes de bases
    //do{
    for( auto m : m_sommets)
    {
        std::cout << id;
        std::vector<const Sommet*> voisins=(m_sommets.find(id))->second->getVoisins();
        /// Parmis les voisins du sommets choisi, trouver les aretes correspondantes
        for(auto y : voisins)
        {
            id_voisin = y->getId(); /// prendre ID du voisin
            /// regarder parmis toutes les aretes du graphe laquelle relis les deux sommets avec leur ID
            for(auto a : m_aretes)
            {
                if(a.second->getBool() != 1)
                {

                std::vector<std::string> sommets = a.second->getSommets();
                std::string num = (m_sommets.find(id))->second->getId(); /// Recuperer ID du sommet initiale

                if(( num == sommets[0])||(num == sommets[1]))  /// Si l'id du sommet initial correspond a une arrete
                    if((id_voisin==sommets[0])||(id_voisin==sommets[1])) /// Si l'id du sommet voisin correspond a la meme arrete
                        {
                            aretes.push_back(a.second);
                            a.second->utiliser(); /// "marquer" l'arete utilisée pour pas qu'on la reprenne
                        }
                }
            }

        }

            /// A REVOIR
            /// Une fois que les arrêtes relies au sommet initiale sont trouvées
            for(auto tri : aretes)
            {
                cou.push_back(tri->getCout1());
            }
            std::sort(cou.begin(), cou.end());
            for(auto tri : aretes)
            {
                if(tri->getSelection()!=1)
                {
                if((cou[0])==(tri->getCout1()))
                    {
                        G.ajouterArete(tri);
                        tri->selectionner();
                        std::string idd = tri->getId_sommet2(); /// faire en sorte de prendre aussi le 1er pcq là on prend en compte que le deuxieme sommet de l'arrete
                        Sommet* so=(m_sommets.find(idd))->second;
                        G.ajouterSommet(so);
                        id=idd;
                    }

                }
            }
    }
   // }while(m_sommets.size()!=(G.getSommets()).size());

        G.afficher();

    return G;
}


graphe::~graphe()
{
    //dtor
}
