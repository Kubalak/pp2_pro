#pragma once
#ifndef BONUSES_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
*/
#define BONUSES_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
/**
* Struktura odpowiedzialna za system bonus�w, wywodzi si� ze struktury zawieraj�cej pociski.
*/
struct bonus
{/**
* Pozycja w osi X
*/
	float pos_x, /**
* Pozycja w osi Y
*/pos_y,/**
* Pr�dko��
*/speed;
/**
* Tesktura bonusu
*/
	ALLEGRO_BITMAP* bmp;
	/**
* Rodzaj bonusu
*/
	unsigned char bonus_type;
	/**
* Wska�nik na nast�pny bonus
*/
	struct bonus* next;
};
/**
* Funkcja tworz�ca nowy bonus w danym miejscu i o zadanej szybko�ci .
* @param bonus_list Pocz�tek listy z bonusami 
* @param x Pozycja bonusu w osi X
* @param y Pozycja bonusu w osi Y
* @param speed Pr�dko�� bonusu (w osi Y)
*/
struct bonus* new_bonus(struct bonus* bonus_list, float x, float y, float speed);
/**
* Funkcja rysuj�ca wszystkie bonusy na ekranie.
* @param bonus_list Pocz�tek listy z bonusami
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void draw_bonuses(struct bonus* bonus_list, unsigned int w, unsigned int h);
/**
* Funkcja usuwaj�ca <b><u>dowolny</u></b> element z listy o pocz�tku podanymprzez parametr begin.
* @param begin Pocz�tek listy z bonusami
* @param node Usuwany element z listy
*/
void destroy_bonus(struct bonus** begin, struct bonus** node);
/**
* Funkcja aktualizuj�ca pozycj� bonus�w oraz przyznaj�ca je graczowi w razie ich zdobycia.
* @param bonus_list Pocz�tek listy z bonusami
* @param play Gracz, kt�remu przyznane zostan� bonusy
*/
void update_bonuses(struct bonus** bonus_list, struct player* play);
/**
* Funkcja losuj�ca typ bonusu dla danego elementu.
* @param bonus_list Wybrany element z listy bonus�w
*/
void rand_bonus(struct bonus* bonus_list);

#endif