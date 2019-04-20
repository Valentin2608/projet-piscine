#include <fstream>
#include <iostream>
#include "graphe.h"
#include <allegro.h>
/// SAUVEGARDE EXTRAITE DU CODE DU TP2
graphe::graphe()
{

}

graphe::graphe(std::string nomFichier, std::string nomFichier2) : m_coutTot2{0.0} , m_coutTot1{0.0}
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
    int id2,id_s1,id_s2,a=0;
    //lecture des aretes
    adj = new std::vector<std::pair<int,int>> [m_sommets.size()];
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
        float w=m_aretes[a]->getCout1();
        adj[id_s1].push_back(std::make_pair(id_s2, w));
        adj[id_s2].push_back(std::make_pair(id_s1, w));
        if(a!=taille2)
            a++;
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

void graphe::CalculPoidsTotaux()
{
    float coutTot1=0;
    float coutTot2=0;

     for (auto b:m_aretes)
    {
        coutTot1=coutTot1+b->getCout1();

    }

    m_coutTot1= coutTot1;
     for (auto a:m_aretes)
    {
        coutTot2=coutTot2+a->getCout2();

    }
    m_coutTot2=coutTot2;

}

float graphe:: getPoidsTotal2() const
{
    return m_coutTot2;
}
float graphe::getPoidsTotal1() const
{
    return m_coutTot1;

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
int graphe::tableau_connexite( )

{
    int cpt=0;
    int i;
    int val=0;
    int somme_connexite=0;
    std::vector<int>connexite;

    for(int i=0; i<m_sommets.size(); i++)

    {

        connexite.push_back(i+1);

    }

///dans le if(vecA[i]->GetEtat()==1) à la fin

    for (auto j: m_aretes)
    {
            val= connexite[j->getId_sommet1()];
            connexite[j->getId_sommet1()]=connexite[j->getId_sommet2()];
            for(int k=0; k<connexite.size(); k++)
            {

                if(connexite[k]==val)

                {
                    connexite[k]=connexite[j->getId_sommet2()];

                }
            }


    }


for(auto l:connexite)
{
    if(connexite[0]==l)
        cpt++;

}
//std::cout << "cpt :" << cpt << "sommet:" << m_sommets.size();
if(cpt==m_sommets.size())
   {
      i=1;
    return i;
   }
   else
    return i=0;




}



std::vector<graphe> graphe::bruteForce()
{

    std::vector<graphe> pourpareto;
    int a;
    int b;
    a=m_sommets.size()-1;
    b=m_aretes.size();
    std::vector<int> tmp(a);
    int recupIDA;
    int nb_composantes_connexes;
    int nb_connexite;

    for (int i = 0; i < a; i++)
        tmp[i] = i;

    while (tmp[0] < b-a+1)
    {

        int j = a - 1;

        graphe *f=new graphe;

        for(auto cq :m_sommets)
        {
            f->ajouterSommet(cq);
        }


        for (auto i=0;i<a;i++)
        {

            recupIDA=tmp[i];
            f->ajouterArete(m_aretes[recupIDA]);

        }
        nb_composantes_connexes=f->rechercher_afficherToutesCC();
        nb_connexite=f->tableau_connexite();
        if((nb_composantes_connexes==1)&& (nb_connexite==1))
        {
          pourpareto.push_back(*f);
        }

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

    return pourpareto;
}
graphe graphe::prim(int num)
{
    int i=0,k,u=0;
    ///  Crée un graphe vide

    graphe G;


    int id=0,id_voisin;
    std::vector<Arete*> aretes;
    std::vector<float> cou;
    int idd;
    float c,c2;
    std::vector<Sommet*> sommets_decouverts;
    Sommet* so;
    m_sommets[id]->selectionner(1);
    /// Selectionne un sommet et l'ajoute au graphe vide
    Sommet* s=m_sommets[id];
    G.ajouterSommet(s);
    /// Parcourir tous les sommets du graphes de bases
    do
    {
        u++;
        std::cout << "   etape   " << u << std::endl;

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
                            //a->AfficherArete();
                        }
                }
            }

        }

        /// A REVOIR
        /// Une fois que les arrêtes relies au sommet initiale sont trouvées
    /*    for(auto tri : aretes)
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
         */
        if(num==1)
                {
                    std::sort(aretes.begin(),aretes.end(),[](Arete* s1, Arete* s2){
              return s1->getCout1() < s2->getCout1();});
                }
        if(num==2)
                {
                    std::sort(aretes.begin(),aretes.end(),[](Arete* s1, Arete* s2){
              return s1->getCout2() < s2->getCout2();});
                }

        k=0,i=0;
        std::cout << "DEBUT"<< std::endl;
        for(auto tri : aretes)
        {
            tri->AfficherArete();
        }
        std::cout << "FIN" << std::endl;
        for(auto tri : aretes)
        {

            if(tri->getSelection()!=1)
            {
                if(num==1)
                {
                    c=tri->getCout1();
                    c2=aretes[0]->getCout1();
                }
                if(num==2)
                {
                    c=tri->getCout2();
                    c2=aretes[0]->getCout2();
                }
                if(c==c2)
                {

                    idd = tri->getId_sommet1();
                    if(idd==id)
                            idd = tri->getId_sommet2();
                    for(auto verif : sommets_decouverts)
                    {
                        if(idd == (verif->getId()))
                            {
                                std::cout << "ici1" << idd;
                                idd = tri->getId_sommet2();
                                for(auto veri : sommets_decouverts)
                                {
                                    if(idd == (veri->getId())&&(i==0))
                                    {
                                        i++;

                                        std::cout<< " ici " << idd;

                                        aretes.erase(aretes.begin()+k);
                                    }

                                }
                            }
                    }
                so=m_sommets[idd];
                       // so->afficherData();
                       if((so->getSelection()==1) && (i==1))
                        i++;

                        if(so->getSelection() != 1)
                        {
                            //cou.clear();
                            if(k==0)
                            {

                                aretes.erase(aretes.begin());
                                id=idd;
                                G.ajouterArete(tri);
                                tri->selectionner(1); ///  Bool 0 -> 1
                                G.ajouterSommet(so);
                                tri->AfficherArete();

                                m_sommets[idd]->selectionner(1); ///  Bool 0 -> 1
                                sommets_decouverts=G.getSommets();

                            }




                            k++;
                        }


                    }

                }
        }
    }
    while(m_sommets.size()!=(G.getSommets()).size());

   // std::sort(sommets_decouverts.begin(), sommets_decouverts.end(), [](Sommet* s1, Sommet* s2){
      //        return s1->getId() < s2->getId();
       //       });

    G.ajouterSommets(m_sommets);

    return G;
}

void graphe::ajouterSommets(std::vector<Sommet*> som)
{
    m_sommets=som;
}

void graphe::ajouterAretes(std::vector<Arete*> som)
{
    m_aretes=som;
}

void graphe::dessinerGraphe()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800,0,0);

    //initialisation allegro

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
    show_mouse(screen);
     while (!key[KEY_ESC])//ne pas sortir de la boucle
    {


    draw_sprite(buffer,fond,0,0);
    rectfill(buffer,300,300,500,400,makecol(0,0,255));
    if (mouse_x>=300 && mouse_x<=500 && mouse_y>=300 && mouse_y<=400 && mouse_b & 1)
    {
        clear_to_color(buffer, makecol(255,255,255));
        draw_sprite(buffer,fond,0,0);
    for (auto a:m_aretes)
     {
         int idd1=a->getId_sommet1();// on prend le numero des sommets de l'arête
         int idd2=a->getId_sommet2();
         Sommet* s=(m_sommets[idd1]);
         Sommet* p=(m_sommets[idd2]);
         line(buffer,s->getX()*1.5,s->getY()*1.5,p->getX()*1.5,p->getY()*1.5,makecol(0,0,255));
         textprintf_ex(buffer,font,(((s->getX()+p->getX())/2)-10)*1.5,(((s->getY()+p->getY())/2)-5)*1.5,makecol(0,0,255),-1,"%d",a->getId());//affichage arête
        // textprintf_ex(screen,font,((s->getX()+p->getX()/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC1().c_str());//affichage numéro arête
        //textprintf_ex(screen,font,((s->getX()+p->getX()/2)-10,((s->getY()+p->getY())/2)-5,makecol(255,255,255),-1,a.second->getC2().c_str());//affichage numéro arête

     }
     //dessin des sommets
    for(auto a:m_sommets)
    {

        circlefill(buffer,(a->getX())*1.5,(a->getY())*1.5,15,makecol(0,0,255));//affichage sommet
        textprintf_ex(buffer,font,(a->getX()-2)*1.5,(a->getY()-2)*1.5,makecol(255,255,255),-1,"%d",a->getId());//affichage numero du sommet
    }


    }
    draw_sprite(screen,buffer,0,0);
    }
}


bool fonction(graphe g, graphe gbis)
{
    return g.getPoidsTotal1()<gbis.getPoidsTotal1();
}
void appliquerPareto(std::vector<graphe> &G)
{
    std::vector<graphe>ParetoD;///graphe pareto dominés
    std::vector<graphe>ParetoND;///graphe pareto non dominés

    for (auto& a: G)
    {
        a.CalculPoidsTotaux();
    }
    std::sort(G.begin(),G.end(),fonction);

    ParetoND.push_back(G[0]);
    float a=G[0].getPoidsTotal2();
    float pred=G[0].getPoidsTotal1();
    graphe predd=G[0];

    for(size_t i=1;i<G.size();++i)
    {
    float b=G[i].getPoidsTotal2();
    if(a<=b)
     {
         ParetoD.push_back(G[i]);
     }
     else
     {
         if( pred == G[i].getPoidsTotal1())
         {
             ParetoND.erase(ParetoND.end());
             ParetoD.push_back(predd);
         }
         ParetoND.push_back(G[i]);
         a=G[i].getPoidsTotal2();
         pred=G[i].getPoidsTotal1();
         predd=G[i];

     }
    }

  //  dessinerpoint(ParetoD,ParetoND);
}

 void dessinerpoint(std::vector<graphe> n1,std::vector<graphe> n2)
    {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800,0,0);

    //initialisation allegro

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
    show_mouse(screen);
     while (!key[KEY_ESC])//ne pas sortir de la boucle
    {
        clear_to_color(buffer, makecol(255,255,255));
        draw_sprite(buffer,fond,0,0);

        for(auto a: n1)
        {

           circlefill(buffer,a.getPoidsTotal1(),a.getPoidsTotal2(),5,makecol(255,0,0));
        }

        for(auto a: n2)
        {

            circlefill(buffer,a.getPoidsTotal1(),a.getPoidsTotal2(),5,makecol(255,0,0));
        }
    }
}


/// inspiré du code sur le site https://ideone.com/qkmt31

void graphe::dijkstra(int source) //Algorithm for SSSP
{

    int A=m_sommets.size();

    bool vis[A]={0};
    int dis[A];
    std::cout << "ici";
    for(int i=0;i<A;i++) //Set initial distances to Infinity
        {
            dis[i]=INT_MAX;
        }

    class prioritize{public: bool operator ()(std::pair<int, float>&p1 ,std::pair<int, float>&p2){return p1.second>p2.second;}};
    std::priority_queue<std::pair<int,float> ,std::vector<std::pair<int,float>>, prioritize> pq; //Priority queue to store vertex,weight pairs
    pq.push(std::make_pair(source,dis[source]=0)); //Pushing the source with distance from itself as 0

    while(!pq.empty())
    {
        std::pair<int, float> curr=pq.top(); //Current vertex. The shortest distance for this has been found
        pq.pop();
        int cv=curr.first,cw=curr.second; //'cw' the final shortest distance for this vertex
        if(vis[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
            continue;
        vis[cv]=true;
        for(int i=0;i<adj[cv].size();i++) //Iterating through all adjacent vertices
            if(!vis[adj[cv][i].first] && adj[cv][i].second+cw<dis[adj[cv][i].first]) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
                pq.push(std::make_pair(adj[cv][i].first,(dis[adj[cv][i].first]=adj[cv][i].second+cw))); //Set the new distance and add to priority queue
    }
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < A; ++i)
        printf("%d \t\t %d\n", i, dis[i]);
}

graphe::~graphe()
{
    //dtor
}
