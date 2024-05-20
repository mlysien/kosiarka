#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<conio.h>
#include <sstream>
#include<windows.h>

#include<SDL_ttf.h>
#include<SDL.h>
#include<SDL_image.h>

#include "Scena.h"
#include "Mapa.h"
#include "Gracz.h"
#include "Kolizja.h"

//G£ÓWNA FUNKCJA MAIN
int main( int argc, char * args[] ){


	//inicjalizacja obiektów
	Gracz kosiarka;
	Scena stage, trawa, kamien, woda, parking, kwiatek, gfKosiarka,
		TrawaSkoszona, Score, background, KosiarkaCrashr, KosiarkaCrashl,
		KosiarkaCrashd, KosiarkaCrashu;
	Mapa mapa;

	//flagi przerwania pêtli
	bool KoniecGry=      false;
	bool KoniecPoziomu = false;


	//zmienne roztrzygaj¹ce zakoñczenie poziomu T-rawa, S-iano
	static int Tliczba, Sliczba;

	//zmienna przechowuj¹ca zu¿yte paliwo
	static int Ostrza = 100;

	static int Paliwo, AddFuel, *wskaznik, superwynik;

	wskaznik=&AddFuel;

		
	static float StartFuel, EndFuel; 




	//zmienna przechowuj¹ca aktualny poziom
	const char *TabLVL[]=
	{"systemlevels/lvl1.lvl",//zaczynamy od 1 poziomu
	 "system/levels/lvl1.lvl",
	 "system/levels/lvl2.lvl",
	 "system/levels/lvl3.lvl",
	 "system/levels/lvl4.lvl",
	 "system/levels/lvl5.lvl",
	 "system/levels/lvl6.lvl",
	 "system/levels/lvl7.lvl",
	 "system/levels/lvl8.lvl",
	 "system/levels/lvl9.lvl",
	 "system/levels/lvl10.lvl",
	 "system/levels/lvl11.lvl",
	 "system/levels/lvl12.lvl",
	 "system/levels/lvl13.lvl",
	 "system/levels/lvl14.lvl",
	 "system/levels/lvl15.lvl",
	};
	
	//tablica z iloœciami dostêpnego paliwa na odpowiednich poziomach
	static int TABFUEL[]=
	{
		1,    //0 level
		70,		//1
		230,	//2
		200,    //3
		230,	//4
		230,	//5
		240,	//6
		150,	//7
		260,	//8 
		280,	//9
		255,	//10 	
		200,	//11
		180,	//12
		160,	//13
		200,	//14
		0		//15 - poziom extreme, czyli musisz go przejœæ na paliwie jakie dotychczas nazbiera³eœ
	};

	//aktualny poziom
	static int level= 1;


	//przechowywanie zdarzeñ
	Uint8 * keystate = SDL_GetKeyState(0);
	SDL_Event zdarzenie;

	unsigned int LastFrame = SDL_GetTicks();
	//zmienna to przechowywania iloœci klatek na sekunde
	float fps = 0.0f; 
	static int Czas;

	//uruchomienie SDL'a
	stage.RunSDL(640, 480, 32, "Kosiarka", true);

	//za³adowanie spritów
	gfKosiarka.texture= 
	gfKosiarka.LoadSprite("system/textures/kosiarka.bmp");
	
	trawa.texture= 
	trawa.LoadSprite("system/textures/trawa.bmp");
	
	kamien.texture= 
	kamien.LoadSprite("system/textures/kamien.bmp");
	
	parking.texture= 
	parking.LoadSprite("system/textures/parking.bmp");
	
	woda.texture= 
	woda.LoadSprite("system/textures/woda.bmp");
	
	kwiatek.texture= 
	kwiatek.LoadSprite("system/textures/kwiatek.bmp");
	
	TrawaSkoszona.texture= 
	TrawaSkoszona.LoadSprite("system/textures/trawa2.bmp");

	KosiarkaCrashr.texture= 
	KosiarkaCrashr.LoadSprite("system/textures/kosiarkacrashr.bmp");

	KosiarkaCrashl.texture= 
	KosiarkaCrashl.LoadSprite("system/textures/kosiarkacrashl.bmp");

	KosiarkaCrashd.texture= 
	KosiarkaCrashd.LoadSprite("system/textures/kosiarkacrashd.bmp");

	KosiarkaCrashu.texture= 
	KosiarkaCrashu.LoadSprite("system/textures/kosiarkacrashu.bmp");

		background.texture= 
		 background.LoadSprite("system/textures/background.bmp");


//G£ÓWNA PÊTLA GRY

while(KoniecGry!=true){

	
	//za³adowanie map
	mapa.LoadMap(TabLVL[level]);

	//wyœwietlenie mapy
	for(int i=0; i<15; i++){
		for(int j=0; j<20; j++){
			
			//wykrycie pozycji gracza na mapie
			if(mapa.Map[i][j]==2){
				kosiarka.pozX= j;
				kosiarka.pozY= i;
			trawa.ShowSprite(j*32,i*32,trawa.texture, stage.EKRAN);
			}
			//wykrycie pozycji trawy na mapie
			if(mapa.Map[i][j]==1){
			trawa.ShowSprite(j*32,i*32,trawa.texture, stage.EKRAN);
			Tliczba++;
			}
			//wykrycie pozycji kamieni na mapie
			if(mapa.Map[i][j]==0){
		   kamien.ShowSprite(j*32,i*32,kamien.texture, stage.EKRAN);
			}
			//wykrycie pozycji wody na mapie
			if(mapa.Map[i][j]==4){
		    woda.ShowSprite(j*32,i*32,woda.texture, stage.EKRAN);
			}			
			//wykrycie pozyji kostki brukowej - parkingu na mapie
			if(mapa.Map[i][j]==5){
			parking.ShowSprite(j*32,i*32,
		    parking.texture, stage.EKRAN);
			}
			//wykrycie pozycji kwiatków na mapie
			if(mapa.Map[i][j]==6){
		    kwiatek.ShowSprite(j*32,i*32,
			kwiatek.texture, stage.EKRAN);
			}


		}
	
	//wyczyszczenie ekranu.
	SDL_Flip(stage.EKRAN);
	
	//zakoñczenie wczytywania poziomu
	KoniecPoziomu= false;

	}//koniec wczytywania mapy
	
//PÊTLA POZIOMU

	while(KoniecPoziomu!=true){

        while( SDL_PollEvent(&zdarzenie) )
        {		
			//sterowanie postaci¹
			if( keystate[ SDLK_RIGHT ] )
			{
				//strza³ka w prawo

				//zmiana pozycji kosiarki
				kosiarka.pozX++;

				//za³adowanie tekstury kosiarki
				gfKosiarka.texture= 
				gfKosiarka.LoadSprite
				("system/textures/kosiarka.bmp");
				//granica ekranu- prawa
				
				//Kolizje
				
				//kolizja z praw¹ krawêdzi¹ ekranu
				if(kosiarka.pozX>19){
					kosiarka.pozX=19;
				}
				//"kolizja" z traw¹
				else{
				if((mapa.Map[kosiarka.pozY][kosiarka.pozX]==1) && 
				   (mapa.Map[kosiarka.pozY][kosiarka.pozX]!=3)){
					
				//w tym miejscu pojawia siê skoszona trawa
				mapa.Map[kosiarka.pozY][kosiarka.pozX]=3;

				//wyœwietlenie skoszonej trawy
				TrawaSkoszona.ShowSprite
				((kosiarka.pozX-1)*32,(kosiarka.pozY)*32,							
				TrawaSkoszona.texture, stage.EKRAN);
				
				//zwiêkszenie liczby skoszonej trawy
				Sliczba++;
				}
				//je¿eli w tym miejscu ju¿ znajduje siê skoszona					//trawa	
				else{
				TrawaSkoszona.ShowSprite((kosiarka.pozX-1)*32,
				(kosiarka.pozY)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
				}
				//kolizja z kamieniami
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==0){

					KosiarkaCrashr.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashr.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					kamien.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, kamien.texture, stage.EKRAN);
					
					--kosiarka.pozX;

					Ostrza -= 10;
				}
				//kolizja z parkingiem
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==5){


					KosiarkaCrashr.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashr.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					parking.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, parking.texture, stage.EKRAN);
					
					--kosiarka.pozX;
				

					Ostrza -= 10;
				}
				//kolizja z wod¹
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==4){
					--kosiarka.pozX;
					Ostrza -= 10;
				}
				}
				++Paliwo;
			}
			if( keystate[ SDLK_LEFT ] )
			{
				//klawisz w lewo
				kosiarka.pozX--;

				//za³adowanie tekstury
				gfKosiarka.texture= 
				gfKosiarka.LoadSprite
				("system/textures/kosiarkal.bmp");
				
				//kolizja z lew¹ krawêdzi¹ ekranu
				if(kosiarka.pozX<0){
					kosiarka.pozX=0;
				}				
				else{
			if((mapa.Map[kosiarka.pozY][kosiarka.pozX]==1) && 
			   (mapa.Map[kosiarka.pozY][kosiarka.pozX]!=3)){

				mapa.Map[kosiarka.pozY][kosiarka.pozX]=3;

				TrawaSkoszona.ShowSprite((kosiarka.pozX+1)*32,
				(kosiarka.pozY)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
				
				Sliczba++;
			
			}else{
				TrawaSkoszona.ShowSprite((kosiarka.pozX+1)*32,
				(kosiarka.pozY)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
			}
				//kolizja z kamieniami
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==0){

					KosiarkaCrashl.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashl.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					kamien.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, kamien.texture, stage.EKRAN);
					
					++kosiarka.pozX;

					Ostrza -= 10;
				}
				//kolizja z parkingiem
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==5){

					KosiarkaCrashl.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashl.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					parking.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, parking.texture, stage.EKRAN);

					++kosiarka.pozX;

					Ostrza -= 10;
				}
				//kolizja z wod¹
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==4){
					++kosiarka.pozX;
					Ostrza -= 10;
				}
			}
			++Paliwo;
			}
			
			if( keystate[ SDLK_UP ] )
			{
				kosiarka.pozY--;
				gfKosiarka.texture= 
				gfKosiarka.LoadSprite
				("system/textures/kosiarkau.bmp");
				if(kosiarka.pozY<0){
					kosiarka.pozY=0;
				}
				else{
			if((mapa.Map[kosiarka.pozY][kosiarka.pozX]==1) && 
			   (mapa.Map[kosiarka.pozY][kosiarka.pozX]!=3)){

				mapa.Map[kosiarka.pozY][kosiarka.pozX]=3;
				
				TrawaSkoszona.ShowSprite((kosiarka.pozX)*32,
				(kosiarka.pozY+1)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
				Sliczba++;
			
			}else{
				TrawaSkoszona.ShowSprite((kosiarka.pozX)*32,
				(kosiarka.pozY+1)*32, TrawaSkoszona.texture, stage.EKRAN);
			}
				//kolizja z kamieniami
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==0){

					KosiarkaCrashu.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashu.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					kamien.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, kamien.texture, stage.EKRAN);
					
					++kosiarka.pozY;
	
					Ostrza -= 10;
				}
				//kolizja z parkingiem
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==5){

					KosiarkaCrashu.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashu.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					parking.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, parking.texture, stage.EKRAN);
					
					++kosiarka.pozY;
			
					Ostrza -= 10;
				}
				//kolizja z wod¹
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==4){
					++kosiarka.pozY;
					Ostrza -= 10;
				}
			}
				++Paliwo;
			}
			if( keystate[ SDLK_DOWN ] )
			{
				kosiarka.pozY++;
				gfKosiarka.texture= 
				gfKosiarka.LoadSprite
				("system/textures/kosiarkad.bmp");
				if(kosiarka.pozY>14){
					kosiarka.pozY=14;
				}		
				else{
			if((mapa.Map[kosiarka.pozY][kosiarka.pozX]==1) && 
			   (mapa.Map[kosiarka.pozY][kosiarka.pozX]!=3)){

				mapa.Map[kosiarka.pozY][kosiarka.pozX]=3;

				TrawaSkoszona.ShowSprite((kosiarka.pozX)*32,
				(kosiarka.pozY-1)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
				Sliczba++;
			}else{
				TrawaSkoszona.ShowSprite((kosiarka.pozX)*32,
				(kosiarka.pozY-1)*32, TrawaSkoszona.texture, 
				stage.EKRAN);
			}
				//kolizja z kamieniami
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==0){

					KosiarkaCrashd.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashd.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					kamien.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, kamien.texture, stage.EKRAN);

					--kosiarka.pozY;

					Ostrza -= 10;
				}
				//kolizja z parkingiem
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==5){

					KosiarkaCrashd.ShowSprite((kosiarka.pozX)*32,
					(kosiarka.pozY)*32, KosiarkaCrashd.texture, 
					stage.EKRAN);

					SDL_Flip(stage.EKRAN);

					SDL_Delay(200);

					parking.ShowSprite((kosiarka.pozX)*32, (kosiarka.pozY)*32, parking.texture, stage.EKRAN);
					
					--kosiarka.pozY;

					Ostrza -= 10;
				}
				//kolizja z wod¹
				if(mapa.Map[kosiarka.pozY][kosiarka.pozX]==4){
					--kosiarka.pozY;
					Ostrza -= 10;
				}

			}
				++Paliwo;
			}
			
			if( keystate[ SDLK_ESCAPE ] )
			{
				KoniecGry= true;
				KoniecPoziomu= true;
			}

			}//koniec sterowania postaci¹

		//aktualizacja ekranu

		//wyœwietlenie postaci
		gfKosiarka.ShowSprite(kosiarka.pozX*32, kosiarka.pozY*32,
								  gfKosiarka.texture, stage.EKRAN);

		

		//update ekranu
		SDL_Flip(stage.EKRAN);


		//Obliczenie ró¿nicy miêdzy klatkami
		unsigned int CurrentFrame = SDL_GetTicks();
		fps= (float)(CurrentFrame - LastFrame)/1000.0f;
		LastFrame= CurrentFrame;


		//sprawdzenie czy ostrza siê ju¿ ca³kowicie nie stêpi³y
		if(Ostrza<=0){

	background.texture= 
		 background.LoadSprite("system/textures/background.bmp");


	TTF_Init();

	//czcionka

	TTF_Font *font = 0;
	font = TTF_OpenFont( "system/font/gunplay.ttf", 40 );
	//kolor czcionki
	SDL_Color textColor = { 255, 102, 0 };
	SDL_Color red= {255, 0, 0};
	
	//stan paliwa
	std::stringstream StanPaliwa;	
	std::stringstream DozwolonePaliwo;
	std::stringstream StanOstrzy;
	std::stringstream JakiPoziom;

		//Wyœwietlenie ekranu ze statystykami

		//Utworzenie powierzchni
		SDL_Surface *PoziomOstrzy = 0;
		SDL_Surface *PoziomPaliwa2= 0;
		SDL_Surface *Capition = 0;	


		DozwolonePaliwo<<"The remaining fuel: "<<(TABFUEL[level]-Paliwo)*0.01<<"l"; 
		StanOstrzy<<"Blades condition: "<<Ostrza<<"%";
		JakiPoziom<<"LEVEL "<<level<<" FAILED!";


		PoziomPaliwa2 = TTF_RenderText_Solid( font, 
					DozwolonePaliwo.str().c_str(),red );
		PoziomOstrzy =  TTF_RenderText_Solid( font, 
					StanOstrzy.str().c_str(),red );
		Capition=  TTF_RenderText_Solid( font, 
					JakiPoziom.str().c_str(),red );


		Score.ShowSprite(1,1, Capition, background.texture);
		Score.ShowSprite(1,40, PoziomOstrzy, background.texture);
		Score.ShowSprite(1,80, PoziomPaliwa2, background.texture);

		background.ShowSprite(0,0, background.texture, stage.EKRAN);
		SDL_Flip(stage.EKRAN);
		SDL_Flip(background.texture);
		SDL_Delay(3000);
		
		SDL_FreeSurface(background.texture);
	
		TTF_Quit();	

		
		
		KoniecPoziomu= true;
		KoniecGry= true;

		break;

		}


		//sprawdzenie czy nie zabrak³o paliwa
		if(Paliwo>=TABFUEL[level]+AddFuel){

	background.texture= 
		 background.LoadSprite("system/textures/background.bmp");


	TTF_Init();

	//czcionka

	TTF_Font *font = 0;
	font = TTF_OpenFont( "system/font/gunplay.ttf", 40 );
	//kolor czcionki
	SDL_Color textColor = { 255, 102, 0 };
	SDL_Color red= {255, 0, 0};
	//stan paliwa
	std::stringstream DozwolonePaliwo;
	std::stringstream StanOstrzy;
	std::stringstream JakiPoziom;


		//Wyœwietlenie ekranu ze statystykami

		//Utworzenie powierzchni
		SDL_Surface *PoziomPaliwa2 = 0;
		SDL_Surface *PoziomOstrzy = 0;
		SDL_Surface *Capition = 0;	


		DozwolonePaliwo<<"The remaining fuel: "<<(TABFUEL[level]-Paliwo)*0.01<<"l"; 
		StanOstrzy<<"Blades condition: "<<Ostrza<<"%";
		JakiPoziom<<"LEVEL "<<level<<" FAILED!";


		PoziomPaliwa2 = TTF_RenderText_Solid( font, 
					DozwolonePaliwo.str().c_str(),red );
		PoziomOstrzy =  TTF_RenderText_Solid( font, 
					StanOstrzy.str().c_str(),red );
		Capition=  TTF_RenderText_Solid( font, 
					JakiPoziom.str().c_str(),red );


		Score.ShowSprite(1,1, Capition, background.texture);
		Score.ShowSprite(1,40, PoziomOstrzy, background.texture);
		Score.ShowSprite(1,80, PoziomPaliwa2, background.texture);

		background.ShowSprite(0,0, background.texture, stage.EKRAN);
		SDL_Flip(stage.EKRAN);
			SDL_Flip(background.texture);
		SDL_Delay(3000);
	
		SDL_FreeSurface(background.texture);
		TTF_Quit();	
		KoniecPoziomu= true;
		KoniecGry= true;
			
		break;
		


		}
	
		//sprawdzenie czy gracz zakoñczy³ poziom
		if(Sliczba==Tliczba){

			//ustawienie iloœci paliwa na nastêpny poziom
			AddFuel+= (TABFUEL[level]-Paliwo);


	background.texture= 
		 background.LoadSprite("system/textures/background.bmp");


	TTF_Init();

	//czcionka

	TTF_Font *font = 0;
	font = TTF_OpenFont( "system/font/gunplay.ttf", 40 );
	//kolor czcionki
	SDL_Color textColor = { 0, 255, 0 };
	
	//stan paliwa

	std::stringstream DozwolonePaliwo;
	std::stringstream StanOstrzy;
	std::stringstream JakiPoziom;
		std::stringstream tescik;

		//Wyœwietlenie ekranu ze statystykami

		//Utworzenie powierzchni
		SDL_Surface *PoziomOstrzy = 0;
		SDL_Surface *Test= 0;
		SDL_Surface *PoziomPaliwa2= 0;
		SDL_Surface *Capition = 0;	


		DozwolonePaliwo<<"The remaining fuel: "<<(TABFUEL[level]-Paliwo)*0.01<<"l"; 
		tescik<<"Additional fuel: "<<AddFuel*0.01<<"l";
		StanOstrzy<<"Blades condition: "<<Ostrza<<"%";
		JakiPoziom<<"LEVEL "<<level<<" COMPLETED!";

		PoziomPaliwa2 = TTF_RenderText_Solid( font, 
					DozwolonePaliwo.str().c_str(),textColor );

				Test = TTF_RenderText_Solid( font, 
					tescik.str().c_str(),textColor );

		PoziomOstrzy =  TTF_RenderText_Solid( font, 
					StanOstrzy.str().c_str(),textColor );
		Capition=  TTF_RenderText_Solid( font, 
					JakiPoziom.str().c_str(),textColor );

		Score.ShowSprite(1,1, Capition, background.texture);
		Score.ShowSprite(1,40, PoziomOstrzy, background.texture);
		Score.ShowSprite(1,80, PoziomPaliwa2, background.texture);
		Score.ShowSprite(1,120, Test, background.texture);

		background.ShowSprite(0,0, background.texture, stage.EKRAN);

		SDL_Flip(stage.EKRAN);
		SDL_Flip(background.texture);

		SDL_Delay(3000);
		SDL_FreeSurface(background.texture);
		TTF_Quit();

			
			//wyzerowanie stanu paliwa
			Paliwo= 0;
			//ustawienie nastêpnego poziomu
			level++;

			KoniecPoziomu= true;

			
		}

	}//KONIEC PÊTLI POZIOMU
	//nastêpny poziom

	if(level==16){
		KoniecGry=true;
	}
	
}//KONIEC G£ÓWNEJ PÊTLI

//wyœwietlenie ekranu po¿egnalnego


//posprz¹tanie po programie
TTF_Quit();
SDL_Quit();
SDL_FreeSurface(gfKosiarka.texture);
SDL_FreeSurface(trawa.texture);
SDL_FreeSurface(kamien.texture);
SDL_FreeSurface(TrawaSkoszona.texture);
//SDL_FreeSurface(lvlcompleted.texture);
SDL_FreeSurface(stage.EKRAN);
	return 0;
}
