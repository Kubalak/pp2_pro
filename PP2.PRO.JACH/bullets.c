#include "bullets.h"
struct bullet* new_bullet(struct bullet* bullet_list, float x, float y, float speed)
{
	struct bullet* new_bul = (struct bullet*)malloc(sizeof(struct bullet));
	if (new_bul)
	{
		new_bul->next = bullet_list;
		new_bul->pos_x = x;
		new_bul->pos_y = y;
		new_bul->speed = speed;
		return new_bul;
	}
	return NULL;
}

void draw_bullets(struct bullet* bullet_list, unsigned int w, unsigned int h)
{
	struct bullet* tmp;
	tmp = bullet_list;
	float ratio = (float)w / h;
	if (tmp)
	{
		do
		{
			if(!tmp->origin)al_draw_filled_rectangle((tmp->pos_x - 0.0015f) * w, (tmp->pos_y - 0.015f) * h, (tmp->pos_x + 0.0015f) * w, (tmp->pos_y + 0.015f) * h, al_map_rgb(0, 255, 0));
			else al_draw_filled_rectangle((tmp->pos_x - 0.0015f) * w, (tmp->pos_y - 0.015f) * h, (tmp->pos_x + 0.0015f) * w, (tmp->pos_y + 0.015f) * h, al_map_rgb(255, 0, 0));
			tmp = tmp->next;
		} while (tmp);
	}

}
void destroy_bullet(struct bullet** begin, struct bullet** node)
{
	struct bullet* prev, * tmp;
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
			free(*node);
			prev->next = tmp;
			*node = tmp;
		}
		else
		{
			tmp = (*node)->next;
			free(*node);
			*node = tmp;
			*begin = tmp;
		}
	}
}
void shoot(struct bullet** bullet_list, struct player play)
{
	*bullet_list = new_bullet(*bullet_list, play.pos_x, play.pos_y - play.size_y / 2, -0.01f);
	(*bullet_list)->origin = false;
}
int update_bullets(ALLEGRO_SAMPLE_INSTANCE *boom,struct bullet** bullet_list, struct bullet** enemy_bullet_list, struct bonus** bonus_list, struct player* play, struct enemy** enemy_matrix, unsigned int w, unsigned int h)
{
	struct bullet* tmp,*enem_tmp;
	struct enemy* enemy;
	enemy = *enemy_matrix;
	tmp = *bullet_list;
	enem_tmp = *enemy_bullet_list;
	int bonus;
	float ratio = (float)w / h;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->pos_y > 1.0f || tmp->pos_y < 0.0f)destroy_bullet(bullet_list, &tmp);
			while (enem_tmp)
			{
				if (enem_tmp->pos_y > 1.0f || enem_tmp->pos_y < 0.0f)destroy_bullet(enemy_bullet_list, &enem_tmp);
				if (enem_tmp)
				{
					if (tmp)
					if ((enem_tmp->pos_y+enem_tmp->speed >= tmp->pos_y || tmp->pos_y + tmp->speed  <= enem_tmp->pos_y) && enem_tmp->pos_x + 0.0015f >= tmp->pos_x-0.0015f && enem_tmp->pos_x + 0.0015f <= tmp->pos_x + 0.0015f)
					{
						destroy_bullet(enemy_bullet_list, &enem_tmp);
						if(!(play->bonuses & 8))destroy_bullet(bullet_list, &tmp);
					}
					if (enem_tmp)
					{	if(!(play->bonuses & 4))
						if (enem_tmp->pos_y >= play->pos_y && enem_tmp->pos_x >= play->pos_x - play->size_x / 2 && enem_tmp->pos_x <= play->pos_x + play->size_x / 2)
						{
							destroy_bullet(enemy_bullet_list, &enem_tmp);
							return 0;
						}	
						else if (enem_tmp->pos_y >= play->pos_y && enem_tmp->pos_x >= play->pos_x - play->size_x / 2 && enem_tmp->pos_x <= play->pos_x + play->size_x / 2)
						{
								destroy_bullet(enemy_bullet_list, &enem_tmp);							
						}
						enem_tmp = enem_tmp->next;
					}
				}
			}
			if (tmp && enemy)
			{
				while (enemy && tmp)
				{
					if (enemy->pos_x > 1.0)return -1;
					if (enemy->pos_y + enemy->size_y >= play->pos_y)
					{
						if (!(play->bonuses & 4))
						{
							if (enemy->pos_x - enemy->size_x / 2 <= play->pos_x && enemy->pos_x + enemy->size_x / 2 >= play->pos_x)
							{
								if (destroy_enemy(&enemy) == 2)*enemy_matrix = enemy;
								if (enemy == NULL)*enemy_matrix = enemy;
								return 0;
							}
						}
						else 
						{
							if (enemy->pos_x - enemy->size_x / 2 <= play->pos_x && enemy->pos_x + enemy->size_x / 2 >= play->pos_x)
								if (destroy_enemy(&enemy) == 2)*enemy_matrix = enemy;
							if (enemy == NULL)*enemy_matrix = enemy;
						}							
					}
					if(enemy)
					if (tmp->pos_x + 0.0015f >= enemy->pos_x && tmp->pos_x - 0.0015f <= enemy->pos_x + enemy->size_x && tmp->pos_y + tmp->speed + 0.015f >= enemy->pos_y && tmp->pos_y + tmp->speed - 0.015f <= enemy->pos_y)
					{
						al_set_sample_instance_playing(boom, true);
						if(!(play->bonuses&8)) destroy_bullet(bullet_list, &tmp);
						if (!(play->bonuses & 16))play->score += enemy->enemy_type;
						else play->score += 2 * enemy->enemy_type;
						al_draw_scaled_bitmap(destroy, 0, 0, al_get_bitmap_width(destroy), al_get_bitmap_height(destroy), enemy->pos_x * w, enemy->pos_y * h, enemy->size_x * w, enemy->size_y * h * ratio, 0);
						bonus = rand() % 30;
						if (bonus >= 10 && bonus <= 15)
						{
							*bonus_list = new_bonus(*bonus_list, enemy->pos_x, enemy->pos_y, 0.001f);
							rand_bonus(*bonus_list);
						}
						if (destroy_enemy(&enemy) == 2)*enemy_matrix = enemy;
						if (enemy == NULL)*enemy_matrix = NULL;
					}
					if(enemy)
						if (enemy->pos_y > play->pos_y+play->size_y)
						return -1;
					if (enemy)enemy = enemy->next;
				}
				enemy = *enemy_matrix;
				if (tmp)tmp->pos_y += tmp->speed;
			}
			if (tmp)tmp = tmp->next;
			enem_tmp = *enemy_bullet_list;
		}
		while (enem_tmp)
		{
			enem_tmp->pos_y += enem_tmp->speed;
			enem_tmp = enem_tmp->next;
		}
		return 1;
	}
	else if (enemy)
	{
		while (enemy)
		{
			if (enemy->pos_x + enemy->size_y > 1.0f)return -1;
			if (enemy->pos_y + enemy->size_y >= play->pos_y)
			{
				if (!(play->bonuses & 4))
				{
					if (enemy->pos_x - enemy->size_x / 2 <= play->pos_x && enemy->pos_x + enemy->size_x / 2 >= play->pos_x)
					{
						if (destroy_enemy(&enemy) == 2)*enemy_matrix = enemy;
						if (enemy == NULL)*enemy_matrix = enemy;
						return 0;
					}
				}
				else
				{
					if (enemy->pos_x - enemy->size_x / 2 <= play->pos_x && enemy->pos_x + enemy->size_x / 2 >= play->pos_x)
					{
						if (destroy_enemy(&enemy) == 2)*enemy_matrix = enemy;
						if (enemy == NULL)*enemy_matrix = enemy;
					}
				}
			}
			if(enemy)enemy = enemy->next;
		}
		if (enem_tmp)
		{
			while (enem_tmp)
			{
				if (enem_tmp->pos_y > 1.0f || enem_tmp->pos_y < 0.0f)destroy_bullet(enemy_bullet_list, &enem_tmp);
				if (enem_tmp)
				{
					if (enem_tmp->pos_y >= play->pos_y && enem_tmp->pos_x >= play->pos_x - play->size_x/2 && enem_tmp->pos_x <= play->pos_x + play->size_x/2)
					{
						destroy_bullet(enemy_bullet_list, &enem_tmp);
						return 0;
					}
					enem_tmp->pos_y += enem_tmp->speed;
					enem_tmp = enem_tmp->next;
				}
			}			
		}
		return 1;
	}
	else return 1;
}
/**
* Funckja odpowiedzialna za strza³ przeciwnika.
* @param enemy_bul Pocz¹tek listy pocisków
* @param enem Przeciwnik od którego pochodziæ bêdzie nowy pocisk
*/
void enemy_shoot(struct bullet** enemy_bul, struct enemy* enem)
{
	*enemy_bul = new_bullet(*enemy_bul, enem->pos_x+enem->size_x/2, enem->pos_y+enem->size_y, 0.005f);
	(*enemy_bul)->origin = true;
}
/**
* Funckja zwracaj¹ca iloœæ przeciwników.
* @param enem Lista przeciwników
*/
int get_enem_count(struct enemy* enem)
{
	int i = 0;
	if (enem)
		while (enem)
		{
			i++;
			enem = enem->next;
		}
	else
		return -1;
	return i;
}

void rand_enemy_shoot(struct bullet** enemy_bul, struct enemy* enem)
{
	int choice = rand() % get_enem_count(enem);
	int i = 0;
	while (enem)
	{
		if (i == choice)
		{
			enemy_shoot(enemy_bul, enem);
			break;
		}
		i++;
		enem = enem->next;
	}
}