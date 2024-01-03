#pragma once
#ifndef BOSS_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
*/
#define BOSS_H
#include <allegro5/allegro.h>
#include "player.h"
#include "bullets.h"
#include "bonuses.h"
/**
* Struktura odpowiedzialna za bossa.
*/
struct boss
{	/**
	* Tekstura bossa w pierwszym etapie ruchu
	*/
	ALLEGRO_BITMAP* texture,/**
	* Tekstura bossa w drugim etapie ruchu
	*/*texture_1;
	/**
	* Rozmiar w osi X
	*/
	float size_x, /**
	* Rozmiar w osi Y
	*/size_y, /**
	* Pozycja w osi X
	*/pos_x,/**
	* Pozycja w osi Y
	*/ pos_y;
	/**
	* Obecne �ycie
	*/
	int HP,/**
	* Pierwotna ilo�� �ycia
	*/MAXHP;
	/**
	* Etap ruchu
	*/
	char stage,/**
	* Kierunek ruchu
	*/direction;
};
/**
* Funkcja odpowiadaj�ca za walk� z bossem.
* Po zako�czeniu 3. fali sterowanie graczem jest przekazywane do niej
* @param background T�o, na kt�rym b�d� wy�wietlane wszystkie elementy pola gry
* @param font Czcionka, kt�r� b�d� wy�wietlane elementy interfejsu
* @param font_sm Czcionka, kt�r� b�d� wy�wietlane elementy interfejsu
* @param instance D�wi�k odtwarzany po strzale
* @param music Muzyka
* @param queue Kolejka zdarze�
* @param event Zdarzenie, potrzebne wraz z queue do obs�ugi wydarze� zwi�zanych z klawiatur� oraz ekranem
* @param play Gracz
* @param difficulty Poziom trudno�ci, im wy�szy tym wi�cej zdrowia posiada boss.
* @param w Wysoko�� okna
* @param h Szeroko�� okna
*/
void bossfight(ALLEGRO_BITMAP* background, ALLEGRO_FONT* font, ALLEGRO_FONT* font_sm, ALLEGRO_SAMPLE_INSTANCE* instance, ALLEGRO_SAMPLE_INSTANCE* music, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* event, struct player* play, unsigned int difficulty, unsigned int w, unsigned int h);
#endif