#include "player.h"

void player_Init(struct player* play, unsigned int w, unsigned int h)
{
	float ratio = (float)w / h;
	play->player_bmp = al_load_bitmap("textures/player.png");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			play->czasy[i][j] = (clock_t)0;
	play->life = al_load_bitmap("textures/extra_life.png");
	play->bonus1 = al_load_bitmap("textures/enemy_freeze.png");
	play->bonus2 = al_load_bitmap("textures/bulletproof.png");
	play->bonus3 = al_load_bitmap("textures/mad_bullet.png");
	play->bonus4 = al_load_bitmap("textures/double_score.png");
	play->state = ALIVE;
	play->pos_x = 0.5f;
	play->size_x = 0.05f;
	play->size_y = 0.02625f*ratio;
	play->bonuses = 0;
	play->pos_y = 1.0f - play->size_y;
}

void Update_player_Pos(struct player* play, float vector_x, float vector_y)
{
	if (play->pos_x + play->size_x + vector_x <= 1.0f && play->pos_x - play->size_x + vector_x >= 0.0f)
	{
		play->pos_x += vector_x;
	}
	else if (play->pos_x + play->size_x + vector_x > 1.0f)
	{
		play->pos_x = 1.0f - play->size_x;
	}
	else if (play->pos_x - play->size_x + vector_x < 1.0f)
	{
		play->pos_x = 0.0f + play->size_x;
	}
	if (play->pos_y + play->size_y + vector_y <= 1.0f && play->pos_y - play->size_y + vector_y >= 0.0f)
	{
		play->pos_y += vector_y;
	}
	else if (play->pos_y + play->size_y + vector_y > 1.0f)
	{
		play->pos_y = 1.0f - play->size_y;
	}
	else if (play->pos_y - play->size_y + vector_y < 0.0f)
	{
		play->pos_y = 0.0f + play->size_y;
	}
}

char is_alive(struct player play)
{
	if (play.lives >= 0)return ALIVE;
	return DEAD;
}

void draw_player(struct player play, unsigned int w,unsigned  int h)
{
	al_draw_scaled_bitmap(play.player_bmp, 0, 0, al_get_bitmap_width(play.player_bmp), al_get_bitmap_height(play.player_bmp), play.pos_x * w - play.size_x * w / 2, play.pos_y * h - play.size_y * h / 2, play.size_x * w, play.size_y * h, 0);
}

void draw_score(struct player play, ALLEGRO_FONT* font, unsigned int w, unsigned int h)
{
	al_draw_textf(font, al_map_rgb(39, 255, 0), 0.1 * w, 0.01 * h, 0, "SCORE <%d>", play.score);
}

void show_player_state(ALLEGRO_FONT* font, struct player play,unsigned int w, unsigned int h)
{
	al_draw_textf(font, al_map_rgb(39, 255,0), 0.9 * w, 0.01 * h, 0, "%d", play.lives);
	al_draw_scaled_bitmap(play.life, 0, 0, al_get_bitmap_width(play.life), al_get_bitmap_height(play.life), 0.95 * w, 0.01 * h , 0.02f * w, 0.02f * h, 0);
	float pos = 0.04f;
	if (play.bonuses & 2)
	{
		al_draw_scaled_bitmap(play.bonus1, 0, 0, al_get_bitmap_width(play.bonus1), al_get_bitmap_height(play.bonus1), 0.95 * w, pos * h, 0.02f *w, 0.02f * h, 0);
		al_draw_textf(font, al_map_rgb(39, 255, 0), 0.9 * w, pos * h, 0, "%d", 5 - (play.czasy[0][1]-play.czasy[0][0]));
		pos += 0.03f;
	}
	if (play.bonuses & 4)
	{
		al_draw_scaled_bitmap(play.bonus2, 0, 0, al_get_bitmap_width(play.bonus2), al_get_bitmap_height(play.bonus2), 0.95 * w, pos * h, 0.02f * w, 0.02f * h, 0);
		al_draw_textf(font, al_map_rgb(39, 255, 0), 0.9 * w,pos * h, 0, "%d", 30 - (play.czasy[1][1] - play.czasy[1][0]));
		pos += 0.03f;
	}
	if (play.bonuses & 8)
	{
		al_draw_scaled_bitmap(play.bonus3, 0, 0, al_get_bitmap_width(play.bonus3), al_get_bitmap_height(play.bonus3), 0.95 * w, pos * h, 0.02f * w, 0.02f * h, 0);
		al_draw_textf(font, al_map_rgb(39, 255, 0), 0.9 * w, pos * h, 0, "%d", 5 - (play.czasy[2][1] - play.czasy[2][0]));
		pos += 0.03f;
	}

	if (play.bonuses & 16)
	{
		al_draw_scaled_bitmap(play.bonus4, 0, 0, al_get_bitmap_width(play.bonus4), al_get_bitmap_height(play.bonus4), 0.95 * w, pos * h, 0.02f * w, 0.02f * h, 0);
		al_draw_textf(font, al_map_rgb(39, 255, 0), 0.9 * w, pos * h, 0, "%d", 10 - (play.czasy[3][1] - play.czasy[3][0]));
	}
}