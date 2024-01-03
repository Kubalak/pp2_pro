#pragma once
#ifndef BULLETS_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
*/
#define BULLETS_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include "enemies.h"
#include "bonuses.h"
/**
* Struktura odpowiedzialna za system pocisków.
*/
struct bullet
{/**
* Pozycja w osi X
*/
	float pos_x, /**
* Pozycja w osi Y
*/pos_y,/**
* Prêdkoœæ (w osi Y)
*/speed;
/**
* Pochodzenie pocisku - gracz / przeciwnik 
*/
	bool origin;
/**
* WskaŸnik na nastêpny element z listy pocisków
*/
	struct bullet* next;
};
/**
* Funkcja tworz¹ca nowy pocisk w danym miejscu i o zadanej szybkoœci.
* @param bullet_list Pocz¹tek listy pocisków, wzglêdem którego dok³adamy nowy element
* @param x Pozycja pocisku w osi X
* @param y Pozycja pocisku w osi Y
* @param speed Prêdkoœæ pocisku (w osi Y)
*/
struct bullet* new_bullet(struct bullet* bullet_list, float x, float y, float speed);
/**
* Funkcja rysuj¹ca wszystkie pociski z listy na ekranie
* @param bullet_list Pocz¹tek listy pocisków, któr¹ bêdziemy wyœwietlaæ
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void draw_bullets(struct bullet* bullet_list, unsigned int w, unsigned int h);
/**
* Funkcja usuwaj¹ca <u><b>dowolny</b></u> pocisk z listy pocisków.
* @param begin Pocz¹tek listy pocisków
* @param node Element, który chcemy usun¹c z listy pocisków
*/
void destroy_bullet(struct bullet** begin, struct bullet** node);
/**
* Funkcja tworz¹ca nowy pocisk w miejscu, gdzie stoi gracz.
* @param bullet_list Pocz¹tek listy pocisków, wzglêdem którego dok³adamy nowy element
* @param play Gracz, od którego wyjdzie nowy pocisk
*/
void shoot(struct bullet** bullet_list, struct player play);
/**
* Funkcja aktualizuj¹ca wszystkie pociski na planszy.
* @param boom Pocz¹tek DŸwiêk niszczenia przeciwnika
* @param bullet_list Lista pocisków gracza
* @param enemy_bullet_list Lista pocisków przeciwników
* @param bonus_list Lista z bonusami 
* @param play Gracz, którego punktacja oraz iloœc ¿yæ bêd¹ modyfikowane w funkcji
* @param enemy_matrix Lista przeciwników
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
int update_bullets(ALLEGRO_SAMPLE_INSTANCE *boom,struct bullet** bullet_list, struct bullet** enemy_bullet_list,struct bonus** bonus_list, struct player* play, struct enemy** enemy_matrix, unsigned int w, unsigned int h);
/**
* Funkcja wybieraj¹ca losowego przeciwnika do strza³u.
* @param enemy_bul ista pocisków przeciwników
* @param enem Lista przeciwników - potrzebna do utworzenia nowego pocisku w odpowiednim miejscu
*/
void rand_enemy_shoot(struct bullet** enemy_bul, struct enemy* enem);
#endif