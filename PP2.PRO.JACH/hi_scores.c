/**
* Wy³¹czenie b³êdów dla funkcji strcpy
*/
#define _CRT_SECURE_NO_WARNINGS
#include "hi_scores.h"
#include <allegro5/allegro.h>
#include <stdio.h>
#include "menu.h"
/**
* Funkcja dodaj¹ca nowy element do listy wyników.
* @param node Pocz¹tek listy, wzglêdem którego dodamy nowy element
*/
struct hi_score* add(struct hi_score* node)
{
	struct hi_score* new_node = (struct hi_score*)malloc(sizeof(struct hi_score));
	if (new_node)
	{
		new_node->data[0] = '\0';
		new_node->score = 0;
		new_node->player_name[5] = '\0';
		if(node)node->prev = new_node;
		new_node->next = node;
		new_node->prev = NULL;
		return new_node;
	}
	return NULL;
}
void set_name(ALLEGRO_FONT* font,ALLEGRO_BITMAP* background, struct hi_score* node,unsigned int w, unsigned int h)
{
	char alfabet[] = "*ABCDEFGHIJKLMNOPRSTUWVXYZ0123456789";
	int indexes[] = { 0,0,0,0,0 };
	int edited = 0;
	bool enter = true,left = false,right = false,up = false,down = false;
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);
	if (node) 
	{
		while (true)
		{
			al_get_keyboard_state(&state);
			if (al_key_down(&state, ALLEGRO_KEY_LEFT))
			{
				if (!left)
				{
					if (edited > 0)edited--;
					else edited = 4;
					left = true;
				}
			}
			else left = false;
			if (al_key_down(&state, ALLEGRO_KEY_RIGHT))
			{
				if (!right)
				{
					if (edited < 4)edited++;
					else edited = 0;
					right = true;
				}
			}
			else right = false;
			if (al_key_down(&state, ALLEGRO_KEY_UP))
			{
				if (!up)
				{
					if (indexes[edited] > 0)indexes[edited]--;
					else indexes[edited] = 35;
					up = true;
				}
			}
			else up = false;
			if (al_key_down(&state, ALLEGRO_KEY_DOWN))
			{
				if (!down)
				{
					if (indexes[edited] < 35)indexes[edited]++;
					else indexes[edited] = 0;
					down = true;
				}
			}
			else down = false;
			if (al_key_down(&state, ALLEGRO_KEY_ENTER))
			{
				if (!enter)break;
			}
			else enter = false;
			for (int i = 0; i < 5; i++)
			{
				if (alfabet[indexes[i]] != '*')node->player_name[i] = alfabet[indexes[i]];
				else node->player_name[i] = ' ';
			}
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, w, h, 0);
			al_draw_textf(font, al_map_rgb(39, 255, 0), (w - al_get_text_width(font, "YOUR SCORE: <0000>")) / 2, 0.25 * h, 0, "YOUR SCORE: <%d>", node->score);
			al_draw_text(font, al_map_rgb(39, 255, 0), w / 2, 0.4 * h, ALLEGRO_ALIGN_CENTRE, "USE ARROW KEYS TO ENTER YOUR NAME");
			for (int i = 0; i < 5; i++)
			{
				al_draw_textf(font, (edited==i)? al_map_rgb(255,0,0) : al_map_rgb(39, 255, 0), (w - al_get_text_width(font, "B B B B B")) / 2 + i*al_get_text_width(font," B"), 0.5 * h, 0,"%c" , alfabet[indexes[i]]);
			}
			al_flip_display();
		}
	}
}


void load_data(struct hi_score** node,int difficulty)
{
	FILE* input;
	if (difficulty == 0)input = fopen("data/hi_scores_easy.dat", "r");
	else if (difficulty == 1)input = fopen("data/hi_scores_normal.dat", "r");
	else input = fopen("data/hi_scores_hard.dat", "r");
	struct hi_score* tmp;
	if (input && !feof(input))
	{
		while (!feof(input))
		{
			tmp = add(*node);
			fread(tmp, sizeof(struct hi_score), 1, input);
			tmp->next = *node;
			tmp->prev = NULL;
			*node = tmp;			
		} 
		fclose(input);
		if (*node)
		{
			tmp = (*node)->next;
			free(*node);
			tmp->prev = NULL;
			*node = tmp;
		}
	}
}
void save_data(struct hi_score* node,int difficulty) 
{
	FILE* output;
	if (difficulty == 0)output = fopen("data/hi_scores_easy.dat", "w");
	else if (difficulty == 1)output = fopen("data/hi_scores_normal.dat", "w");
	else output = fopen("data/hi_scores_hard.dat", "w");
	int i = 0;
	if (output)
	{
		while (node&&i < 10)
		{
			fwrite(node, sizeof(struct hi_score),1,output);
			node = node->next;
			i++;
		}
		fclose(output);
	}
}
void print_hi_score(ALLEGRO_FONT *font, ALLEGRO_BITMAP* background,struct hi_score* node, struct hi_score* new_node , unsigned int screen_w,unsigned int screen_h) 
{
	unsigned int padding = 0.085 * screen_h;
	unsigned int pos_y = padding;
	ALLEGRO_KEYBOARD_STATE state;
	struct hi_score* tmp = node;
	time_t czas;
	bool enter = true;
	time(&czas);
	do 
	{
		pos_y = padding;
		tmp = node;
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
		al_draw_text(font, al_map_rgb(39, 255, 0), (screen_w - al_get_text_width(font, "Hi-scores")) / 2, 0.02 * screen_h, 0, "Hi-scores");
		for (int i = 0; i < 10; i++)
		{
			if (!tmp)break;
			if(tmp==new_node && (czas & 1)) al_draw_textf(font, al_map_rgb(255, 0, 0), screen_w / 2, pos_y,ALLEGRO_ALIGN_CENTER, "%s  %s SCORE: <%d>", tmp->player_name, tmp->data, tmp->score);
			else al_draw_textf(font, al_map_rgb(39, 255, 0), screen_w / 2, pos_y, ALLEGRO_ALIGN_CENTER, "%s  %s SCORE: <%d>",tmp->player_name,tmp->data,tmp->score);
			pos_y += padding;
			tmp = tmp->next;
		}
		time(&czas);
		al_get_keyboard_state(&state);
		al_flip_display();
		if (al_key_down(&state, ALLEGRO_KEY_ENTER)|| al_key_down(&state,ALLEGRO_KEY_ESCAPE))
		{
			if (!enter)break;
		}
		else enter = false;
	} while (true);
}
void new_score(struct hi_score** node, char data[], int score)
{
	struct hi_score* tmp = NULL;
	struct hi_score* prev = *node;
	struct hi_score* new_node = add(*node);
	if (new_node)
	{
		if (*node)tmp = (*node)->next;
		strcpy(new_node->data, data);
		new_node->score = score;
		*node = new_node;
	}
}
/**
* Funkcja s³u¿¹ca do zamiany dwóch elementów w liœcie.
* @param ptr1 Pierwszy element do zamiany
* @param ptr2 Drugi element do zamiany
*/
void swap(struct hi_score** ptr1, struct hi_score** ptr2)
{
	struct hi_score* tmp;
	if ((*ptr1) != NULL && (*ptr2) != NULL)
	{
		if ((*ptr1)->next == (*ptr2) || (*ptr2)->next == (*ptr1))
		{
			if ((*ptr1)->next == (*ptr2))
			{
				(*ptr1)->next = (*ptr2)->next;
				(*ptr2)->prev = (*ptr1)->prev;
				if ((*ptr2)->next)(*ptr2)->next->prev = (*ptr1);
				if ((*ptr1)->prev)(*ptr1)->prev->next = (*ptr2);
				(*ptr1)->prev = (*ptr2);
				(*ptr2)->next = (*ptr1);
			}
			else
			{
				(*ptr2)->next = (*ptr1)->next;
				(*ptr1)->prev = (*ptr2)->prev;
				if ((*ptr1)->next)(*ptr1)->next->prev = (*ptr2);
				if ((*ptr2)->prev)(*ptr2)->prev->next = (*ptr1);
				(*ptr2)->prev = (*ptr1);
				(*ptr1)->next = (*ptr2);
			}
		}
		else
		{
			tmp = (*ptr2)->next;
			(*ptr2)->next = (*ptr1)->next;
			(*ptr1)->next = tmp;
			tmp = (*ptr2)->prev;
			(*ptr2)->prev = (*ptr1)->prev;
			(*ptr1)->prev = tmp;

			if ((*ptr2)->next)(*ptr2)->next->prev = (*ptr2);
			if ((*ptr2)->prev)(*ptr2)->prev->next = (*ptr2);

			if ((*ptr1)->next)(*ptr1)->next->prev = (*ptr1);
			if ((*ptr1)->prev)(*ptr1)->prev->next = (*ptr1);
		}
		tmp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = tmp;
	}
}
void sort(struct hi_score** node)
{
	struct hi_score* wsk1 = *node, * wsk2 = *node, * max = *node;

	if (*node)wsk2 = (*node)->next;
	if (wsk1)
	{
		while (wsk1)
		{
			max = wsk1;
			wsk2 = wsk1->next;
			while (wsk2)
			{
				if (wsk2->score > max->score)
					max = wsk2;
				wsk2 = wsk2->next;
			}
			if (wsk1 != max)
			{
				if (!wsk1->prev)*node = max;
				else if (!max->prev)*node = wsk1;
				swap(&wsk1, &max);
			}			
			wsk1 = wsk1->next;
		}
		while ((*node)->prev)*node = (*node)->prev;
	}

}
void delete_all(struct hi_score** start)
{
	struct hi_score* tmp = *start;
	if(tmp)tmp = tmp->next;
	while (tmp)
	{
		free(*start);
		*start = tmp;
		tmp = tmp->next;
	}
	*start = NULL;
}