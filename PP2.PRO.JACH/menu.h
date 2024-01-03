#pragma once
#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include "hi_scores.h"
/**
* Struktura odpowiedzialna za przechowywanie r�nych rozdzielczo�ci ekranu.
*/
struct resolution
{
	/**
	* Szeroko�� ekranu
	*/
	int x;
	/**
	* Wysokos� ekranu
	*/
	int y;
};
/**
* Funkcja odpowiadaj�ca za zmian� ustawie� gry.
* Modyfikuje ona zawarto�� ALLEGRO_CONFIG spod wska�nika <b>cfg</b>.
* @param font Czcionka, kt�ra jest potrzebna do wy�wietlania napis�w, zostanie ona prze�adowana przy zmianie wymiar�w okna
* @param state Wska�nik na struktur�, w kt�rej przechowywany jest stan klawiatury - wci�ni�tych klawiszy
* @param cfg Wska�nik do konfiguracji gry, za jej pomoc� zapisywane i odczytywane s� ustawienia gry przy uruchamianiu
* @param display Wska�nik na okno (wy�wietlacz), kt�rego wymiary oraz flagi zostan� zmienione
* @param background Wska�nik na bitmap�, kt�ra jest t�em dla ekranu.
* @param screen_w Wska�nik na szeroko�� ekranu - przy zmianie wymiar�w ekranu oryginalne warto�ci tak�e zostan� zmienione
* @param screen_h Wska�nik na wysoko�� ekranu - przy zmianie wymiar�w ekranu oryginalne warto�ci tak�e zostan� zmienione
*/
void change_set(ALLEGRO_FONT** font, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h);
/**
* Funkcja odpowiadaj�ca za g��wne menu gry.
* @param cfg Wska�nik na konfiguracj�, kt�ry zostanie przekazany dalej do funkcji <b>change_set()</b> je�li zostanie ona wywo�ana
* @param display Wska�nik na okno (wy�wietlacz), kt�rego wymiary oraz flagi zostan� zmienione
* @param state Wska�nik na struktur�, w kt�rej przechowywany jest stan klawiatury - wci�ni�tych klawiszy
* @param font Czcionka, kt�ra jest potrzebna do wy�wietlania napis�w, zostanie ona prze�adowana przy zmianie wymiar�w okna
* @param font_sm Ma�a czcionka, potrzebna do wy�wietlenia mniejszych element�w w funkcji <b>print_hi_score()</b>
* @param background Wska�nik na bitmap�, kt�ra jest t�em dla ekranu.
* @param screen_w Wska�nik na szeroko�� ekranu - przy zmianie wymiar�w ekranu oryginalne warto�ci tak�e zostan� zmienione.
* @param screen_h Wska�nik na wysoko�� ekranu - przy zmianie wymiar�w ekranu oryginalne warto�ci tak�e zostan� zmienione.
*/
int menu(ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_FONT** font, ALLEGRO_FONT** font_sm, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h);
#endif