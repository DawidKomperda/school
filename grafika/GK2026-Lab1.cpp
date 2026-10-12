#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
using namespace std;
SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
#define szerokosc 640
#define wysokosc 400
#define tytul "GK2026 - Lab 1 - Komperda Dawid"
struct CMYK
{
    int c, m, y, k;
    CMYK() : c(0), m(0), y(0), k(0) {};
    CMYK(Uint8 R, Uint8 G, Uint8 B)
    {
        Uint8 C = 255 - R;
        Uint8 M = 255 - G;
        Uint8 Y = 255 - B;
        k = min(min(C, M), Y);
        c = C - k;
        m = M - k;
        y = Y - k;
    }
};

// --- DEKLARACJE FUNKCJI ---
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel(int x, int y);
void setCMYK(int xx, int yy, Uint8 R, Uint8 G, Uint8 B);
CMYK getCMYK();
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

// Funkcje rysujące prymitywy (Zadania z laboratorium)
void linia3(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void elipsa(int x_sr, int y_sr, int a, int b, Uint8 R, Uint8 G, Uint8 B);
void kwadrat(int x, int y, int a, Uint8 R, Uint8 G, Uint8 B);
void kwadratw(int x, int y, int a, Uint8 R, Uint8 G, Uint8 B);
void prostokat(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B);
void prostokatw(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

void Funkcja1()
{
    int R, G, B;
    int C, M, Y;
    int c, m, y, k;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            R = getPixel(xx, yy).r;
            G = getPixel(xx, yy).g;
            B = getPixel(xx, yy).b;

            setPixel(xx + szerokosc / 2, yy, R, G, B);

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;
            k = min(min(C, M), Y);

            c = C - k;
            m = M - k;
            y = Y - k;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;
            setPixel(xx + szerokosc / 2, yy, R, G, B);
        }
    }
    SDL_UpdateWindowSurface(window);
}
void Funkcja2()
{
    int R, G, B;
    int C, M, Y;
    int c, m, y, k;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            R = getPixel(xx, yy).r;
            G = getPixel(xx, yy).g;
            B = getPixel(xx, yy).b;

            setPixel(xx + szerokosc / 2, yy, R, G, B);

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;
            k = min(min(C, M), Y);

            c = C - k;
            m = M - k;
            y = 0;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;
            setPixel(xx + szerokosc / 2, yy, R, G, B);
        }
    }
    SDL_UpdateWindowSurface(window);
}
void Funkcja3()
{
    int R, G, B;
    int C, M, Y;
    int c, m, y, k;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            R = getPixel(xx, yy).r;
            G = getPixel(xx, yy).g;
            B = getPixel(xx, yy).b;

            setPixel(xx + szerokosc / 2, yy, R, G, B);

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;

            k = min(min(C, M), Y);
            c = C - k;
            m = 0;
            y = Y - k;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;

            setPixel(xx + szerokosc / 2, yy, R, G, B);
        }
    }
    SDL_UpdateWindowSurface(window);
}
void Funkcja4()
{
    int R, G, B;
    int C, M, Y;
    int c, m, y, k;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            R = getPixel(xx, yy).r;
            G = getPixel(xx, yy).g;
            B = getPixel(xx, yy).b;

            setPixel(xx + szerokosc / 2, yy, R, G, B);

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;

            k = min(min(C, M), Y);
            c = 0;
            m = M - k;
            y = Y - k;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;

            setPixel(xx + szerokosc / 2, yy, R, G, B);
        }
    }
    SDL_UpdateWindowSurface(window);
}
void Funkcja5()
{
    int R, G, B;
    int C, M, Y;
    int c, m, y, k;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            R = getPixel(xx, yy).r;
            G = getPixel(xx, yy).g;
            B = getPixel(xx, yy).b;

            setPixel(xx + szerokosc / 2, yy, R, G, B);

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;
            k = min(min(C, M), Y);

            int czarny = 255 - k;

            setPixel(xx + szerokosc / 2, yy + wysokosc / 2, czarny, czarny, czarny);

            c = C - k;
            m = M - k;
            y = Y - k;
            k = 0;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;
            setPixel(xx + szerokosc / 2, yy, R, G, B);
            // k = 0;
        }
    }
    SDL_UpdateWindowSurface(window);
}
void Funkcja6()
{
    Uint8 R, G, B;
    float Y, Cb, Cr;
    for (int yy = 0; yy < wysokosc / 2; yy++)
    {
        for (int xx = 0; xx < szerokosc / 2; xx++)
        {
            SDL_Color color = getPixel(xx, yy);
            R = color.r;
            G = color.g;
            B = color.b;

            Y = 0.299 * R + 0.587 * G + 0.114 * B;
            Cb = 128 - 0.1687 * R - 0.3313 * G + 0.5 * B;
            Cr = 128 + 0.5 * R - 0.4187 * G - 0.0813 * B;

            Uint8 szary = (Uint8)Y;
            setPixel(xx + szerokosc / 2, yy + wysokosc / 2, szary, szary, szary);

            Uint8 cb = (Uint8)Cb;
            setPixel(xx, yy + wysokosc / 2, cb, cb, cb);

            Uint8 cr = (Uint8)Cr;
            setPixel(xx + szerokosc / 2, yy, cr, cr, cr);
        }
    }
    SDL_UpdateWindowSurface(window);
}

// --- NOWE METODY RASTERYZACYJNE (ZADANIA SPRAWOZDANIE) ---

// Uniwersalny algorytm Bresenhama dla dowolnego odcinka (linia3 ze skryptu, str. 15-16)
void linia3(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int kx = 1;
    int ky = 1;

    if (dx < 0) {
        dx = x1 - x2;
        kx = -1;
    }
    if (dy < 0) {
        dy = y1 - y2;
        ky = -1;
    }

    int x = x1;
    int y = y1;
    setPixel(x, y, R, G, B);

    if (dx >= dy) {
        int d = 2 * dy - dx;
        while (x != x2) {
            if (d >= 0) {
                x += kx;
                y += ky;
                d = d + 2 * (dy - dx);
            } else {
                x += kx;
                d = d + 2 * dy;
            }
            setPixel(x, y, R, G, B);
        }
    } else {
        int d = 2 * dx - dy;
        while (y != y2) {
            if (d >= 0) {
                y += ky;
                x += kx;
                d = d + 2 * (dx - dy);
            } else {
                y += ky;
                d = d + 2 * dx;
            }
            setPixel(x, y, R, G, B);
        }
    }
}

// Zadanie 1: Rasteryzacja elipsy algorytmem Bresenhama (str. 6-7)
void elipsa(int x_sr, int y_sr, int a, int b, Uint8 R, Uint8 G, Uint8 B) {
    long long a2 = (long long)a * a;
    long long b2 = (long long)b * b;

    // Część 1: Oś wiodąca OX
    int x = 0;
    int y = b;
    long long d = 4 * b2 - 4 * a2 * b + a2;

    while (b2 * x < a2 * y) {
        setPixel(x_sr + x, y_sr + y, R, G, B);
        setPixel(x_sr - x, y_sr + y, R, G, B);
        setPixel(x_sr + x, y_sr - y, R, G, B);
        setPixel(x_sr - x, y_sr - y, R, G, B);

        if (d < 0) {
            d = d + 8 * b2 * x + 12 * b2;
            x++;
        } else {
            d = d + 8 * b2 * x + 12 * b2 - 8 * a2 * y + 8 * a2;
            x++;
            y--;
        }
    }

    // Część 2: Oś wiodąca OY
    d = b2 * (2 * x + 1) * (2 * x + 1) + 4 * a2 * (y - 1) * (y - 1) - 4 * a2 * b2;

    while (y >= 0) {
        setPixel(x_sr + x, y_sr + y, R, G, B);
        setPixel(x_sr - x, y_sr + y, R, G, B);
        setPixel(x_sr + x, y_sr - y, R, G, B);
        setPixel(x_sr - x, y_sr - y, R, G, B);

        if (d < 0) {
            d = d + 8 * a2 * y + 12 * a2;
            y--;
        } else {
            d = d - 8 * b2 * x + 8 * b2 + 8 * a2 * y + 12 * a2;
            x++;
            y--;
        }
    }
}

// Zadanie 2: Rysowanie pustego kwadratu
void kwadrat(int x, int y, int a, Uint8 R, Uint8 G, Uint8 B) {
    linia3(x, y, x + a, y, R, G, B);
    linia3(x + a, y, x + a, y + a, R, G, B);
    linia3(x + a, y + a, x, y + a, R, G, B);
    linia3(x, y + a, x, y, R, G, B);
}

// Zadanie 3: Rysowanie wypełnionego kwadratu
void kwadratw(int x, int y, int a, Uint8 R, Uint8 G, Uint8 B) {
    for (int i = 0; i <= a; i++) {
        linia3(x, y + i, x + a, y + i, R, G, B);
    }
}

// Zadanie 4: Rysowanie pustego prostokąta
void prostokat(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B) {
    linia3(x, y, x + a, y, R, G, B);
    linia3(x + a, y, x + a, y + b, R, G, B);
    linia3(x + a, y + b, x, y + b, R, G, B);
    linia3(x, y + b, x, y, R, G, B);
}

// Zadanie 5: Rysowanie wypełnionego prostokąta
void prostokatw(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B) {
    for (int i = 0; i <= b; i++) {
        linia3(x, y + i, x + a, y + i, R, G, B);
    }
}

// Wywołanie testowe wszystkich nowych funkcjonalności pod klawiszem '7'
void Funkcja7()
{
    czyscEkran(0, 0, 0); // Czyszczenie tła na czarno

    // Test Elips (Zadanie 1)
    elipsa(150, 100, 80, 40, 255, 255, 0);   // Żółta elipsa pozioma
    elipsa(450, 150, 50, 100, 0, 255, 255);  // Turkusowa elipsa pionowa

    // Test Kwadratów (Zadanie 2 i 3)
    kwadrat(50, 220, 70, 255, 255, 255);     // Biały pusty kwadrat
    kwadratw(160, 220, 70, 255, 100, 100);   // Różowy wypełniony kwadrat

    // Test Prostokątów (Zadanie 4 i 5)
    prostokat(300, 250, 120, 60, 0, 255, 0);    // Zielony pusty prostokąt
    prostokatw(460, 280, 140, 50, 100, 100, 255); // Niebieski wypełniony prostokąt

    SDL_UpdateWindowSurface(window);
}

void Funkcja8()
{
    //...
    SDL_UpdateWindowSurface(window);
}
void Funkcja9()
{
    //...
    SDL_UpdateWindowSurface(window);
}
void setCMYK(int xx, int yy, Uint8 c, Uint8 m, Uint8 y, Uint8 k)
{
    Uint8 R, G, B;
    int C = c + k;
    int M = m + k;
    int Y = y + k;
    if (C > 255)
        C = 255;
    if (M > 255)
        C = 255;
    if (Y > 255)
        C = 255;
    R = 255 - C;
    G = 255 - M;
    B = 255 - Y;
    setPixel(xx, yy, R, G, B);
}
CMYK getCMYK(int xx, int yy)
{
    int C, M, Y, K;
    CMYK res;
    SDL_Color color = getPixel(xx, yy);
    C = 255 - color.r;
    M = 255 - color.g;
    Y = 255 - color.b;
    K = min(min(C, M), Y);
    res.c = C;
    res.m = M;
    res.y = Y;
    res.k = K;
    return res;
}
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc))
    {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);
        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;
        /* Obliczamy adres piksela */
        Uint8 *p1 = (Uint8 *)screen->pixels + (y * 2) * screen->pitch + (x * 2) * bpp;
        Uint8 *p2 = (Uint8 *)screen->pixels + (y * 2 + 1) * screen->pitch + (x * 2) * bpp;
        Uint8 *p3 = (Uint8 *)screen->pixels + (y * 2) * screen->pitch + (x * 2 + 1) * bpp;
        Uint8 *p4 = (Uint8 *)screen->pixels + (y * 2 + 1) * screen->pitch + (x * 2 + 1) * bpp;
        /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
        switch (bpp)
        {
        case 1: // 8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;
        case 2: // 16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;
        case 3: // 24-bit
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            }
            else
            {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4: // 32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;
        }
    }
}
void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    if ((x >= 0) && (x < szerokosc * 2) && (y >= 0) && (y < wysokosc * 2))
    {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);
        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;
        /* Obliczamy adres piksela */
        Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
        /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
        switch (bpp)
        {
        case 1: // 8-bit
            *p = pixel;
            break;
        case 2: // 16-bit
            *(Uint16 *)p = pixel;
            break;
        case 3: // 24-bit
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4: // 32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}
SDL_Color getPixel(int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc))
    {
        // określamy pozycję
        char *pPosition = (char *)screen->pixels;
        // przesunięcie względem y
        pPosition += (screen->pitch * y * 2);
        // przesunięcie względem x
        pPosition += (screen->format->BytesPerPixel * x * 2);
        // kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);
        // konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return (color);
}
SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface)
{
    SDL_Color color;
    Uint32 col = 0;
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc))
    {
        // określamy pozycję
        char *pPosition = (char *)surface->pixels;
        // przesunięcie względem y
        pPosition += (surface->pitch * y);
        // przesunięcie względem x
        pPosition += (surface->format->BytesPerPixel * x);
        // kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);
        // konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return (color);
}
void ladujBMP(char const *nazwa, int x, int y)
{
    SDL_Surface *bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy = 0; yy < bmp->h; yy++)
        {
            for (int xx = 0; xx < bmp->w; xx++)
            {
                kolor = getPixelSurface(xx, yy, bmp);
                setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
            }
        }
        SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }
}
void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc * 2, wysokosc * 2, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL)
    {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_UpdateWindowSurface(window);
    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (SDL_WaitEvent(&event))
    {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (event.type)
        {
        case SDL_QUIT:
            done = true;
            break;
            // sprawdzamy czy został wciśnięty klawisz
        case SDL_KEYDOWN:
        {
            // wychodzimy, gdy wciśnięto ESC
            if (event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
            if (event.key.keysym.sym == SDLK_1)
                Funkcja1();
            if (event.key.keysym.sym == SDLK_2)
                Funkcja2();
            if (event.key.keysym.sym == SDLK_3)
                Funkcja3();
            if (event.key.keysym.sym == SDLK_4)
                Funkcja4();
            if (event.key.keysym.sym == SDLK_5)
                Funkcja5();
            if (event.key.keysym.sym == SDLK_6)
                Funkcja6();
            if (event.key.keysym.sym == SDLK_7)
                Funkcja7();
            if (event.key.keysym.sym == SDLK_8)
                Funkcja8();
            if (event.key.keysym.sym == SDLK_9)
                Funkcja9();
            if (event.key.keysym.sym == SDLK_a)
                ladujBMP("obrazek1.bmp", 0, 0);
            if (event.key.keysym.sym == SDLK_s)
                ladujBMP("obrazek2.bmp", 0, 0);
            if (event.key.keysym.sym == SDLK_d)
                ladujBMP("obrazek3.bmp", 0, 0);
            if (event.key.keysym.sym == SDLK_f)
                ladujBMP("obrazek4.bmp", 0, 0);
            if (event.key.keysym.sym == SDLK_g)
                ladujBMP("obrazek5.bmp", 0, 0);
            if (event.key.keysym.sym == SDLK_b)
                czyscEkran(0, 0, 0);
            else
                break;
        }
        }
        if (done)
            break;
    }
    if (screen)
    {
        SDL_FreeSurface(screen);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}