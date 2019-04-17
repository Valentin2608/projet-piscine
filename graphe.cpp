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
        m_aretes.push_back(new Arete{idd,c1,c2});
    }
    /// OUVERTURE FICHIER
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
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


/// A enlever si on a plus besoin à la fin
/*void graphe::parcoursBFS(std::string id) const
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
*/
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



graphe graphe::prim(int num)
{
    int i=0,k;
    ///  Crée un graphe vide

    graphe G;


    int id=0,id_voisin;
    std::vector<Arete*> aretes;
    std::vector<float> cou;
    int idd;
    float c;
    std::vector<Sommet*> sommets_decouverts;
    Sommet* so;
    m_sommets[id]->selectionner();
    /// Selectionne un sommet et l'ajoute au graphe vide
    Sommet* s=m_sommets[id];
    G.ajouterSommet(s);
    /// Parcourir tous les sommets du graphes de bases
    do
    {
        std::vector<const Sommet*> voisins=m_sommets[id]->getVoisins();
        /// Parmis les voisins du sommets choisi, trouver les aretes correspondantes
        for(auto y : voisins)
        {
            id_voisin = y->getId(); /// prendre ID du voisin
            /// regarder parmis toutes les aretes du graphe laquelle relis les deux sommets avec leur ID
            for(auto a : m_aretes)
            {
                if(a->getBool() != 1)
                {

                    std::vector<int> sommets = a->getSommets();
                    int num = m_sommets[id]->getId(); /// Recuperer ID du sommet initiale

                    if(( num == sommets[0])||(num == sommets[1]))  /// Si l'id du sommet initial correspond a une arrete
                        if((id_voisin==sommets[0])||(id_voisin==sommets[1])) /// Si l'id du sommet voisin correspond a la meme arrete
                        {
                            aretes.push_back(a);
                            a->utiliser(); /// "marquer" l'arete utilisée pour pas qu'on la reprenne

                        }
                }
            }

        }

        /// A REVOIR
        /// Une fois que les arrêtes relies au sommet initiale sont trouvées
        for(auto tri : aretes)
        {
            if(tri->getSelection()!=1)
            {
                if(num==1)
                {
                cou.push_back(tri->getCout1());
                }
                if(num==2)
                {
                cou.push_back(tri->getCout2());
                }

            }
        }
        std::sort(cou.begin(), cou.end()); /// on range tous les coût par ordre croissant


        for(auto tri : aretes)
        {


            if(tri->getSelection()!=1)
            {
                if(num==1)
                {
                    c=tri->getCout1();
                }
                if(num==2)
                {
                    c=tri->getCout2();
                }
                if((cou[i])==c)
                {

                    idd = tri->getId_sommet1();
                    if(idd==id)
                            idd = tri->getId_sommet2();
                    for(auto verif : sommets_decouverts)
                    {
                        if(idd == (verif->getId()))
                            {
                                idd = tri->getId_sommet2();
                                for(auto veri : sommets_decouverts)
                                {
                                    if(idd == (veri->getId()))
                                    {
                                        i++;
                                    }

                                }
                            }
                    }

                        so=m_sommets[idd];
                        if(so->getSelection() != 1)
                        {
                            cou.clear();

                            G.ajouterArete(tri);
                            tri->selectionner(); ///  Bool 0 -> 1
                            G.ajouterSommet(so);

                            m_sommets[idd]->selectionner(); ///  Bool 0 -> 1
                            sommets_decouverts=G.getSommets();

                            id=idd;

                        }


                    }

                }
        }

    }
    while(m_sommets.size()!=(G.getSommets()).size());

    return G;
}

void graphe::dessinerGraphe()
{
    //initialisation allegro

    BITMAP*buffer;
    BITMAP*fond;
    buffer=create_bitmap(800,600);
    fond=load_bitmap("fond.bmp",NULL);
    int boutton=0;
    int boutton1=0;
    int boutton2=0;
     if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
     while (!key[KEY_ESC])//ne pas sortir de la boucle
    {


    draw_sprite(buffer,fond,0,0);
    rectfill(buffer,300,300,500,400,makecol(0,0,255));
    if (mouse_x>=300 && mouse_x<=500 && mouse_y>=300 && mouse_y<=400 && mouse_b & 1)
    {
        clear_to_color(buffer, makecol(255,255,255));
        draw_sprite(buffer,fond,0,0);

      //  for (auto a:m_aretes)
      for(size_t i=0;i<sizeof(m_aretes);i++)
     {
         int idd1=m_aretes[i]->getId_sommet1();// on prend le numero des sommets de l'arête
         int idd2=m_aretes[i]->getId_sommet2();
         Sommet*s=(m_sommets[idd1]);
         Sommet*p= (m_sommets[idd2]);
         line(buffer,s->getX()*1.5,s->getY()*1.5,p->getX()*1.5,p->getY()*1.5,makecol(0,0,255));
         textprintf_ex(buffer,font,(((s->getX()+p->getX())/2)-10)*1.5,(((s->getY()+p->getY())/2)-5)*1.5,makecol(0,0,255),-1,"%d",m_aretes[i]->getId());//affichage arête
       //  textprintf_ex(screen,font,((s->getX()+p->getX()/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC1().c_str());//affichage numéro arête
        //textprintf_ex(screen,font,((s->getX()+p->getX()/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC2().c_str());//affichage numéro arête
     }
     //dessin des sommets
   // for(auto a:m_sommets)
   for(size_t i=0;i<sizeof(m_sommets);i++)
    {
        circlefill(buffer,(m_sommets[i]->getX())*1.5,(m_sommets[i]->getY())*1.5,15,makecol(0,0,255));//affichage sommet
        textprintf_ex(buffer,font,(m_sommets[i]->getX()-2)*1.5,(m_sommets[i]->getY()-2)*1.5,makecol(255,255,255),-1,"%d",m_sommets[i]->getId());//affichage numero du sommet
    }
    /*boutton1=draw_bouton(buffer,800/2-25,600/2+100,800/2-25+60,600/2+30+100,makecol(228,22,84),makecol(239,99,141),3,"QUITTER");
    boutton=draw_bouton(buffer,800/2-25,600/2,800/2-25+60,600/2+30,makecol(36,172,217),makecol(168,222,240),3,"RESUME");
    boutton2=draw_bouton(buffer,800/2-25,600/2+50,800/2-25+60,600/2+30+50,makecol(36,172,217),makecol(168,222,240),3,"REJOUER");*/

    }
    draw_sprite(screen,buffer,0,0);
    }
}



graphe::~graphe()
{
    //dtor
}
