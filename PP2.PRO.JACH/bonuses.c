#include "bonuses.h"
struct bonus* new_bonus(struct bonus* bonus_list, float x, float y, float speed)
{
	struct bonus* new_bul = (struct bonus*)malloc(sizeof(struct bonus));
	if (new_bul)
	{
		new_bul->next = bonus_list;
		new_bul->pos_x = x;
		new_bul->pos_y = y;
		new_bul->speed = speed;
		return new_bul;
	}
	return NULL;
}

void draw_bonuses(struct bonus* bonus_list, unsigned int w, unsigned int h)
{
	struct bonus* tmp;
	tmp = bonus_list;
	float ratio = (float)w / h;
	if (tmp)
	{
		do
		{
			al_draw_scaled_bitmap(tmp->bmp, 0, 0, al_get_bitmap_width(tmp->bmp), al_get_bitmap_height(tmp->bmp), tmp->pos_x*w, tmp->pos_y*h, 0.02 * w, 0.02 * h, 0);
			tmp = tmp->next;
		} while (tmp);
	}

}
void destroy_bonus(struct bonus** begin, struct bonus** node)
{
	struct bonus* prev, * tmp;
	prev = *begin;
	if (prev && *node)
	{
		if (prev != *node)
		{
			do
			{
				if (prev->next)
				{
					if (prev->next == *node)break;
				}
				else break;
				prev = prev->next;
			} while (prev);
			tmp = (*node)->next;
			al_destroy_bitmap((*node)->bmp);
			free(*node);
			prev->next = tmp;
			*node = tmp;
		}
		else
		{
			al_destroy_bitmap((*node)->bmp);
			tmp = (*node)->next;
			free(*node);
			*node = tmp;
			*begin = tmp;
		}
	}
}
void update_bonuses(struct bonus** bonus_list, struct player* play)
{
	struct bonus* tmp = *bonus_list;
	if (play->bonuses & 2)
	{
		play->czasy[0][1] = time(NULL);
		if (play->czasy[0][1] - play->czasy[0][0] >= 5)
		{
			play->bonuses ^= 2;
			play->czasy[0][0] = play->czasy[0][1];
		}
	}
	if (play->bonuses & 4)
	{
		play->czasy[1][1] = time(NULL);
		if (play->czasy[1][1] - play->czasy[1][0] >= 30)
		{
			play->bonuses ^= 4;
			play->czasy[1][0] = play->czasy[1][1];
		}
	}
	if (play->bonuses & 8)
	{
		play->czasy[2][1] = time(NULL);
		if (play->czasy[2][1] - play->czasy[2][0] >= 5)
		{
			play->bonuses ^= 8;
			play->czasy[2][0] = play->czasy[2][1];
		}
	}
	if (play->bonuses & 16)
	{
		play->czasy[3][1] = time(NULL);
		if (play->czasy[3][1] - play->czasy[3][0] >= 10)
		{
			play->bonuses ^= 16;
			play->czasy[3][0] = play->czasy[3][1];
		}
	}
	while (tmp)
	{
		if (tmp->pos_y > 1)destroy_bonus(bonus_list, &tmp);
		if (tmp)
		{
			if (tmp->pos_x + 0.02f >= play->pos_x - play->size_x / 2 && tmp->pos_x - 0.02f <= play->pos_x + play->size_x / 2 && tmp->pos_y >= play->pos_y - play->size_y / 2 && tmp->pos_y <= play->pos_y + play->size_y / 2)
			{
				play->bonuses |= tmp->bonus_type;
				if (play->bonuses & 1)
				{
					play->lives++;
					play->bonuses ^= 1;
				}
				switch (tmp->bonus_type)
				{
					case 2:
						play->czasy[0][0] = time(NULL);
						break;
					case 4:
						play->czasy[1][0] = time(NULL);
						break;
					case 8:
						play->czasy[2][0] = time(NULL);
						break;
					case 16:
						play->czasy[3][0] = time(NULL);
						break;
				}
				destroy_bonus(bonus_list, &tmp);
			}
			if (tmp)
			{
				tmp->pos_y += tmp->speed;
				tmp = tmp->next;
			}
		}		
	}
}

void rand_bonus(struct bonus* bonus_list)
{
	int choice = rand() % 5;
	switch (choice)
	{
		case 0:
			bonus_list->bmp = al_load_bitmap("textures/extra_life.png");
			bonus_list->bonus_type = 1;
			break;
		case 1:
			bonus_list->bmp = al_load_bitmap("textures/enemy_freeze.png");
			bonus_list->bonus_type = 2;
			break;
		case 2:
			bonus_list->bmp = al_load_bitmap("textures/bulletproof.png");
			bonus_list->bonus_type = 4;
			break;
		case 3:
			bonus_list->bmp = al_load_bitmap("textures/mad_bullet.png");
			bonus_list->bonus_type = 8;
			break;
		case 4:
			bonus_list->bmp = al_load_bitmap("textures/double_score.png");
			bonus_list->bonus_type = 16;
			break;
	}	
}