#include <fstream>
#include <iostream>
#include "graphe.h"
#include <allegro.h>
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
    int idd;
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
        float c[2]; c[0]=c1; c[1]=c2;
        m_aretes.push_back(new Arete{idd,c});
    }
    /// OUVERTURE FICHIER
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    nb_sommets=ordre;
    int id;
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
        m_sommets.push_back(new Sommet{id,x,y});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    nb_aretes=taille;
    int id2,id_s1,id_s2;
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
        m_aretes[id2]->AjouterSommets(id_s1,id_s2);
        m_sommets[id_s1]->ajouterVoisin(m_sommets[id_s2]);
        m_sommets[id_s2]->ajouterVoisin(m_sommets[id_s1]);
    }

}
void graphe::afficher() const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<< "ordre : " << m_sommets.size() <<std::endl;
    for(auto s:m_sommets)
    {
        std::cout<<"sommet: ";
        s->afficherData();
        std::cout << std::endl;
    }

    for(auto s:m_aretes)
    {
        std::cout<<"arrete: ";
        s->AfficherArete();
        std::cout << std::endl;
    }
}

int graphe::rechercher_afficherToutesCC ( ) const
{
	int i = 0, nb=0;
	std::unordered_set<int> set;
	for ( auto& a : m_sommets )
	{
	    a->selectionner(0);
	}
	for ( auto& a : m_sommets )
	{
		if ( set.find ( a->getId() ) == set.end ( ) )
            {
			++i;
			std::unordered_set<int> temp = a->rechercherCC ( );
			set.insert ( temp.begin ( ) , temp.end ( ) );
            }
	}
	for(auto& b : m_aretes)
    {
        m_sommets[b->getId_sommet1()]->selectionner(1);
        m_sommets[b->getId_sommet2()]->selectionner(1);
    }
    for ( auto& a : m_sommets )
	{
	    if(a->getSelection()==1)
            nb++;
	}
	if(nb!=m_sommets.size())
        i++;
	return i;
}



void graphe::ajouterSommet(Sommet* s)
{
    m_sommets.push_back(s);
}

void graphe::ajouterArete(Arete* s)
{
    m_aretes.push_back(s);
}

std::vector<Sommet*> graphe::getSommets()
{
    return m_sommets;
}
/*void graphe::dessinerGraphe()
{
    //initialisation allegro
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
    BITMAP*buffer;
    BITMAP*fond;
    buffer=create_bitmap(1200,800);
    fond=load_bitmap("fond.bmp",NULL);
     if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
     while (!key[KEY_ESC])//ne pas sortir de la boucle
    {

    draw_sprite(buffer,fond,0,0);
    // dessin arêtes
     for (auto a:m_aretes)
     {
         std::string idd1=a.second->getId_sommet1();// on prend le numero des sommets de l'arête
         std::string idd2=a.second->getId_sommet2();
         Sommet*s=(m_sommets.find(idd1))->second;
         Sommet*p= (m_sommets.find(idd2))->second;
         line(buffer,s->getX()*1.5,s->getY()*1.5,p->getX()*1.5,p->getY()*1.5,makecol(0,0,255));//affichage arête
       //  textprintf_ex(screen,font,((s->getX()+p->getX)/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC1().c_str());//affichage numéro arête
        //textprintf_ex(screen,font,((s->getX()+p->getX)/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC2().c_str());//affichage numéro arête
     }
     //dessin des sommets
    for(auto a:m_sommets)
    {
        circlefill(buffer,(a.second->getX())*1.5,(a.second->getY())*1.5,15,makecol(0,0,255));//affichage sommet
        textprintf_ex(buffer,font,(a.second->getX()-2)*1.5,(a.second->getY()-2)*1.5,makecol(255,255,255),-1,a.second->getId().c_str());//affichage numero du sommet
    }
    draw_sprite(screen,buffer,0,0);
    }
}*/
std::vector<std::vector<int>> graphe::bruteForce(int a,int b)
{
    std::vector<std::vector<int>> res;

    std::vector<int> tmp(a);

    for (int i = 0; i < b; i++)
        tmp[i] = i;

    while (tmp[0] < b-a+1)
    {
        int j = a - 1;

        res.push_back(tmp);

        tmp[j] += 1;

        int lim = b;

        int cpt = 0;

        while(j > 0)
        {
            if (tmp[j] >= lim)
            {
                j -= 1;
                lim -= 1;
                tmp[j] += 1;
                cpt++;
            }

            else
                j = -1;
        }

        for (int i = a - cpt; i < a; i ++)
            tmp[i] = tmp[i - 1] + 1;
    }

    return res;
}

std::vector<graphe> graphe::creerGraphes(std::vector<std::vector<int>> tab)
{

    std::vector<graphe> pourpareto;

    int recupIDA;


    for (auto a:tab)
    {

      graphe g;
        for(auto b :m_sommets)
        {
            g.ajouterSommet(b);
        }

    for (auto i=0;i<nb_sommets-1;i++)
    {

        recupIDA=a[i];
        g.ajouterArete(m_aretes[recupIDA]);

    }

     pourpareto.push_back(g);

    }

    return pourpareto;

}

 std::vector<graphe> graphe::trierpourpareto(std::vector<graphe> grapheN)
{
     std::vector<graphe> pareto;
    int nb_composantes_connexes;
    int i=0;
    for (auto a:grapheN)
    {


        nb_composantes_connexes=a.rechercher_afficherToutesCC();
        if(nb_composantes_connexes==1)
        {
          pareto.push_back(a);
        }
        i++;
    }
    return pareto;




}




graphe::~graphe()
{
    //dtor
}
