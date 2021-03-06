#include <allegro.h>
#include<stdlib.h>

#define jack_width 53
#define jack_height 84


volatile long predkosc = 0;

void zwieksz_predkosc()
{
    predkosc++;
}
END_OF_FUNCTION( zwieksz_predkosc );
LOCK_VARIABLE( predkosc );
LOCK_FUNCTION( zwieksz_predkosc );


int main()
{
/* Inicjalizacja Allegro */
/*-----------------------*/
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0 );
    install_timer();
    install_int_ex( zwieksz_predkosc, BPS_TO_TIMER( 150 ) );
    srand(time(NULL));


/* Grafika */
/*---------*/
BITMAP * bufor = NULL;
BITMAP *tlo = NULL;
BITMAP *jack =NULL;
BITMAP *jack_stop=NULL;
BITMAP *rzecz = NULL;
FONT *czcionka = NULL;

bufor = create_bitmap( 1024, 768 );

if( !bufor )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc bufora !" );
    allegro_exit();
    return 0;
}
tlo = load_bmp("tlo.bmp",default_palette);
if( !tlo )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc tla !" );
    allegro_exit();
    return 0;
}
jack = load_bmp("jackszablon.bmp",default_palette);
if( !jack )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc Jacka !" );
    allegro_exit();
    return 0;
}
jack_stop= load_bmp("jack.bmp",default_palette);
if( !jack_stop )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc Jacka Stop !" );
    allegro_exit();
    return 0;
}
rzecz = load_bmp("rzecz.bmp",default_palette);
if( !rzecz )
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc rzeczy !" );
    allegro_exit();
    return 0;
}

czcionka =load_font("oet.pcx",default_palette,NULL);
if(!czcionka)
{
   set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message( "Nie moge utworzyc czcionki !" );
    allegro_exit();
    return 0;
}

/* Poczatkowe wartosci kierunku i polozenia obiekt�w */
/*---------------------------------------------------*/
int jack_kierunek=0;
int jack_x = 400, jack_y = 400;
int rzecz_x = rand() % (1024-jack_width), rzecz_y = rand() % (786-jack_height);
int klatki;
int wynik = 0;
int zebrane= 0;

/* Sterowanie */
/*------------*/
while( !key[ KEY_ESC ] )
{
    while( predkosc > 0 )
    {
        jack_kierunek = 0;

        if( key[ KEY_LEFT ] ){jack_kierunek = 4; jack_x--;}

        if( key[ KEY_RIGHT ] ) {jack_kierunek = 6;jack_x++;}

        if( key[ KEY_UP ] ) {jack_kierunek = 8;jack_y--;}

        if( key[ KEY_DOWN ] ) {jack_kierunek = 2;jack_y++;}

        predkosc--;

        klatki++;
        if( klatki > 80 ) klatki = 0;
    }

/*Czyszczenie bufora*/
/*------------------*/
    clear_to_color( bufor, makecol(255,0,255));
    rest(1);
    blit(tlo,bufor,0,0,0,0,1024,768);

/* Uniemozliwienie wychodzenia Jacka poza ekran */
/*----------------------------------------------*/
    jack_x=MAX(0,MIN(jack_x,1024-jack_width));
    jack_y=MAX(0,MIN(jack_y,768-jack_height));

/* Sterowanie animacja */
/*---------------------*/

   if(jack_kierunek==0)
        {
            masked_blit( jack_stop, bufor,0,0,jack_x, jack_y,jack_width, jack_height );
        }
/* Lewo */
/*------*/
    if( klatki < 20 && jack_kierunek==4 )
        {
            masked_blit( jack, bufor,jack_width*0,jack_height*3,jack_x, jack_y,jack_width, jack_height );
        }
    if( klatki >= 20 && klatki < 40 && jack_kierunek==4 )
        {
            masked_blit(jack, bufor,jack_width*1,jack_height*3,jack_x, jack_y,jack_width,jack_height) ;
        }
    if( klatki >= 40 && klatki < 60 && jack_kierunek==4 )
        {
            masked_blit( jack, bufor,jack_width*2,jack_height*3,jack_x, jack_y,jack_width,jack_height  );
        }
    if(klatki>=60 && klatki <=80 && jack_kierunek==4)
        {
            masked_blit(jack, bufor, jack_width*3,jack_height*3,jack_x,jack_y,jack_width,jack_height);
        }
/* Prawo */
/*-------*/
    if( klatki < 20 && jack_kierunek==6 )
        {
            masked_blit( jack, bufor,jack_width*0,jack_height*2,jack_x, jack_y,jack_width,jack_height );
        }
    if( klatki >= 20 && klatki < 40 && jack_kierunek==6 )
        {
            masked_blit(jack, bufor,jack_width*1,jack_height*2,jack_x, jack_y,jack_width,jack_height) ;
        }
    if( klatki >= 40 && klatki < 60 && jack_kierunek==6 )
        {
            masked_blit( jack, bufor,jack_width*2,jack_height*2,jack_x, jack_y,jack_width,jack_height );
        }
    if(klatki>=60 && klatki <=80 && jack_kierunek==6)
        {
            masked_blit(jack, bufor, jack_width*3,jack_height*2,jack_x,jack_y,jack_width,jack_height);
        }
/* Gora */
/*------*/
    if( klatki < 20 && jack_kierunek==8 )
        {
            masked_blit( jack, bufor,jack_width*0,jack_height*1,jack_x, jack_y,jack_width,jack_height );
        }
    if( klatki >= 20 && klatki < 40 && jack_kierunek==8 )
        {
            masked_blit(jack, bufor,jack_width*1,jack_height*1,jack_x, jack_y,jack_width,jack_height) ;
        }
    if( klatki >= 40 && klatki < 60 && jack_kierunek==8 )
        {
            masked_blit( jack, bufor,jack_width*2,jack_height*1,jack_x, jack_y,jack_width,jack_height );
        }
    if(klatki>=60 && klatki <=80 && jack_kierunek==8)
        {
            masked_blit(jack, bufor, jack_width*3,jack_height*1,jack_x,jack_y,jack_width,jack_height);
        }
/* Dol */
/*-----*/
    if( klatki < 20 && jack_kierunek==2 )
        {
            masked_blit( jack, bufor,jack_width*0,jack_height*0,jack_x, jack_y,jack_width,jack_height );
        }
    if( klatki >= 20 && klatki < 40 && jack_kierunek==2 )
        {
            masked_blit(jack, bufor,jack_width*1,jack_height*0,jack_x, jack_y,jack_width,jack_height) ;
        }
    if( klatki >= 40 && klatki < 60 && jack_kierunek==2 )
        {
            masked_blit( jack, bufor,jack_width*2,jack_height*0,jack_x, jack_y,jack_width,jack_height  );
        }
    if(klatki>=60 && klatki <=80 && jack_kierunek==2)
        {
            masked_blit(jack, bufor, jack_width*3,jack_height*0,jack_x,jack_y,jack_width,jack_height);
        }

/* Rysowanie medalionu na ekranie */
/*-----------------------------*/
    masked_blit(rzecz, bufor,0,0,rzecz_x,rzecz_y,64,64);

/* Zbieranie i tworzenie nowego medalionu */
/*----------------------------------------*/
  textprintf_ex(bufor,czcionka,20,0,makecol(0,0,0),-1,"Wynik: %i",wynik+100*zebrane);
  textprintf_ex(bufor,czcionka,750,0,makecol(0,0,0),-1,"Zebrane: %i",zebrane);

    if(abs(jack_x-rzecz_x)<20 && abs(jack_y-rzecz_y)<60)
        {
            zebrane++;
            rzecz_x=rand()%1000;
            rzecz_y=rand()%750;
        }


/* Wyswietlanie */
/*--------------*/

    blit( bufor, screen, 0, 0, 0, 0, 1024, 768 );
    blit(tlo,bufor,0,0,0,0,1024,786);
}

remove_int( zwieksz_predkosc );
destroy_bitmap( jack );
destroy_bitmap(jack_stop);
destroy_bitmap(rzecz);
destroy_bitmap(tlo);
destroy_bitmap( bufor );
allegro_exit();

return 0;
}
END_OF_MAIN()
