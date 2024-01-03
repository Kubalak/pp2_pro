#include "enemies.h"

struct enemy* create_enemy(struct enemy* present)
{
	struct enemy* new_enemy = (struct enemy*)malloc(sizeof(struct enemy));
	if (new_enemy)
	{
		new_enemy->bmp = NULL;
		new_enemy->bmp_1 = NULL;
		new_enemy->prev = NULL;
		new_enemy->next = present;
		if(present)present->prev = new_enemy;
		return new_enemy;
	}
	return NULL;
}

struct enemy* create_enemy_matrix(struct enemy* front, unsigned int rows, unsigned int columns)
{
	rows *= columns;
	for (unsigned int i = 0; i < rows; i++)front = create_enemy(front);
	return front;
}

void enemy_Init(struct enemy* enemies_matrix, float padding_x, float padding_y, unsigned int w, unsigned int h, unsigned int rows, unsigned int columns)
{
	destroy = al_load_bitmap("textures/boom.png");
	float ratio = (float)w / h;
	float space_x, space_y;
	float pos_x = padding_x;
	float pos_y = padding_y;
	float end,end_y;
	space_x = (((w - ((double)2 * padding_x * w) - (double)columns * 0.04f) / (columns - 0.5))) / w;
	space_y = 0.01f * ratio + 0.0325f * ratio;
		//((float)(h - (0.8 * h + (double)0.0325*ratio * rows)) / rows) / h * ratio;
	end = pos_x+columns*space_x;
	end_y = pos_y + rows * space_y;
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			if (enemies_matrix)
			{
				if (i == 0)
				{
					enemies_matrix->enemy_type = 30;
					enemies_matrix->bmp = al_load_bitmap("textures/enemy_2.png");
					enemies_matrix->bmp_1 = al_load_bitmap("textures/enemy_2_1.png");
				}
				else if (i == 1 || i == 2)
				{
					enemies_matrix->enemy_type = 20;
					enemies_matrix->bmp = al_load_bitmap("textures/enemy_1.png");
					enemies_matrix->bmp_1 = al_load_bitmap("textures/enemy_1_1.png");
				}
				else
				{
					enemies_matrix->enemy_type = 10;
					enemies_matrix->bmp = al_load_bitmap("textures/enemy_3.png");
					enemies_matrix->bmp_1 = al_load_bitmap("textures/enemy_3_1.png");
				}
				enemies_matrix->size_x = 0.04f;
				enemies_matrix->size_y = 0.0325f*ratio;
				enemies_matrix->pos_x = pos_x;
				enemies_matrix->pos_y = pos_y;
				enemies_matrix->start_pos = padding_x;
				enemies_matrix->end_pos = end;
				enemies_matrix->end_y_pos = end_y;
				enemies_matrix->row = i;
				enemies_matrix->col = j;
				enemies_matrix->mov = 1;
				pos_x += space_x;
				enemies_matrix = enemies_matrix->next;
			}
		}
		pos_x = padding_x;
		pos_y += space_y;
	}
}

bool draw_enemy(struct enemy* enemy_matrix, unsigned int w, unsigned int h)
{
	if (!enemy_matrix)return true;
	while (enemy_matrix)
	{
		if(enemy_matrix->mov&1)al_draw_scaled_bitmap(enemy_matrix->bmp, 0, 0, al_get_bitmap_width(enemy_matrix->bmp),	al_get_bitmap_height(enemy_matrix->bmp),enemy_matrix->pos_x * w, enemy_matrix->pos_y * h, enemy_matrix->size_x * w, enemy_matrix->size_y * h, 0);
		else al_draw_scaled_bitmap(enemy_matrix->bmp_1, 0, 0, al_get_bitmap_width(enemy_matrix->bmp_1), al_get_bitmap_height(enemy_matrix->bmp_1), enemy_matrix->pos_x * w, enemy_matrix->pos_y * h, enemy_matrix->size_x * w, enemy_matrix->size_y * h, 0);
			enemy_matrix = enemy_matrix->next;
	}
	return false;
}

int destroy_enemy(struct enemy** node)
{
	if (*node)
	{
		struct enemy* next = (*node)->next;
		struct enemy* prev = (*node)->prev;
		al_destroy_bitmap((*node)->bmp);
		al_destroy_bitmap((*node)->bmp_1);
		free(*node);
		if (prev)
		{
			*node = prev;
			prev->next = next;
			if (next)next->prev = prev;
		}
		else if (next)
		{
			*node = next;
			next->prev = NULL;
			return 2;
		}
		else
		{
			*node = NULL;
		}
		return 1;		
	}
	return 0;	
}

void free_enemy_matrix(struct enemy** matrix)
{
	while (destroy_enemy(matrix));	
}
void move_enemy(struct enemy* enemy_list,unsigned int rows,unsigned int columns)
{
	struct enemy* tmp = enemy_list;
	float end_y;
	if (tmp)
	{
		end_y = tmp->end_y_pos;
	}
	while (tmp)
	{
		if (tmp->pos_y + tmp->size_y > end_y)end_y = tmp->pos_y + tmp->size_y;
		tmp = tmp->next;
	}
	tmp = enemy_list;
	while (tmp)
	{
		tmp->end_y_pos = end_y;
		tmp = tmp->next;
	}
	while (enemy_list)
	{
		if (enemy_list->row == rows)
		{
			if (enemy_list->mov <= 2)
			{
				if (enemy_list->end_pos < 0.9f)
				{
					enemy_list->pos_x += 0.01f;
					enemy_list->start_pos += 0.01f;
					enemy_list->end_pos += 0.01f;
					if (enemy_list->mov == 1)enemy_list->mov = 2;
					else enemy_list->mov = 1;
				}
				else
				{
					if (enemy_list->end_y_pos <= 0.85f)
					{
						enemy_list->pos_y += enemy_list->size_y;
						enemy_list->end_y_pos += enemy_list->size_y;
					}
					enemy_list->mov = 3;
				}
			}
			else if (enemy_list->mov > 2)
			{
				if (enemy_list->start_pos > 0.1f)
				{
					enemy_list->pos_x -= 0.01f;
					enemy_list->start_pos -= 0.01f;
					enemy_list->end_pos -= 0.01f;
					if (enemy_list->mov == 3)enemy_list->mov = 4;
					else enemy_list->mov = 3;
				}
				else
				{
					if (enemy_list->end_y_pos <= 0.85f)
					{
						enemy_list->pos_y += enemy_list->size_y;
						enemy_list->end_y_pos += enemy_list->size_y;

					}
					enemy_list->mov = 1;
				}
			}
		}
		enemy_list = enemy_list->next;
	}
		
}