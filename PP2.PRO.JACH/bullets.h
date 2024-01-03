#pragma once
#ifndef BULLETS_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
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
* Struktura odpowiedzialna za system pocisk�w.
*/
struct bullet
{/**
* Pozycja w osi X
*/
	float pos_x, /**
* Pozycja w osi Y
*/pos_y,/**
* Pr�dko�� (w osi Y)
*/speed;
/**
* Pochodzenie pocisku - gracz / przeciwnik 
*/
	bool origin;
/**
* Wska�nik na nast�pny element z listy pocisk�w
*/
	struct bullet* next;
};
/**
* Funkcja tworz�ca nowy pocisk w danym miejscu i o zadanej szybko�ci.
* @param bullet_list Pocz�tek listy pocisk�w, wzgl�dem kt�rego dok�adamy nowy element
* @param x Pozycja pocisku w osi X
* @param y Pozycja pocisku w osi Y
* @param speed Pr�dko�� pocisku (w osi Y)
*/
struct bullet* new_bullet(struct bullet* bullet_list, float x, float y, float speed);
/**
* Funkcja rysuj�ca wszystkie pociski z listy na ekranie
* @param bullet_list Pocz�tek listy pocisk�w, kt�r� b�dziemy wy�wietla�
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void draw_bullets(struct bullet* bullet_list, unsigned int w, unsigned int h);
/**
* Funkcja usuwaj�ca <u><b>dowolny</b></u> pocisk z listy pocisk�w.
* @param begin Pocz�tek listy pocisk�w
* @param node Element, kt�ry chcemy usun�c z listy pocisk�w
*/
void destroy_bullet(struct bullet** begin, struct bullet** node);
/**
* Funkcja tworz�ca nowy pocisk w miejscu, gdzie stoi gracz.
* @param bullet_list Pocz�tek listy pocisk�w, wzgl�dem kt�rego dok�adamy nowy element
* @param play Gracz, od kt�rego wyjdzie nowy pocisk
*/
void shoot(struct bullet** bullet_list, struct player play);
/**
* Funkcja aktualizuj�ca wszystkie pociski na planszy.
* @param boom Pocz�tek D�wi�k niszczenia przeciwnika
* @param bullet_list Lista pocisk�w gracza
* @param enemy_bullet_list Lista pocisk�w przeciwnik�w
* @param bonus_list Lista z bonusami 
* @param play Gracz, kt�rego punktacja oraz ilo�c �y� b�d� modyfikowane w funkcji
* @param enemy_matrix Lista przeciwnik�w
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
int update_bullets(ALLEGRO_SAMPLE_INSTANCE *boom,struct bullet** bullet_list, struct bullet** enemy_bullet_list,struct bonus** bonus_list, struct player* play, struct enemy** enemy_matrix, unsigned int w, unsigned int h);
/**
* Funkcja wybieraj�ca losowego przeciwnika do strza�u.
* @param enemy_bul ista pocisk�w przeciwnik�w
* @param enem Lista przeciwnik�w - potrzebna do utworzenia nowego pocisku w odpowiednim miejscu
*/
void rand_enemy_shoot(struct bullet** enemy_bul, struct enemy* enem);
#endif