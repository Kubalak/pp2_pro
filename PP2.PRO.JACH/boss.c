#include "boss.h"
/**
* Funkcja inicjuj¹ca bossa.
* @param final WskaŸnik na bossa, którego zamierzamy zainicjowaæ
* @param difficulty Poziom trudnoœci - zale¿y od niego iloœæ ¿ycia bossa
*/
void boss_init(struct boss* final, int difficulty)
{
	final->texture = al_load_bitmap("textures/boss.png");
	final->texture_1 = al_load_bitmap("textures/boss_1.png");
	if (difficulty == 0)final->HP = final->MAXHP = 10000;
	else if (difficulty == 1)final->HP = final->MAXHP = 20000;
	else final->HP = final->MAXHP = 50000;
	final->size_x = 0.3f;
	final->size_y = 0.3f;
	final->pos_x = 0.35f;
	final->pos_y = 0.1f;
	final->direction = final->stage = 1;
}
/**
* Funkcja rysuj¹ca bossa.
* @param overlord Boss do narysowania
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/
void draw_boss(struct boss overlord, unsigned int w, unsigned int h)
{
	if(overlord.stage&1)al_draw_scaled_bitmap(overlord.texture, 0, 0, al_get_bitmap_width(overlord.texture), al_get_bitmap_height(overlord.texture), overlord.pos_x * w, overlord.pos_y * h, overlord.size_x * w, overlord.size_y *(float)w/h * h, 0);
	else al_draw_scaled_bitmap(overlord.texture_1, 0, 0, al_get_bitmap_width(overlord.texture_1), al_get_bitmap_height(overlord.texture_1), overlord.pos_x * w, overlord.pos_y * h, overlord.size_x * w, overlord.size_y * (float)w / h * h, 0);
}
/**
* Funkcja poruszaj¹ca bossem.
* @param final WskaŸnik na bossa, który ma byæ przesuniêty
*/
void mov_boss(struct boss* final)
{
	if (final->direction)
	{
		if (final->pos_x + final->size_x <= 0.9f)
			final->pos_x += 0.015f;
		else
		{
			final->direction = 0;
			if(final->pos_y+final->size_y<0.9f)
			final->pos_y += 0.05f;
		}
	}
	else
	{
		if (final->pos_x >= 0.1f)
			final->pos_x -= 0.015f;
		else
		{
			final->direction = 1;
			if (final->pos_y + final->size_y < 0.9f)
			final->pos_y += 0.05f;
		}
	}
	final->stage ^= 1;
}

/**
* Specjalna funkcja do aktualizacji pocisków gracza, bossa a tak¿e tworzenia bonusów po trafieniu w niego.
* @param player_bul Lista pocisków gracza
* @param enemy_bul Lista pocisków przeciwnika
* @param play Gracz
* @param bonuses Lista bonusów
* @param overlord Boss, z którym walczymy
*/
void final_update_bul(struct bullet** player_bul, struct bullet** enemy_bul, struct player* play,struct bonus** bonuses,struct boss* overlord)
{
	struct bullet* play_tmp, * enem_tmp;
	play_tmp = *player_bul;
	enem_tmp = *enemy_bul;
	if (enem_tmp)
	{
		while (enem_tmp)
		{
			if (enem_tmp->pos_y >= 1.0)destroy_bullet(enemy_bul, &enem_tmp);
			if (enem_tmp)
			{
				while (enem_tmp && play_tmp)
				{

					if (play_tmp->pos_y >= 1.0f || play_tmp->pos_y <= 0.0f)destroy_bullet(player_bul, &play_tmp);
					if (play_tmp)
					{
						if (play_tmp->pos_x >= overlord->pos_x && play_tmp->pos_x <= overlord->pos_x + overlord->size_x && play_tmp->pos_y >= overlord->pos_y && play_tmp->pos_y <= overlord->pos_y + overlord->size_y)
						{
							if (!(play->bonuses & 8))
							{
								if (overlord->HP - 200 >= 0)overlord->HP -= 200;
								else overlord->HP = 0;
								play->score += (play->bonuses & 16) ? 120 : 60;
							}
							else
							{
								if (overlord->HP - 400 >= 0)overlord->HP -= 400;
								else overlord->HP = 0;
								play->score += (play->bonuses & 16) ? 240 : 120;
							}
							if (rand() % 20 >= 15)
							{
								*bonuses = new_bonus(*bonuses, overlord->pos_x+overlord->size_x/2, overlord->pos_y + overlord->size_y, 0.001f);
								rand_bonus(*bonuses);
							}
								
							destroy_bullet(player_bul, &play_tmp);
						}
					if (play_tmp)
						{
							if ((enem_tmp->pos_y + enem_tmp->speed >= play_tmp->pos_y || play_tmp->pos_y + play_tmp->speed <= enem_tmp->pos_y) && enem_tmp->pos_x + 0.0015f >= play_tmp->pos_x - 0.0015f && enem_tmp->pos_x + 0.0015f <= play_tmp->pos_x + 0.0015f)
							{
								destroy_bullet(enemy_bul, &enem_tmp);
								if (!(play->bonuses & 8))destroy_bullet(player_bul, &play_tmp);
							}
							if(play_tmp)play_tmp = play_tmp->next;
						}					
					
					}
					

				}
				if (enem_tmp)
					{
						if (enem_tmp->pos_y >= play->pos_y && enem_tmp->pos_x >= play->pos_x - play->size_x / 2 && enem_tmp->pos_x <= play->pos_x + play->size_x / 2)
						{
							destroy_bullet(enemy_bul, &enem_tmp);
							if (!(play->bonuses & 4))play->lives--;
						}

					}
			}
			play_tmp = *player_bul;
			if (enem_tmp)
			{
				enem_tmp->pos_y += enem_tmp->speed;
				enem_tmp = enem_tmp->next;
			}
		}
		play_tmp = *player_bul;
		while (play_tmp)
		{
			play_tmp->pos_y += play_tmp->speed;
			play_tmp = play_tmp->next;
		}
	}
	else if (play_tmp)
	{
		while (play_tmp)
		{
			if (play_tmp->pos_y >= 1.0f||play_tmp->pos_y <= 0.0f)destroy_bullet(player_bul, &play_tmp);
			if (play_tmp)
			{
				if (play_tmp->pos_x >= overlord->pos_x && play_tmp->pos_x <= overlord->pos_x + overlord->size_x &&play_tmp->pos_y>=overlord->pos_y&& play_tmp->pos_y <= overlord->pos_y+overlord->size_y)
				{
					if (!(play->bonuses & 8))
					{
						if (overlord->HP - 200 >= 0)overlord->HP -= 200;
						else overlord->HP = 0;
						play->score += (play->bonuses & 16) ? 120 : 60;
					}
					else
					{
						if (overlord->HP - 400 >= 0)overlord->HP -= 400;
						else overlord->HP = 0;
						play->score += (play->bonuses & 16) ? 240 : 120;
					}
					if (rand() % 20 >= 15)
					{
						*bonuses = new_bonus(*bonuses, overlord->pos_x + overlord->size_x / 2, overlord->pos_y + overlord->size_y, 0.001f);
						rand_bonus(*bonuses);
					}
					destroy_bullet(player_bul, &play_tmp);
				}
				
			}
			if (play_tmp)
			{
				play_tmp->pos_y += play_tmp->speed;
				play_tmp = play_tmp->next;
			}
		}
	}
}
/**
* Funkcja losuj¹ca czy boss strzeli,a tak¿e ile pocisków wypuœci.
* @param final Boss, który bêdzie strzela³
* @param final_bul Lista pocisków bossa
*/
void rand_shoot(struct boss final, struct bullet** final_bul)
{
	int decision = rand() % 20;
	if (decision >= 10 && decision <= 15)
	{
		int bul_num = 2 + rand() % 4;
		float padding = final.size_x / (bul_num + 1);
		for (int i = 0; i < bul_num; i++)
		{
			*final_bul = new_bullet(*final_bul, final.pos_x +(i+1)*padding, final.pos_y+final.size_y/2, 0.005f);
			(*final_bul)->origin = true;
		}
	}
}
/**
* Funkcja rysuj¹ca wszystkie pociski z <b>dowolnej</b> listy pocisków o kolorze zale¿nym od Ÿród³a pocisku.
* @param bullet_list Lista pocisków
* @param w Szerokoœæ okna
* @param h Wysokoœæ okna
*/

void draw_final_bullets(struct bullet* bullet_list, unsigned int w, unsigned int h)
{
	struct bullet* tmp;
	tmp = bullet_list;
	float ratio = (float)w / h;
	if (tmp)
	{
		do
		{
			if (!tmp->origin)al_draw_filled_rectangle((tmp->pos_x - 0.0015f) * w, (tmp->pos_y - 0.015f) * h, (tmp->pos_x + 0.0015f) * w, (tmp->pos_y + 0.015f) * h, al_map_rgb(0, 255, 0));
			else al_draw_filled_rectangle((tmp->pos_x - 0.0015f) * w, (tmp->pos_y - 0.015f) * h, (tmp->pos_x + 0.0015f) * w, (tmp->pos_y + 0.015f) * h, al_map_rgb(255, 177, 0));
			tmp = tmp->next;
		} while (tmp);
	}

}
void bossfight(ALLEGRO_BITMAP* background, ALLEGRO_FONT* font, ALLEGRO_FONT* font_sm ,ALLEGRO_SAMPLE_INSTANCE*instance, ALLEGRO_SAMPLE_INSTANCE* music, ALLEGRO_EVENT_QUEUE *queue,ALLEGRO_EVENT *event,struct player* play, unsigned int difficulty, unsigned int w, unsigned int h)
{
	ALLEGRO_KEYBOARD_STATE state;
	ALLEGRO_BITMAP* lifebar = al_load_bitmap("textures/healthbar.png");
	ALLEGRO_BITMAP* lifebar_background = al_load_bitmap("textures/healthbar_dark.png");
	clock_t czas_1, czas_2,bos_1,bos_2;
	time_t span;
	struct bullet* player_bul = NULL, * enemy_bul = NULL;
	struct boss overlord;
	struct bonus* bonus_list = NULL;
	boss_init(&overlord, difficulty);
	al_get_keyboard_state(&state);
	al_wait_for_event_timed(queue, event, 0.01f);
	czas_1 = czas_2 = bos_1 = bos_2 = clock();
	play->bonuses = 0;
	while (!al_key_down(&state, ALLEGRO_KEY_ESCAPE) && (*event).display.type != ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		al_get_keyboard_state(&state);
		al_wait_for_event_timed(queue, event, 0.01f);
		czas_2 = clock();
		bos_2 = clock();
		if (al_key_down(&state, ALLEGRO_KEY_LEFT) || al_key_down(&state, ALLEGRO_KEY_A))
		{
			Update_player_Pos(play,play->speed_x , play->speed_y);
		}
		if (al_key_down(&state, ALLEGRO_KEY_RIGHT) || al_key_down(&state, ALLEGRO_KEY_D))
		{
			Update_player_Pos(play, -play->speed_x, play->speed_y);
		}
		if ((*event).keyboard.keycode == ALLEGRO_KEY_SPACE && (*event).type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (czas_2-czas_1 >= 650)
			{
				czas_1 = czas_2;
				al_set_sample_instance_playing(instance, true);
				shoot(&player_bul, *play);
			}
		}
		if (al_key_down(&state, ALLEGRO_KEY_P) && (*event).type == ALLEGRO_EVENT_KEY_DOWN)
		{
			al_set_sample_instance_playing(music, false);
			do
			{
				for (int i = 0; i < 4; i++)
				{
					span = play->czasy[i][1] - play->czasy[i][0];
					play->czasy[i][0] = time(NULL);
					play->czasy[i][1] = play->czasy[i][0] + span;
				}
				al_wait_for_event_timed(queue, event, 0.05f);
				al_get_keyboard_state(&state);
				al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, w, h, 0);
				al_draw_text(font, al_map_rgb(39, 255, 0), 0.5 * w, 0.5 * h, ALLEGRO_ALIGN_CENTRE, "Game paused");
				al_flip_display();
			} while ((!al_key_down(&state, ALLEGRO_KEY_P) && !al_key_down(&state, ALLEGRO_KEY_ESCAPE)) || (*event).type != ALLEGRO_EVENT_KEY_DOWN);
			al_set_sample_instance_playing(music, true);
		}
		if ((*event).display.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, w, h, 0);
		al_draw_scaled_bitmap(lifebar_background, 0, 0, al_get_bitmap_width(lifebar_background), al_get_bitmap_height(lifebar_background), 0.1 * w, 0.05 * h, 0.8 * w, 0.01 * h, 0);
		al_draw_scaled_bitmap(lifebar, 0, 0, al_get_bitmap_width(lifebar), al_get_bitmap_height(lifebar), 0.1 * w, 0.05 * h, 0.8 * w*((float)overlord.HP / overlord.MAXHP), 0.01 * h , 0);
		update_bonuses(&bonus_list, play);
		final_update_bul(&player_bul, &enemy_bul, play,&bonus_list, &overlord);
		if (bos_2 - bos_1 >= 300)
		{
			bos_1 = bos_2;
			if (!(play->bonuses & 2))
			{
				mov_boss(&overlord);
				rand_shoot(overlord, &enemy_bul);
			}
		}
		if (overlord.pos_y + overlord.size_y*(float)w/h >= play->pos_y && play->pos_x >= overlord.pos_x && play->pos_x + play->size_x <= overlord.pos_x + overlord.size_x)
		{
			overlord.pos_x = 0.35f;
			overlord.pos_y = 0.1f;
			play->lives--;
		}
		draw_score(*play,font,w,h);
		draw_final_bullets(player_bul, w, h);
		draw_final_bullets(enemy_bul, w, h);
		draw_boss(overlord, w, h);
		draw_player(*play, w, h);
		draw_bonuses(bonus_list, w, h);
		show_player_state(font_sm, *play, w, h);
		al_flip_display();
		if (!is_alive(*play)) break;
		if (overlord.HP <= 0)break;
	}
	al_destroy_bitmap(overlord.texture);
	al_destroy_bitmap(overlord.texture_1);
}