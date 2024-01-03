#pragma once
#ifndef PLAYER_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
*/
#define PLAYER_H
/**
* Definicja dla gracza
*/
#define ALIVE 1
/**
* Definicja dla gracza
*/
#define DEAD 0
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
/**
* Struktura zawieraj¹ca dane gracza  - wynik, iloœæ ¿yæ aktywne bonusy i czasy ich trwania.
*/
struct player
{
	/**
	*	Iloœæ zdobytych przez gracza punktów
	*/
	unsigned int score;
	/**
	*	Iloœc pozosta³ych ¿yæ
	*/
	char lives;
	/**
	* Poszczególne bonusy - wed³ug kolejnych bitów w zmiennej<br>
	*0000 0000 (0) - ¯aden nie jest aktywny<br>
	*0000 0001 (1) - Dodatkowe ¿ycie - jednorazowy<br>
	*0000 0010 (2) - Zatrzymanie ruchu przeciwników na 5 sekund<br>
	*0000 0100 (4) - Odpornoœæ na strza³y przeciwników na 30 sekund<br>
	*0000 1000 (8) - Kula przechodz¹ca, przez wszystkich przeciwników na swojej drodze przez 5 sekund<br>
	*0001 0000 (16)  - Podwojenie zdobywanych punktów<br>
	*/
	unsigned char bonuses;
	/**
	* Tabela z czasami rozpoczêcia oraz z aktualnym czasem dla ka¿dego z bonusów
	*/
	time_t czasy[4][2];
	/**
	* Bitmapa dla gracza
	*/
	ALLEGRO_BITMAP* player_bmp,/**
	* Bitmapa dla ikony ¿ycia
	*/*life,
	/**
	* Bitmapa dla pierwszego bonusu
	*/* bonus1,/**
	* Bitmapa dla drugiego bonusu
	*/*bonus2,
	/**
    * Bitmapa dla trzeciego bonusu
    */*bonus3,/**
	* Bitmapa dla czwartego bonusu
	*/*bonus4;
	/**
	* Stan gracza
	*/
	char state;
	/**
	* Pozycja gracza w osi X
	*/
	float pos_x, /**
	* Pozycja gracza w osi Y
	*/pos_y,/**
	* Rozmiar gracza w osi X
	*/size_x,/**
	* Rozmiar gracza w osi Y
	*/size_y,/**
	* Prêdkoœæ gracza w osi X
	*/speed_x,/**
	* Prêdkoœæ gracza w osi Y
	*/speed_y;
};
/**
* Funkcja inicjuj¹ca gracza, ³aduj¹ca tekstury, zeruj¹ca bonusy oraz ustawiaj¹ca gracza na odpowiedniej pozycji.
* @param play WskaŸnik do gracza, którego parametry zmodyfikujemy
* @param w Szerokoœæ okna
* @param h wysokoœæ okna<br>Obie potrzebne do wyliczenia proporcji ekranu.
*/
void player_Init(struct player* play, unsigned int w, unsigned int h);
/**
* Funkcja s³u¿¹ca do zmiany pozycji gracza - zmiana pozycji mo¿liwa jest zarówno w osi X jak i Y.
* @param play WskaŸnik do gracza, którego pozycjê chcemy zmieniæ
* @param vector_x Przesuniêcie w poziomie -  wartoœci wiêksze od 0 przesuwaj¹ w prawo a mniejsze w lewo
* @param vector_y Przesuniêcie w pionie - wartoœci wiêksze od 0 przesuwaj¹ w dó³, mniejsze od 0 do góry
*
*/
void Update_player_Pos(struct player* play, float vector_x, float vector_y);
/**
* Funkcja zwraca czy gracz ¿yje.
* @param play Gracz, którego status chcemy sprawdziæ
*/
char is_alive(struct player play);
/**
* Funkcja odpowiedzialna za wyœwietlanie gracza
* @param play Gracz, którego mamy wyœwietliæ
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void draw_player(struct player play,unsigned  int w, unsigned int h);
/**
* Funkcja wyœwietlaj¹ca aktualn¹ iloœæ punktów, które zdoby³ gracz.
* @param play Gracz, którego iloœæ punktów chcemy wyœwietliæ
* @param font Czcionka, której u¿yjemy do wyœwietlenia wyniku
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void draw_score(struct player play, ALLEGRO_FONT* font, unsigned int w, unsigned int h);
/**
* Funkcja wyœwietlaj¹ca aktualn¹ iloœæ ¿yæ, bonusy oraz czas, który pozosta³ do ich zakoñczenia.
* @param font Czcionka, której u¿yjemy do wyœwietlenia pozosta³ego czasu / ¿yæ
* @param play Gracz, którego iloœæ punktów chcemy wyœwietliæ
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void show_player_state(ALLEGRO_FONT* font, struct player play, unsigned int w, unsigned int h);
#endif