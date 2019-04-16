#include <fstream>
#include <iostream>
#include "graphe.h"
#include <allegro.h>

graphe::graphe(std::string nomFichier, std::string nomFichier2)
{
        /// OUVERTURE DU SECOND FICHIER
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
void graphe::dessinerGraphe()
{
    //initialisation allegro
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
     if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
     while (!key[KEY_ESC])//ne pas sortir de la boucle
    {



    // dessin arêtes
     for (auto a:m_aretes)
     {
         std::string idd1=a.second->getId_sommet1();// on prend le numero des sommets de l'arête
         std::string idd2=a.second->getId_sommet2();
         Sommet*s=(m_sommets.find(idd1))->second;
         Sommet*p= (m_sommets.find(idd2))->second;
         line(screen,s->getX()*1.5,s->getY()*1.5,p->getX()*1.5,p->getY()*1.5,makecol(0,0,255));//affichage arête
       //  textprintf_ex(screen,font,((s->getX()+p->getX)/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC1().c_str());//affichage numéro arête
        //textprintf_ex(screen,font,((s->getX()+p->getX)/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC2().c_str());//affichage numéro arête
     }
     //dessin des sommets
    for(auto a:m_sommets)
    {
        circlefill(screen,(a.second->getX())*1.5,(a.second->getY())*1.5,15,makecol(0,0,255));//affichage sommet
        textprintf_ex(screen,font,(a.second->getX()-2)*1.5,(a.second->getY()-2)*1.5,makecol(255,255,255),-1,a.second->getId().c_str());//affichage numero du sommet
    }
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

int graphe::isEulerien() const
{
    int s=0,nbSoImpairs=0,eul=0,nbSoPairs=0;
    for(auto a:m_sommets)
    {
    Sommet* s0=a.second;
    s=s0->PairOuImpair();
       if(s==1)
       {
           nbSoImpairs++;
       }
       if(s==0)
       {
           nbSoPairs++;
       }
    }
    if(nbSoImpairs==2)
    {
        eul=1;
    }
    if(nbSoPairs==m_sommets.size())
    {
        eul=2;
    }
    return eul;
}

graphe::~graphe()
{
    //dtor
}
