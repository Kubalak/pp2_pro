#pragma once
#ifndef ENEMIES_H
/**
* Standardowa definicja dla pliku Ÿród³owego zabezpieczaj¹ca przed jego wielokrotnym do³¹czeniem do kompilacji
*/
#define ENEMIES_H
#include<allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
/**
* Struktura odpowiedzialna za przeciwników.
*/
struct enemy
{
/**
* Rodzaj przeciwnika - iloœæ punktów przyznawanych za jego zniszczenie
*/
	char enemy_type,/**
* Wiersz, w którym przeciwnik siê znajduje
*/row,/**
* Kolumna, w którym przeciwnik siê znajduje
*/col, /**
* Etap ruchu wykonywany przez przeciwnika
*/mov;
	/**
* Pozycja w osi X
*/
	float pos_x, /**
* Pozycja w osi Y
*/pos_y,/**
* Rozmiar w osi X
*/size_x,/**
* Rozmiar w osi Y
*/size_y,/**
* Pcz¹tkowa pozycja macierzy przeciwników w osi X
*/start_pos,/**
* Koñcowa pozycja macierzy przeciwników w osi X
*/end_pos,/**
* Koñcowa pozycja macierzy przeciwników w osi Y
*/end_y_pos;
/**
* Bitmapa dla przeciwnika w pierwszym etapie ruchu
*/
	ALLEGRO_BITMAP* bmp;
	/**
* Bitmapa dla przeciwnika w drugim etapie ruchu
*/
	ALLEGRO_BITMAP* bmp_1;//Bitmapa przygotowana dla kolejnego ruchu przeciwników
	/**
* WskaŸnik na nastêpny element z listy
*/
	struct enemy* next,/**
* WskaŸnik na poprzedni element z listy
*/*prev;
};
/**
* Bitmapa u¿ywana do przedstawienia wybuchu
*/
ALLEGRO_BITMAP* destroy;
/**
* Funkcja tworz¹ca nowego przeciwnika w liœcie.
* @param present Aktualny pocz¹tek listy
*/
struct enemy* create_enemy(struct enemy* present);
/**
* Funkcja tworz¹ca listê przeciwników u³o¿on¹ w macierz o rozmiarze <b>rows</b> na <b>cols</b>.
* @param front Aktualny pocz¹tek listy
* @param rows Iloœæ wierszy
* @param columns Iloœæ kolumn
*/
struct enemy* create_enemy_matrix(struct enemy*front,unsigned int rows, unsigned int columns);
/**
* Funkcja pozycjonuj¹ca przeciwników w liœcie w macierz o rozmiarze <b>rows</b> na <b>cols</b> oraz ³aduj¹ca tekstury przeciwników.
* @param enemies_matrix Aktualny pocz¹tek listy
* @param padding_x Odstêpy po bokach
* @param padding_y Odstêp górny
* @param w Wysokoœæ okna
* @param h Szerokoœæ okna
* @param rows Iloœæ wierszy
* @param columns Iloœæ kolumn
*/
void enemy_Init(struct enemy* enemies_matrix, float padding_x, float padding_y, unsigned int w, unsigned int h, unsigned int rows, unsigned int columns);
/**
* Funkcja rysuj¹ca wszystkich przeciwników.
* @param enemy_matrix Aktualny pocz¹tek listy
* @param w Wysokoœæ okna
* @param h Szerokoœæ okna
*/
bool draw_enemy(struct enemy* enemy_matrix, unsigned int w, unsigned int h);
/**
* Funkcja wykonuj¹ca kolejny ruch przeciwników z danego wiersza.
* @param enemy_list Aktualny pocz¹tek listy
* @param rows Iloœæ wierszy
* @param columns Iloœæ kolumn
*/
void move_enemy(struct enemy* enemy_list, unsigned int rows,unsigned int columns);
/**
* Funkcja usuwaj¹ca <u><b>dowolny</b></u> element z listy przeciwników.
* @param front Aktualny pocz¹tek listy
*/
int destroy_enemy(struct enemy** front);
/**
* Funkcja usuwaj¹ca ca³¹ listê przeciwników.
* @param matrix Aktualny pocz¹tek listy
*/
void free_enemy_matrix(struct enemy** matrix);
#endif