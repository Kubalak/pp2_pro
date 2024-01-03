#pragma once
#ifndef PLAYER_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
*/
#define PLAYER_H
/**
* Definicja dla gracza
*/
#define ALIVE 1
/**
* Definicja dla gracza
*/
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
/**
* Struktura zawieraj�ca dane gracza  - wynik, ilo�� �y� aktywne bonusy i czasy ich trwania.
*/
struct player
{
	/**
	*	Ilo�� zdobytych przez gracza punkt�w
	*/
	unsigned int score;
	/**
	*	Ilo�c pozosta�ych �y�
	*/
	char lives;
	/**
	* Poszczeg�lne bonusy - wed�ug kolejnych bit�w w zmiennej<br>
	*0000 0000 (0) - �aden nie jest aktywny<br>
	*0000 0001 (1) - Dodatkowe �ycie - jednorazowy<br>
	*0000 0010 (2) - Zatrzymanie ruchu przeciwnik�w na 5 sekund<br>
	*0000 0100 (4) - Odporno�� na strza�y przeciwnik�w na 30 sekund<br>
	*0000 1000 (8) - Kula przechodz�ca, przez wszystkich przeciwnik�w na swojej drodze przez 5 sekund<br>
	*0001 0000 (16)  - Podwojenie zdobywanych punkt�w<br>
	*/
	unsigned char bonuses;
	/**
	* Tabela z czasami rozpocz�cia oraz z aktualnym czasem dla ka�dego z bonus�w
	*/
	time_t czasy[4][2];
	/**
	* Bitmapa dla gracza
	*/
	ALLEGRO_BITMAP* player_bmp,/**
	* Bitmapa dla ikony �ycia
	*/*life,
	/**
	* Bitmapa dla pierwszego bonusu
	*/* bonus1,/**
	* Bitmapa dla drugiego bonusu
	*/*bonus2,
	/**
    * Bitmapa dla trzeciego bonusu
    */*bonus3,/**
	* Bitmapa dla czwartego bonusu
	*/*bonus4;
	/**
	* Stan gracza
	*/
	char state;
	/**
	* Pozycja gracza w osi X
	*/
	float pos_x, /**
	* Pozycja gracza w osi Y
	*/pos_y,/**
	* Rozmiar gracza w osi X
	*/size_x,/**
	* Rozmiar gracza w osi Y
	*/size_y,/**
	* Pr�dko�� gracza w osi X
	*/speed_x,/**
	* Pr�dko�� gracza w osi Y
	*/speed_y;
};
/**
* Funkcja inicjuj�ca gracza, �aduj�ca tekstury, zeruj�ca bonusy oraz ustawiaj�ca gracza na odpowiedniej pozycji.
* @param play Wska�nik do gracza, kt�rego parametry zmodyfikujemy
* @param w Szeroko�� okna
* @param h wysoko�� okna<br>Obie potrzebne do wyliczenia proporcji ekranu.
*/
void player_Init(struct player* play, unsigned int w, unsigned int h);
/**
* Funkcja s�u��ca do zmiany pozycji gracza - zmiana pozycji mo�liwa jest zar�wno w osi X jak i Y.
* @param play Wska�nik do gracza, kt�rego pozycj� chcemy zmieni�
* @param vector_x Przesuni�cie w poziomie -  warto�ci wi�ksze od 0 przesuwaj� w prawo a mniejsze w lewo
* @param vector_y Przesuni�cie w pionie - warto�ci wi�ksze od 0 przesuwaj� w d�, mniejsze od 0 do g�ry
*
*/
void Update_player_Pos(struct player* play, float vector_x, float vector_y);
/**
* Funkcja zwraca czy gracz �yje.
* @param play Gracz, kt�rego status chcemy sprawdzi�
*/
char is_alive(struct player play);
/**
* Funkcja odpowiedzialna za wy�wietlanie gracza
* @param play Gracz, kt�rego mamy wy�wietli�
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void draw_player(struct player play,unsigned  int w, unsigned int h);
/**
* Funkcja wy�wietlaj�ca aktualn� ilo�� punkt�w, kt�re zdoby� gracz.
* @param play Gracz, kt�rego ilo�� punkt�w chcemy wy�wietli�
* @param font Czcionka, kt�rej u�yjemy do wy�wietlenia wyniku
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void draw_score(struct player play, ALLEGRO_FONT* font, unsigned int w, unsigned int h);
/**
* Funkcja wy�wietlaj�ca aktualn� ilo�� �y�, bonusy oraz czas, kt�ry pozosta� do ich zako�czenia.
* @param font Czcionka, kt�rej u�yjemy do wy�wietlenia pozosta�ego czasu / �y�
* @param play Gracz, kt�rego ilo�� punkt�w chcemy wy�wietli�
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void show_player_state(ALLEGRO_FONT* font, struct player play, unsigned int w, unsigned int h);
#endif