/*
 * TexturesUtils.h
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#ifndef TEXTURESUTILS_H_
#define TEXTURESUTILS_H_

////do tekstur
//GLUquadric *podloga;
//GLuint woodTexture; //deskryptor tekstury drewna na podlodze
//
////funkcja zwraca deskryptor tekstury i laduje ja z pliku
//int LoadTextureFromBitmapFile(char *filename) {
//	FILE * file;
//	char temp;
//	long i;
//
//	BITMAPINFOHEADER infoheader; //windows.h zawiera opis naglowka bitmapy
//	unsigned char *bitmap_data; //ale miejsce na dane pikseli musimy zapewnic sami
//
//	GLuint textureID; //deskryptor tekstury, to bedziemy zwracac (= unsigned int)
//
//	file = fopen(filename, "rb");
//	if(file == NULL) //nie udalo sie otworzyc pliku do czytania binarnego
//	{
//		printf("Blad otwarcia pliku %s\n", filename);
//		return -1;
//	}
//
//	//odczytujemy rozmiar bitmapy
//	fseek(file, 18, SEEK_CUR);  //przesuwamy sie na odczytanie rozmiaru bitmapy
//	fread(&infoheader.biWidth, sizeof(int), 1, file); //czytamy szerokosc w pikselach
//	fread(&infoheader.biHeight, sizeof(int), 1, file); //i wysokosc w pikselach
//
//	//te rozmiary musza byc u nas dodatnie, a w bitmapie moga byc ujemne
//	if(infoheader.biWidth < 0)
//		infoheader.biWidth = -infoheader.biWidth;
//	if(infoheader.biHeight < 0)
//		infoheader.biHeight = -infoheader.biHeight;
//
//	//odczytujemy ilosc wartsw kolorow (powinna wynosic 1)
//	fread(&infoheader.biPlanes, sizeof(short int), 1, file);
//	if (infoheader.biPlanes != 1) //jak nie, to blad
//	{
//		printf("Liczba wartsw kolorow w pliku %s wynosi: %u a powinna wynosic: 1!\n", filename, infoheader.biPlanes);
//		return 0;
//	}
//
//	//odczytujemy liczbe bitow na piksel
//	fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
//	if (infoheader.biBitCount != 24) //obslugujemy tylko 24-bitowe bitmapy
//	{
//		printf("Bitmapa %s jest %d-bitowa, a powinna byc 24-bitowa!\n", filename, infoheader.biBitCount);
//		return 0;
//	}
//
//	//rezerwujemy odpowiednia ilosc miejsca na mape pikseli
//	bitmap_data = (unsigned char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
//	if (bitmap_data == NULL) //nie udalo sie zaalokowac
//	{
//		printf("Blad: nie udalo sie zaalokowac miejsca na dane z bitmapy!\n");
//		return 0;
//	}
//
//	//wczytujemy bitmape z pliku do pamieci
//	fseek(file, 24, SEEK_CUR); //ustawiamy sie na poczatek danych pikseli
//	i = fread(bitmap_data, 1, infoheader.biWidth * infoheader.biHeight * 3, file);
//	if(i != infoheader.biWidth * infoheader.biHeight * 3) //powinnismy odczytac tyle bajtow, ile wyzej powiedzielismy
//	{
//		printf("Nie udalo sie odczytac danych z pliku %s!\n", filename);
//		return 0;
//	}
//	//plik juz nam nie bedzie potrzebny, mozna go zamknac
//	fclose(file);
//
//	//trzeba jeszcze odwrocic kolejnosc kolorw z BGR na RGB
//	for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3)
//	{
//		temp = bitmap_data[i];
//		bitmap_data[i] = bitmap_data[i+2];
//		bitmap_data[i+2] = temp;
//	}
//
//	glGenTextures(1, &textureID); //tworzy deskryptor tekstury (jeden) w zmiennej textureID
//	glBindTexture(GL_TEXTURE_2D, textureID); //dolacza ta teksture do tekstur 2D
//
//	//ustawianie parametrow tekstury
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //powtzraznie tekstury w poziomie
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //i w pionie
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //blisko: wyliczamy pliksel jako srednia czterech sasiednich
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //daleko: tak jak wyzej, ale korzystamy z najblizszej mipmapy
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //sposob nakladania tekstury: modulate - mnozy kolor wyliczony np. z oswietlenia z kolorem tekstury
//
//	//tworzenie tekstury zrozumialej dla OpenGL
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_data);
//
//	//tworzenie mipmap (dla wiekszych odleglosci od ekranu)
//	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, bitmap_data);
//
//	//zwalniamy pamiec, teraz teksture trzyma OpenGL u siebie
//	free(bitmap_data);
//
//	return (textureID);
//} //end of LoadBitmap()
//
//
//
//void loadTextures() {
//	podloga = gluNewQuadric();
//	gluQuadricTexture(podloga, GL_TRUE);
//	woodTexture = LoadTextureFromBitmapFile("img/wood.bmp");
////	wall = gluNewQuadric();
////	gluQuadricTexture(wall, GL_TRUE);
////	wallTexture = LoadBitmap("img/wall.bmp");
////	ceiling = gluNewQuadric();
////	gluQuadricTexture(ceiling, GL_TRUE);
////	ceilingTexture = LoadBitmap("img/ceiling.bmp");
////	red = gluNewQuadric();
////	gluQuadricTexture(red, GL_TRUE);
////	redTexture = LoadBitmap("img/red.bmp");
////	dark = gluNewQuadric();
////	gluQuadricTexture(dark, GL_TRUE);
////	darkTexture = LoadBitmap("img/dark.bmp");
//}

#endif /* TEXTURESUTILS_H_ */
