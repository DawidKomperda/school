
    // C = 255 -R;
    // M = 255 -G;
    // Y = 255 -B;
    
    // // RGB -> CMY -> cmyk -> CMY -> RGB
    // for (int yy = 0; yy < wysokosc / 2; yy++)
    // {
    //     for (int xx = 0; xx < szerokosc / 2; xx++)
    //     {
    //         R = getPixel(xx, yy).r;
    //         G = getPixel(xx, yy).g;
    //         B = getPixel(xx, yy).b;

    //         setPixel(xx + szerokosc / 2, yy, C,M,Y);
    //     }
    // }

    // SDL_UpdateWindowSurface(window);