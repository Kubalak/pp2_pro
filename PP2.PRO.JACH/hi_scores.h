#pragma once
#ifndef HI_SCORES_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
*/
#define HI_SCORES_H
#include <allegro5/allegro_font.h>
/**
* Struktura odpowiedzialna za przechowywanie najlepszych wynik�w wraz z dat�, a tak�e nazwami graczy.
*
*/
struct hi_score
{
	/**
	* Nazwa gracza
	*/
	char player_name[6];
	/**
	* Data uzyskania wyniku
	*/
	char data[16];
	/**
	* Wynik
	*/
	int score;
	/**
	* Kolejny element z listy
	*/

	struct hi_score* next,	
	/**
	* Poprzedni element z listy
	*/*prev;
};

/**
* Funkcja tworz�ca nowy wpis w li�cie z wynikami.
* @param node Aktualny pocz�tek listy
* @param data Data uzyskania wyniku
* @param score Liczba zdobytych przez gracza punkt�w
*/
void new_score(struct hi_score** node,char data[],int score);
/**
* Funkcja odpowiadaj�ca za za�adowanie listy wynik�w dla danego poziomu trudno�ci.
* @param node Aktualny pocz�tek listy
* @param difficulty Poziom trudno�ci, dla kt�rego nale�y za�adowa� list� wynik�w
*/
void load_data(struct hi_score** node,int difficulty);
/**
* Funkcja odpowiadaj�ca za zapisanie listy wynik�w dla danego poziomu trudno�ci do pliku *.dat.
* @param node Aktualny pocz�tek listy
* @param difficulty Poziom trudno�ci, dla kt�rego nale�y zapisa� list� wynik�w - ka�dy poziom trudno�ci ma oddzielny plik z danymi
*/
void save_data(struct hi_score* node,int difficulty);
/**
* Funkcja wy�wietlaj�ca 10 najlepszych wynik�w dla danego poziomu trudno�ci.
* @param font Czcionka, kt�r� b�d� wy�wietlane wpisy 
* @param background T�o, na kt�rym wy�iwetlane b�d� wyniki
* @param node Pocz�tek listy wynik�w
* @param new_node Nowo dodany do listy wpis - ten uzyskany przez gracza w bie��cej sesji
* @param screen_w Szeroko�� okna
* @param screen_h Wysoko�c okna
*/
void print_hi_score(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background,struct hi_score* node, struct hi_score* new_node,  unsigned int screen_w, unsigned int screen_h);
/**
* Funkcja sortuj�ca list� wynik�w od najwi�kszego do najmniejszego.
* @param node Aktualny pocz�tek listy
*/
void sort(struct hi_score** node);
/**
* Funkcja usuwaj�ca ca�� list� wynik�w.
* @param start Aktualny pocz�tek listy
*/
void delete_all(struct hi_score** start);
/**
* Funkcja s�u��ca nadawaniu nazwy graczowi po zako�czonej grze.
* @param font Czcionka, kt�r� b�dzie wy�wietlana nazwa gracza oraz inne elementy interfejsu
* @param background T�o, na kt�rym wy�wietlane b�d� pozosta�e elementy okna
* @param node Aktualny pocz�tek listy
* @param w Szeroko�� okna
* @param h Wysoko�� okna
*/
void set_name(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background, struct hi_score* node, unsigned int w, unsigned int h);
#endif