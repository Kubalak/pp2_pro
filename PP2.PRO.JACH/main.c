#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "bullets.h"
#include "enemies.h"
#include "resource.h"
#include "hi_scores.h"
#include "menu.h"
#include "bonuses.h"
#include "boss.h"
/**
* G³ówna funkcja programu.
* @param argc Liczba argumentów, z którymi uruchamiany jest program
* @param argv Lista wskaŸników do argumentów wywo³ania programu
*
*/

int main(int argc, char** argv)
{
	al_install_system(ALLEGRO_VERSION, NULL);
	al_init();
	float padding = 0.2f;
	float padding_top = 0.2f;
	int count = 100;
	char data[16];
	time_t czas;
	struct tm date;
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_install_keyboard();
	al_init_acodec_addon();
	al_set_app_name("Space Invaders");
	al_set_new_display_flags(ALLEGRO_FRAMELESS);
	int screen_w = 1024, screen_h = 768, mov_speed = 1, difficulty = 1;
	bool fullscreen = 0;
	float speed = 1.0f;
	ALLEGRO_CONFIG* cfg = al_load_config_file("data/options.ini");
	if (!cfg)
	{
		cfg = al_create_config();
		al_add_config_section(cfg, "Difficulty");
		al_set_config_value(cfg, "Difficulty", "Lvl", "1");
		al_add_config_section(cfg, "Fullscreen");
		al_set_config_value(cfg, "Fullscreen", "Value", "0");
		al_add_config_section(cfg, "Resolution");
		al_set_config_value(cfg, "Resolution", "Width", "1024");
		al_set_config_value(cfg, "Resolution", "Height", "768");
		al_add_config_section(cfg, "Speed");
		al_set_config_value(cfg, "Speed", "Value", "1");
		al_save_config_file("data/options.ini", cfg);
	}
	else
	{
		difficulty = atoi(al_get_config_value(cfg, "Difficulty", "Lvl"));
		if (atoi(al_get_config_value(cfg, "Fullscreen", "Value")))fullscreen = true;
		else fullscreen = false;
		screen_w = atoi(al_get_config_value(cfg, "Resolution", "Width"));
		screen_h = atoi(al_get_config_value(cfg, "Resolution", "Height"));
		mov_speed = atoi(al_get_config_value(cfg, "Speed", "Value"));
		if (mov_speed == 0)speed = 0.5f;
		else if (mov_speed == 2)speed = 1.5f;
	}
	ALLEGRO_DISPLAY* startup = al_create_display(200, 100);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	struct hi_score* scores = NULL;
	struct hi_score* wynik = NULL;
	struct bonus* bonuses = NULL;
	int result;
	ALLEGRO_BITMAP* enemy = al_load_bitmap("textures/enemy_1.png");
	ALLEGRO_BITMAP* steer = al_load_bitmap("textures/steering.png");
	ALLEGRO_BITMAP* pause = al_load_bitmap("textures/pause.png");
	ALLEGRO_BITMAP* exit = al_load_bitmap("textures/exit.png");
	al_draw_scaled_bitmap(enemy, 0, 0, al_get_bitmap_width(enemy), al_get_bitmap_height(enemy), 50, 10, 100, 80, 0);
	ALLEGRO_TIMER* timer = al_create_timer(0.75);
	ALLEGRO_TIMER* enem = al_create_timer(0.002);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_KEYBOARD_STATE state;
	ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_MIXER* mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	ALLEGRO_SAMPLE* boom = al_load_sample("sounds/invaderkilled.wav");
	ALLEGRO_SAMPLE_INSTANCE* boom_inst = al_create_sample_instance(boom);
	ALLEGRO_SAMPLE* sample = al_load_sample("sounds/shoot.wav");
	ALLEGRO_SAMPLE_INSTANCE* instance = al_create_sample_instance(sample);
	ALLEGRO_SAMPLE* winner = al_load_sample("sounds/victory.wav");
	ALLEGRO_SAMPLE_INSTANCE* win_inst = al_create_sample_instance(winner);
	ALLEGRO_SAMPLE* music = al_load_sample("sounds/music.mp3");
	ALLEGRO_SAMPLE_INSTANCE* music_inst = al_create_sample_instance(music);
	al_attach_sample_instance_to_mixer(instance, mixer);
	al_attach_sample_instance_to_mixer(boom_inst, mixer);
	al_attach_sample_instance_to_mixer(win_inst, mixer);
	al_attach_sample_instance_to_mixer(music_inst, mixer);
	al_attach_mixer_to_voice(mixer, voice);
	al_set_sample_instance_gain(music_inst, 0.05f);
	al_set_sample_instance_playmode(music_inst, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(win_inst, 0.1f);
	al_set_sample_instance_gain(instance, 0.4f);
	al_set_sample_instance_gain(boom_inst, 0.4f);
	/*
	 Tutaj bêdziemy sprawdzaæ  czy dostêpne s¹ wszystkie zasoby
	*/
	al_flip_display();
	al_rest(0.5);
	al_destroy_display(startup);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
	ALLEGRO_DISPLAY* display = al_create_display(screen_w, screen_h);
	al_set_display_flag(display, ALLEGRO_FRAMELESS, true);
	if (fullscreen)
	{
		al_set_display_flag(display, ALLEGRO_FULLSCREEN, true);
		al_set_display_flag(display, ALLEGRO_MAXIMIZED, true);
	}
	ALLEGRO_FONT* font = al_load_ttf_font("fonts/INVADERS.ttf", 0.0375f * screen_w, 0);
	ALLEGRO_FONT* font_sm = al_load_ttf_font("fonts/INVADERS.ttf", 0.025f * screen_w, 0);
	ALLEGRO_FONT* font_vsm = al_load_ttf_font("fonts/INVADERS.ttf", 0.015f * screen_w, 0);
	ALLEGRO_BITMAP* background = al_load_bitmap("textures/background.png");
	srand(time(NULL));
	clock_t start;
	clock_t finish;
	unsigned long long int span;


	if (al_is_keyboard_installed())
	{
		/*Przed w³aœciwym uruchomieniem gry*/
		if (menu(cfg, display, &state, &font, &font_sm, background, &screen_w, &screen_h) == 0)
		{
			int position_x = screen_w / 2, position_y = screen_h / 2;
			struct player nowy;
			nowy.score = 0;
			nowy.lives = 3;
			unsigned int rows = 0, cols = 0, curr_row = 0;
			
			difficulty = atoi(al_get_config_value(cfg, "Difficulty", "Lvl"));
			if (difficulty == 0)
			{
				padding_top = 0.2f;
				padding = 0.25f;
				rows = 3;
				cols = 6;
				curr_row = 3;
			}
			else if (difficulty == 1)
			{
				padding = 0.2f;
				padding_top = 0.2f;
				rows = 5;
				cols = 11;
				curr_row = 5;
			}
			else
			{
				padding_top = 0.05f;
				padding = 0.15f;
				rows = 10;
				cols = 16;
				curr_row = 10;
			}
			load_data(&scores, difficulty);
			al_destroy_font(font);
			al_destroy_font(font_sm);
			al_destroy_font(font_vsm);
			font = al_load_ttf_font("fonts/INVADERS.ttf", 0.0375f * screen_w, 0);
			font_sm = al_load_ttf_font("fonts/INVADERS.ttf", 0.025f * screen_w, 0);
			font_vsm = al_load_ttf_font("fonts/INVADERS.ttf", 0.015f * screen_w, 0);
			struct enemy* wrogowie = NULL;
			nowy.speed_x = -0.01f * speed;
			nowy.speed_y = 0.0f;
			struct bullet* bullets = NULL;
			struct bullet* enemy_bullets = NULL;
			difficulty = atoi(al_get_config_value(cfg, "Difficulty", "Lvl"));
			mov_speed = atoi(al_get_config_value(cfg, "Speed", "Value"));
			if (mov_speed == 0)speed = 0.5f;
			else if (mov_speed == 2)speed = 1.5f;
			else speed = 1.0f;

			al_get_keyboard_state(&state);
			al_register_event_source(queue, al_get_display_event_source(display));
			al_register_event_source(queue, al_get_keyboard_event_source());
			ALLEGRO_EVENT event;
			al_wait_for_event_timed(queue, &event, 0.01f);
			/*Gra*/
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
			al_draw_scaled_bitmap(steer, 0, 0, al_get_bitmap_width(steer), al_get_bitmap_height(steer),0.2*screen_w, 0.2 *(float)screen_h/screen_w * screen_h, 0.6 * screen_w, 0.5 * ((float)screen_w / screen_h) * screen_h, 0);
			al_draw_scaled_bitmap(pause, 0, 0, al_get_bitmap_width(pause), al_get_bitmap_height(pause), 0.85 * screen_w, 0.05 * screen_h, 0.1 * screen_w, 0.05 * (float)screen_w / screen_h * screen_h, 0);
			al_draw_scaled_bitmap(exit, 0, 0, al_get_bitmap_width(exit), al_get_bitmap_height(exit), 0.05 * screen_w, 0.05 * screen_h, 0.1 * screen_w, 0.05 * (float)screen_w / screen_h * screen_h, 0);
			al_flip_display();
			al_rest(2.0);
			al_set_sample_instance_playing(music_inst, true);
			al_start_timer(timer);
			al_start_timer(enem);
			start = clock();
			player_Init(&nowy, screen_w, screen_h);
			for (int i = 1; i <= 3; i++)
			{
				while (enemy_bullets)destroy_bullet(&enemy_bullets, &enemy_bullets);
				while (bullets)destroy_bullet(&bullets, &bullets);
				while (bonuses)destroy_bonus(&bonuses, &bonuses);
				count = 100;
				curr_row = rows;
				wrogowie = create_enemy_matrix(NULL, rows, cols);
				al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
				al_draw_textf(font, al_map_rgb(39, 255, 0), screen_w / 2, 0.5 * screen_h, ALLEGRO_ALIGN_CENTRE, "WAVE %s", (i == 1) ? "ONE" : (i == 2) ? "TWO" : "THREE");
				al_flip_display();
				nowy.bonuses = 0;
				nowy.pos_x = 0.5f;
				enemy_Init(wrogowie, padding, padding_top, screen_w, screen_h, rows, cols);
				al_rest(1.0);
				while (!al_key_down(&state, ALLEGRO_KEY_ESCAPE))
				{
					al_get_keyboard_state(&state);
					if (al_key_down(&state, ALLEGRO_KEY_ESCAPE))
					{
						i = 4;
						break;
					}
					if (al_key_down(&state, ALLEGRO_KEY_LEFT) || al_key_down(&state, ALLEGRO_KEY_A))
					{
						Update_player_Pos(&nowy, nowy.speed_x, nowy.speed_y);
					}
					if (al_key_down(&state, ALLEGRO_KEY_RIGHT) || al_key_down(&state, ALLEGRO_KEY_D))
					{
						Update_player_Pos(&nowy, -nowy.speed_x, nowy.speed_y);
					}
					if (al_key_down(&state, ALLEGRO_KEY_P) && event.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						al_set_sample_instance_playing(music_inst, false);
						do
						{
							span = (unsigned long long int)finish - start;
							start = clock();
							finish = start + span;
							for (int i = 0; i < 4; i++)
							{
								span = nowy.czasy[i][1] - nowy.czasy[i][0];
								nowy.czasy[i][0] = time(NULL);
								nowy.czasy[i][1] = nowy.czasy[i][0] + span;
							}
							al_wait_for_event_timed(queue, &event, 0.05f);
							al_get_keyboard_state(&state);
							al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
							al_draw_text(font, al_map_rgb(39, 255, 0), 0.5 * screen_w, 0.5 * screen_h, ALLEGRO_ALIGN_CENTRE, "Game paused");
							al_flip_display();
						} while ((!al_key_down(&state, ALLEGRO_KEY_P) && !al_key_down(&state,ALLEGRO_KEY_ESCAPE))|| event.type != ALLEGRO_EVENT_KEY_DOWN  );						
						al_set_sample_instance_playing(music_inst, true);
					}
					if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && event.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						if (al_get_timer_count(timer) >= 1)
						{
							al_set_timer_count(timer, 0);
							al_set_sample_instance_playing(instance, true);
							shoot(&bullets, nowy);
						}
					}
					if (event.display.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						free_enemy_matrix(&wrogowie);
						break;
					}
					al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
					result = update_bullets(boom_inst, &bullets, &enemy_bullets, &bonuses, &nowy, &wrogowie, screen_w, screen_h);
					if (!result && !(nowy.bonuses & 4))
					{
						nowy.lives--;						
					}
					else if (result == -1)
					{
						nowy.lives--;
						nowy.score = 0;
						free_enemy_matrix(&wrogowie);
						wrogowie = create_enemy_matrix(wrogowie, rows, cols);
						enemy_Init(wrogowie, padding, padding_top, screen_w, screen_h, rows, cols);
					}
					if (!is_alive(nowy))
					{
						i = 4;
						break;
					}
					show_player_state(font_vsm, nowy, screen_w, screen_h);
					draw_bullets(bullets, screen_w, screen_h);
					draw_bullets(enemy_bullets, screen_w, screen_h);
					draw_bonuses(bonuses, screen_w, screen_h);
					draw_player(nowy, screen_w, screen_h);
					update_bonuses(&bonuses, &nowy);
					draw_score(nowy, font_sm, screen_w, screen_h);
					if (al_get_timer_count(enem) >= count)
					{
						al_set_timer_count(enem, 0);
						if (!(nowy.bonuses & 2))
						{
							move_enemy(wrogowie, curr_row, cols);
							if (curr_row > 0)curr_row--;
							else
							{
								curr_row = rows;
								if (count - 1 >= 1)count -= 1;
							}
						}
					}
					finish = clock();
					if (finish - start >= 1000/i)
					{
						if (!(nowy.bonuses & 2))rand_enemy_shoot(&enemy_bullets, wrogowie);
						start = finish;
					}
					if (draw_enemy(wrogowie, screen_w, screen_h))
					{
						break;
					}
					al_flip_display();
					al_wait_for_event_timed(queue, &event, 0.001f);
				}
				
				free_enemy_matrix(&wrogowie);
			}
			if(is_alive(nowy)&&!al_key_down(&state,ALLEGRO_KEY_ESCAPE))	bossfight(background,font_sm,font_vsm,instance,music_inst,queue,&event,&nowy,difficulty,screen_w,screen_h);
			al_get_keyboard_state(&state);
			if (!al_key_down(&state, ALLEGRO_KEY_ESCAPE))
			{
				if (is_alive(nowy))
				{
					time(&czas);
					localtime_s(&date, &czas);
					strftime(data, 16, "%d.%m.%y ", &date);
					new_score(&scores, data, nowy.score);
					al_set_sample_instance_playing(music_inst, false);
					al_set_sample_instance_playing(win_inst, true);
					/*Koniec gry */
					while (!al_key_down(&state, ALLEGRO_KEY_ENTER) && event.display.type != ALLEGRO_EVENT_DISPLAY_CLOSE)
					{

						al_get_keyboard_state(&state);
						al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
						al_draw_text(font, al_map_rgb(39, 255, 0), (1.0f - (float)al_get_text_width(font, "You won! Press Enter to continue...") / screen_w) * 0.5f * screen_w, 0.5 * screen_h - 15, 0, "You won! Press Enter to continue...");
						al_wait_for_event_timed(queue, &event, 0.01f);
						al_flip_display();
					}
					set_name(font, background, scores, screen_w, screen_h);
					wynik = scores;
					sort(&scores);
					save_data(scores, difficulty);
					al_set_sample_instance_playing(win_inst, false);
					print_hi_score(font_sm, background, scores, wynik, screen_w, screen_h);
					delete_all(&scores);
				}
				else
				{
					time(&czas);
					localtime_s(&date, &czas);
					strftime(data, 16, "%d.%m.%y ", &date);
					new_score(&scores, data, nowy.score);
					al_set_sample_instance_playing(music_inst, false);
					while (!al_key_down(&state, ALLEGRO_KEY_ENTER) && event.display.type != ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						al_get_keyboard_state(&state);
						al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, screen_w, screen_h, 0);
						al_draw_text(font, al_map_rgb(255, 15, 0), (1.0f - (float)al_get_text_width(font, "Game over! Press Enter to continue...") / screen_w) * 0.5f * screen_w, 0.5 * screen_h - 15, 0, "Game over! Press Enter to continue...");
						al_wait_for_event_timed(queue, &event, 0.01f);
						al_flip_display();
					}
					set_name(font, background, scores, screen_w, screen_h);
					wynik = scores;
					sort(&scores);
					save_data(scores, difficulty);
					print_hi_score(font_sm, background, scores, wynik, screen_w, screen_h);
					delete_all(&scores);
				}
			}
			al_destroy_bitmap(pause);
			al_destroy_bitmap(exit);
			al_destroy_bitmap(steer);
		}
		
	}
	else
	{
		al_draw_text(font, al_map_rgb(0, 0, 255), screen_w / 2, screen_h / 2, 0, "Something went wrong");
		al_flip_display();
	}
	al_destroy_bitmap(background);
	al_destroy_config(cfg);
	al_destroy_sample(music);
	al_destroy_sample(winner);
	al_destroy_sample(sample);
	al_destroy_sample_instance(music_inst);
	al_destroy_sample_instance(win_inst);
	al_destroy_sample_instance(instance);
	al_destroy_mixer(mixer);
	al_destroy_voice(voice);
	al_destroy_font(font);
	al_destroy_font(font_sm);
	al_destroy_font(font_vsm);
	al_destroy_display(display);
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_uninstall_system();
	return 0;
}