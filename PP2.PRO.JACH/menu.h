#pragma once
#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include "hi_scores.h"
/**
* Struktura odpowiedzialna za przechowywanie ró¿nych rozdzielczoœci ekranu.
*/
struct resolution
{
	/**
	* Szerokoœæ ekranu
	*/
	int x;
	/**
	* Wysokosæ ekranu
	*/
	int y;
};
/**
* Funkcja odpowiadaj¹ca za zmianê ustawieñ gry.
* Modyfikuje ona zawartoœæ ALLEGRO_CONFIG spod wskaŸnika <b>cfg</b>.
* @param font Czcionka, która jest potrzebna do wyœwietlania napisów, zostanie ona prze³adowana przy zmianie wymiarów okna
* @param state WskaŸnik na strukturê, w której przechowywany jest stan klawiatury - wciœniêtych klawiszy
* @param cfg WskaŸnik do konfiguracji gry, za jej pomoc¹ zapisywane i odczytywane s¹ ustawienia gry przy uruchamianiu
* @param display WskaŸnik na okno (wyœwietlacz), którego wymiary oraz flagi zostan¹ zmienione
* @param background WskaŸnik na bitmapê, która jest t³em dla ekranu.
* @param screen_w WskaŸnik na szerokoœæ ekranu - przy zmianie wymiarów ekranu oryginalne wartoœci tak¿e zostan¹ zmienione
* @param screen_h WskaŸnik na wysokoœæ ekranu - przy zmianie wymiarów ekranu oryginalne wartoœci tak¿e zostan¹ zmienione
*/
void change_set(ALLEGRO_FONT** font, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h);
/**
* Funkcja odpowiadaj¹ca za g³ówne menu gry.
* @param cfg WskaŸnik na konfiguracjê, który zostanie przekazany dalej do funkcji <b>change_set()</b> jeœli zostanie ona wywo³ana
* @param display WskaŸnik na okno (wyœwietlacz), którego wymiary oraz flagi zostan¹ zmienione
* @param state WskaŸnik na strukturê, w której przechowywany jest stan klawiatury - wciœniêtych klawiszy
* @param font Czcionka, która jest potrzebna do wyœwietlania napisów, zostanie ona prze³adowana przy zmianie wymiarów okna
* @param font_sm Ma³a czcionka, potrzebna do wyœwietlenia mniejszych elementów w funkcji <b>print_hi_score()</b>
* @param background WskaŸnik na bitmapê, która jest t³em dla ekranu.
* @param screen_w WskaŸnik na szerokoœæ ekranu - przy zmianie wymiarów ekranu oryginalne wartoœci tak¿e zostan¹ zmienione.
* @param screen_h WskaŸnik na wysokoœæ ekranu - przy zmianie wymiarów ekranu oryginalne wartoœci tak¿e zostan¹ zmienione.
*/
int menu(ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_FONT** font, ALLEGRO_FONT** font_sm, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h);
#endif