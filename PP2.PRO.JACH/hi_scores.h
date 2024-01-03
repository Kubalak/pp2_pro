#pragma once
#ifndef HI_SCORES_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
*/
#define HI_SCORES_H
#include <allegro5/allegro_font.h>
/**
* Struktura odpowiedzialna za przechowywanie najlepszych wyników wraz z dat¹, a tak¿e nazwami graczy.
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
* Funkcja tworz¹ca nowy wpis w liœcie z wynikami.
* @param node Aktualny pocz¹tek listy
* @param data Data uzyskania wyniku
* @param score Liczba zdobytych przez gracza punktów
*/
void new_score(struct hi_score** node,char data[],int score);
/**
* Funkcja odpowiadaj¹ca za za³adowanie listy wyników dla danego poziomu trudnoœci.
* @param node Aktualny pocz¹tek listy
* @param difficulty Poziom trudnoœci, dla którego nale¿y za³adowaæ listê wyników
*/
void load_data(struct hi_score** node,int difficulty);
/**
* Funkcja odpowiadaj¹ca za zapisanie listy wyników dla danego poziomu trudnoœci do pliku *.dat.
* @param node Aktualny pocz¹tek listy
* @param difficulty Poziom trudnoœci, dla którego nale¿y zapisaæ listê wyników - ka¿dy poziom trudnoœci ma oddzielny plik z danymi
*/
void save_data(struct hi_score* node,int difficulty);
/**
* Funkcja wyœwietlaj¹ca 10 najlepszych wyników dla danego poziomu trudnoœci.
* @param font Czcionka, któr¹ bêd¹ wyœwietlane wpisy 
* @param background T³o, na którym wyœiwetlane bêd¹ wyniki
* @param node Pocz¹tek listy wyników
* @param new_node Nowo dodany do listy wpis - ten uzyskany przez gracza w bie¿¹cej sesji
* @param screen_w Szerokoœæ okna
* @param screen_h Wysokoœc okna
*/
void print_hi_score(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background,struct hi_score* node, struct hi_score* new_node,  unsigned int screen_w, unsigned int screen_h);
/**
* Funkcja sortuj¹ca listê wyników od najwiêkszego do najmniejszego.
* @param node Aktualny pocz¹tek listy
*/
void sort(struct hi_score** node);
/**
* Funkcja usuwaj¹ca ca³¹ listê wyników.
* @param start Aktualny pocz¹tek listy
*/
void delete_all(struct hi_score** start);
/**
* Funkcja s³u¿¹ca nadawaniu nazwy graczowi po zakoñczonej grze.
* @param font Czcionka, któr¹ bêdzie wyœwietlana nazwa gracza oraz inne elementy interfejsu
* @param background T³o, na którym wyœwietlane bêd¹ pozosta³e elementy okna
* @param node Aktualny pocz¹tek listy
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void set_name(ALLEGRO_FONT* font, ALLEGRO_BITMAP* background, struct hi_score* node, unsigned int w, unsigned int h);
#endif