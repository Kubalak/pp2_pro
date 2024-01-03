#pragma once
#ifndef BOSS_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
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
	* Obecne ¿ycie
	*/
	int HP,/**
	* Pierwotna iloœæ ¿ycia
	*/MAXHP;
	/**
	* Etap ruchu
	*/
	char stage,/**
	* Kierunek ruchu
	*/direction;
};
/**
* Funkcja odpowiadaj¹ca za walkê z bossem.
* Po zakoñczeniu 3. fali sterowanie graczem jest przekazywane do niej
* @param background T³o, na którym bêd¹ wyœwietlane wszystkie elementy pola gry
* @param font Czcionka, któr¹ bêd¹ wyœwietlane elementy interfejsu
* @param font_sm Czcionka, któr¹ bêd¹ wyœwietlane elementy interfejsu
* @param instance DŸwiêk odtwarzany po strzale
* @param music Muzyka
* @param queue Kolejka zdarzeñ
* @param event Zdarzenie, potrzebne wraz z queue do obs³ugi wydarzeñ zwi¹zanych z klawiatur¹ oraz ekranem
* @param play Gracz
* @param difficulty Poziom trudnoœci, im wy¿szy tym wiêcej zdrowia posiada boss.
* @param w Wysokoœæ okna
* @param h Szerokoœæ okna
*/
void bossfight(ALLEGRO_BITMAP* background, ALLEGRO_FONT* font, ALLEGRO_FONT* font_sm, ALLEGRO_SAMPLE_INSTANCE* instance, ALLEGRO_SAMPLE_INSTANCE* music, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* event, struct player* play, unsigned int difficulty, unsigned int w, unsigned int h);
#endif