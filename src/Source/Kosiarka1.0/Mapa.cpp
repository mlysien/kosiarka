#include<cstdlib>
#include<cstdio>
#include "Mapa.h"

//konstruktor
Mapa::Mapa(){
	Mwidth=  20;
	Mheight= 15;

	Player=  2;
	Grass=   1;
	Stone=   0;
	Water=   4;
	Parking= 5;
	Flower=  6;
}


//funkcja ³aduje mapê z pliku
bool Mapa::LoadMap(const char *plik){

	//otwarcie pliku
	FILE *map= fopen(plik, "r");

	//je¿eli coœ posz³o Ÿle
	if(!map) return false;

	for(int j=0; j<15; j++){
		
		char linia[300];
		
		fgets(linia, sizeof(linia), map);

		//sprawdzenie czy nie plik siê nie skoñczy³
		if(feof(map)){
			fclose(map);
			return false;
		}

		for(int i= 0; i<20; i++){

			switch(linia[i]){
			//trawa => . | kamieñ=> x
			case 'o': Map[j][i]= Player; break;
			case '.': Map[j][i]= Grass; break;
			case 'x': Map[j][i]= Stone; break;
			case 'w': Map[j][i]= Water; break;
			case 'k': Map[j][i]= Flower; break;
			case 'p': Map[j][i]= Parking; break;

			default: fclose(map); return false; 
			}

		}

	}

	//je¿eli wszystko posz³o dobrze
	fclose(map);
	return true;
}
 