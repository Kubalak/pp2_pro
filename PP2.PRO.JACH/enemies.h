#pragma once
#ifndef ENEMIES_H
/**
* Standardowa definicja dla pliku �r�d�owego zabezpieczaj�ca przed jego wielokrotnym do��czeniem do kompilacji
*/
#define ENEMIES_H
#include<allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
/**
* Struktura odpowiedzialna za przeciwnik�w.
*/
struct enemy
{
/**
* Rodzaj przeciwnika - ilo�� punkt�w przyznawanych za jego zniszczenie
*/
	char enemy_type,/**
* Wiersz, w kt�rym przeciwnik si� znajduje
*/row,/**
* Kolumna, w kt�rym przeciwnik si� znajduje
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
* Pcz�tkowa pozycja macierzy przeciwnik�w w osi X
*/start_pos,/**
* Ko�cowa pozycja macierzy przeciwnik�w w osi X
*/end_pos,/**
* Ko�cowa pozycja macierzy przeciwnik�w w osi Y
*/end_y_pos;
/**
* Bitmapa dla przeciwnika w pierwszym etapie ruchu
*/
	ALLEGRO_BITMAP* bmp;
	/**
* Bitmapa dla przeciwnika w drugim etapie ruchu
*/
	ALLEGRO_BITMAP* bmp_1;//Bitmapa przygotowana dla kolejnego ruchu przeciwnik�w
	/**
* Wska�nik na nast�pny element z listy
*/
	struct enemy* next,/**
* Wska�nik na poprzedni element z listy
*/*prev;
};
/**
* Bitmapa u�ywana do przedstawienia wybuchu
*/
ALLEGRO_BITMAP* destroy;
/**
* Funkcja tworz�ca nowego przeciwnika w li�cie.
* @param present Aktualny pocz�tek listy
*/
struct enemy* create_enemy(struct enemy* present);
/**
* Funkcja tworz�ca list� przeciwnik�w u�o�on� w macierz o rozmiarze <b>rows</b> na <b>cols</b>.
* @param front Aktualny pocz�tek listy
* @param rows Ilo�� wierszy
* @param columns Ilo�� kolumn
*/
struct enemy* create_enemy_matrix(struct enemy*front,unsigned int rows, unsigned int columns);
/**
* Funkcja pozycjonuj�ca przeciwnik�w w li�cie w macierz o rozmiarze <b>rows</b> na <b>cols</b> oraz �aduj�ca tekstury przeciwnik�w.
* @param enemies_matrix Aktualny pocz�tek listy
* @param padding_x Odst�py po bokach
* @param padding_y Odst�p g�rny
* @param w Wysoko�� okna
* @param h Szeroko�� okna
* @param rows Ilo�� wierszy
* @param columns Ilo�� kolumn
*/
void enemy_Init(struct enemy* enemies_matrix, float padding_x, float padding_y, unsigned int w, unsigned int h, unsigned int rows, unsigned int columns);
/**
* Funkcja rysuj�ca wszystkich przeciwnik�w.
* @param enemy_matrix Aktualny pocz�tek listy
* @param w Wysoko�� okna
* @param h Szeroko�� okna
*/
bool draw_enemy(struct enemy* enemy_matrix, unsigned int w, unsigned int h);
/**
* Funkcja wykonuj�ca kolejny ruch przeciwnik�w z danego wiersza.
* @param enemy_list Aktualny pocz�tek listy
* @param rows Ilo�� wierszy
* @param columns Ilo�� kolumn
*/
void move_enemy(struct enemy* enemy_list, unsigned int rows,unsigned int columns);
/**
* Funkcja usuwaj�ca <u><b>dowolny</b></u> element z listy przeciwnik�w.
* @param front Aktualny pocz�tek listy
*/
int destroy_enemy(struct enemy** front);
/**
* Funkcja usuwaj�ca ca�� list� przeciwnik�w.
* @param matrix Aktualny pocz�tek listy
*/
void free_enemy_matrix(struct enemy** matrix);
#endif