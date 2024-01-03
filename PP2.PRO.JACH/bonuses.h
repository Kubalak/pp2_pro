#pragma once
#ifndef BONUSES_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
*/
#define BONUSES_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
/**
* Struktura odpowiedzialna za system bonusów, wywodzi siê ze struktury zawieraj¹cej pociski.
*/
struct bonus
{/**
* Pozycja w osi X
*/
	float pos_x, /**
* Pozycja w osi Y
*/pos_y,/**
* Prêdkoœæ
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
* WskaŸnik na nastêpny bonus
*/
	struct bonus* next;
};
/**
* Funkcja tworz¹ca nowy bonus w danym miejscu i o zadanej szybkoœci .
* @param bonus_list Pocz¹tek listy z bonusami 
* @param x Pozycja bonusu w osi X
* @param y Pozycja bonusu w osi Y
* @param speed Prêdkoœæ bonusu (w osi Y)
*/
struct bonus* new_bonus(struct bonus* bonus_list, float x, float y, float speed);
/**
* Funkcja rysuj¹ca wszystkie bonusy na ekranie.
* @param bonus_list Pocz¹tek listy z bonusami
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void draw_bonuses(struct bonus* bonus_list, unsigned int w, unsigned int h);
/**
* Funkcja usuwaj¹ca <b><u>dowolny</u></b> element z listy o pocz¹tku podanymprzez parametr begin.
* @param begin Pocz¹tek listy z bonusami
* @param node Usuwany element z listy
*/
void destroy_bonus(struct bonus** begin, struct bonus** node);
/**
* Funkcja aktualizuj¹ca pozycjê bonusów oraz przyznaj¹ca je graczowi w razie ich zdobycia.
* @param bonus_list Pocz¹tek listy z bonusami
* @param play Gracz, któremu przyznane zostan¹ bonusy
*/
void update_bonuses(struct bonus** bonus_list, struct player* play);
/**
* Funkcja losuj¹ca typ bonusu dla danego elementu.
* @param bonus_list Wybrany element z listy bonusów
*/
void rand_bonus(struct bonus* bonus_list);

#endif