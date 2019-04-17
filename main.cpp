#include <iostream>
#include "graphe.h"
#include <allegro.h>
WinMain()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);

    std::string id;
    graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    graphe g_min;
    g_min=g.prim(2);
    g_min.afficher();



    return 0;
}
