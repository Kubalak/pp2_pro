#include "menu.h"

void change_set(ALLEGRO_FONT** font, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h)
{
	int status = 0, edit = 0, dif_state = 0, exit = 0, speed = 1, res_state = 0;
	char write[20];
	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	struct resolution res[] =
	{
		{1024,600}, {1024,768}, {1280,720}, {1280,800}, {1280,1024},
		{1366,768}, {1400,1050}, {1440,900}, {1600,900},  {1600,1024},
		{1680,1050},{1600,1200},{1920,1080},{1920,1200},{2048,1152},
		{2048,1536}, {2560,1080}, {2560,1440}, {2560,1600},	{2560,2048}, {monitor.x2,monitor.y2} 
	};
	do {
		if (res[res_state].x == *screen_w && res[res_state].y == *screen_h)break;
		res_state++;
	} while (res_state < 19);
	bool fullscreen = 0;
	bool pressed_down = false, pressed_up = false, pressed_right = false, pressed_left = false, back = false, enter = true;
	ALLEGRO_COLOR colour = al_map_rgb(39, 255, 0);
	ALLEGRO_COLOR colour_2 = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR edited = al_map_rgb(128, 0, 0);
	ALLEGRO_BITMAP* go_back = al_load_bitmap("textures/back.png");
	dif_state = atoi(al_get_config_value(cfg, "Difficulty", "Lvl"));
	if (atoi(al_get_config_value(cfg, "Fullscreen", "Value")))fullscreen = true;
	else fullscreen = false;
	speed = atoi(al_get_config_value(cfg, "Speed", "Value"));
	do
	{
		al_get_keyboard_state(state);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, *screen_w, *screen_h, 0);
		al_draw_scaled_bitmap(go_back, 0, 0, al_get_bitmap_width(go_back), al_get_bitmap_height(go_back), 0.05 * (*screen_w), 0.05 * (*screen_h), 0.1 * (*screen_w), 0.05 * (float)(*screen_w) / (*screen_h) * (*screen_h), 0);
		al_draw_text(*font, status == 0 ? (edit != 0 ? edited : colour_2) : colour, ((*screen_w) - al_get_text_width(*font, "Difficulty")) / 2, 0.18 * (*screen_h), 0, "Difficulty");
		if (dif_state == 0)al_draw_text(*font, (status == 0 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Easy")) / 2, 0.25 * (*screen_h), 0, "Easy");
		else if (dif_state == 1)al_draw_text(*font, (status == 0 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Normal")) / 2, 0.25 * (*screen_h), 0, "Normal");
		else al_draw_text(*font, (status == 0 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Hard")) / 2, 0.25 * (*screen_h), 0, "Hard");
		if (al_key_down(state, ALLEGRO_KEY_ENTER) && !enter)
		{
			edit = status + 1;
		}
		if (al_key_down(state, ALLEGRO_KEY_RIGHT))
		{
			if (!pressed_right)
			{
				if (edit == 1)
				{
					dif_state++;
					dif_state %= 3;
				}
				else if (edit == 2)
				{
					fullscreen ^= 1;
				}
				else if (edit == 3)
				{
					if (res_state < 20)res_state++;
					else res_state = 0;
				}
				else if (edit == 4)
				{
					if (speed < 2)speed++;
					else speed = 0;
				}
				pressed_right = true;
			}
		}
		else pressed_right = false;
		if (al_key_down(state, ALLEGRO_KEY_LEFT))
		{
			if (!pressed_left)
			{
				if (edit == 1)
				{
					if (dif_state)dif_state--;
					else dif_state = 2;
				}
				else if (edit == 2)
				{
					fullscreen ^= 1;
				}
				else if (edit == 3)
				{
					if (res_state > 0)res_state--;
					else res_state = 20;
				}
				else if (edit == 4)
				{
					if (speed > 0)speed--;
					else speed = 2;
				}
				pressed_left = true;
			}
		}
		else pressed_left = false;

		al_draw_text(*font, status == 1 ? (edit != 0 ? edited : colour_2) : colour, ((*screen_w) - al_get_text_width(*font, "Fullscreen")) / 2, 0.38 * (*screen_h), 0, "Fullscreen");
		if (!fullscreen)al_draw_text(*font, (status == 1 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "NO")) / 2, 0.45 * (*screen_h), 0, "NO");
		else  al_draw_text(*font, (status == 1 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "YES")) / 2, 0.45 * (*screen_h), 0, "YES");
		al_draw_text(*font, status == 2 ? (edit != 0 ? edited : colour_2) : colour, ((*screen_w) - al_get_text_width(*font, "Resolution")) / 2, 0.58 * (*screen_h), 0, "Resolution");
		al_draw_textf(*font, (status == 2 && edit == 3) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "2560x2048")) / 2, 0.65 * (*screen_h), 0, "%d x %d", res[res_state].x, res[res_state].y);
		al_draw_text(*font, status == 3 ? (edit != 0 ? edited : colour_2) : colour, ((*screen_w) - al_get_text_width(*font, "Movement speed")) / 2, 0.78 * (*screen_h), 0, "Movement speed");
		if (speed == 0)al_draw_text(*font, (status == 3 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Slow")) / 2, 0.85 * (*screen_h), 0, "Slow");
		else if (speed == 1)al_draw_text(*font, (status == 3 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Normal")) / 2, 0.85 * (*screen_h), 0, "Normal");
		else al_draw_text(*font, (status == 3 && edit) ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Fast")) / 2, 0.85 * (*screen_h), 0, "Fast");

		if (al_key_down(state, ALLEGRO_KEY_DOWN) && !edit)
		{
			if (!pressed_down)
			{
				status++;
				status %= 4;
				pressed_down = true;
			}
		}
		else pressed_down = false;
		if (al_key_down(state, ALLEGRO_KEY_UP) && !edit)
		{
			if (!pressed_up)
			{

				if (status <= 0)status = 3;
				else status--;
				pressed_up = true;
			}
		}
		else pressed_up = false;
		if (al_key_down(state, ALLEGRO_KEY_ESCAPE))
		{
			snprintf(write, 19, "%d", dif_state);
			al_set_config_value(cfg, "Difficulty", "Lvl", write);
			snprintf(write, 19, "%d", speed);
			al_set_config_value(cfg, "Speed", "Value", write);
			snprintf(write, 19, "%d", fullscreen);
			al_set_config_value(cfg, "Fullscreen", "Value", write);
			snprintf(write, 19, "%d", res[res_state].x);
			al_set_config_value(cfg, "Resolution", "Width", write);
			snprintf(write, 19, "%d", res[res_state].y);
			al_set_config_value(cfg, "Resolution", "Height", write);
			al_save_config_file("data/options.ini", cfg);
			if (edit == 2 || edit == 3)
			{
				al_destroy_font(*font);
				if (fullscreen)
				{
					al_resize_display(display, res[res_state].x, res[res_state].y);
					al_set_display_flag(display, ALLEGRO_FULLSCREEN, false);
					al_set_display_flag(display, ALLEGRO_MAXIMIZED, false);
					al_set_display_flag(display, ALLEGRO_FULLSCREEN, true);
					al_set_display_flag(display, ALLEGRO_MAXIMIZED, true);
					
				}
				else
				{
					al_set_display_flag(display, ALLEGRO_FULLSCREEN, false);
					al_set_display_flag(display, ALLEGRO_MAXIMIZED, false);
					al_resize_display(display, res[res_state].x, res[res_state].y);
					al_set_window_position(display, ((monitor.x2 - res[res_state].x) / 2) >= 0 ? (monitor.x2 - res[res_state].x) / 2 : 0, ((monitor.y2 - res[res_state].y) / 2) >= 0 ? ((monitor.y2 - res[res_state].y) / 2) : 0);
				}
				*screen_w = res[res_state].x;
				*screen_h = res[res_state].y;
				*font = al_load_ttf_font("fonts/INVADERS.ttf", 0.0375 * (*screen_w), 0);
			}
			if (edit)
			{
				back = true;
			}
			edit = 0;
			if (!edit && !back)break;
		}
		else back = false;
		if (al_key_down(state, ALLEGRO_KEY_ENTER))
			enter = true;
		else enter = false;
		al_rest(0.01);
		al_flip_display();
	} while (1);
	al_destroy_bitmap(go_back);

}

int menu(ALLEGRO_CONFIG* cfg, ALLEGRO_DISPLAY* display, ALLEGRO_KEYBOARD_STATE* state, ALLEGRO_FONT** font, ALLEGRO_FONT** font_sm, ALLEGRO_BITMAP* background, unsigned int* screen_w, unsigned int* screen_h)
{
	int status = 0;
	bool pressed_down = false, pressed_up = false;
	ALLEGRO_COLOR colour = al_map_rgb(39, 255, 0);
	ALLEGRO_COLOR colour_2 = al_map_rgb(255, 0, 0);

	do
	{
		al_get_keyboard_state(state);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, *screen_w, *screen_h, 0);
		al_draw_text(*font, status == 0 ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Play")) / 2, 0.18 * (*screen_h), 0, "Play");
		al_draw_text(*font, status == 1 ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Options")) / 2, 0.38 * (*screen_h), 0, "Options");
		al_draw_text(*font, status == 2 ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Hi-scores")) / 2, 0.58 * (*screen_h), 0, "Hi-scores");
		al_draw_text(*font, status == 3 ? colour_2 : colour, ((*screen_w) - al_get_text_width(*font, "Exit")) / 2, 0.78 * (*screen_h), 0, "Exit");
		if (al_key_down(state, ALLEGRO_KEY_DOWN))
		{
			if (!pressed_down)
			{
				status++;
				status %= 4;
				pressed_down = true;
			}
		}
		else pressed_down = false;
		if (al_key_down(state, ALLEGRO_KEY_UP))
		{
			if (!pressed_up)
			{
				if (status > 0)status--;
				else status = 3;

				pressed_up = true;
			}
		}
		else pressed_up = false;
		if (al_key_down(state, ALLEGRO_KEY_ENTER) && status == 1) change_set(font, state, cfg, display, background, screen_w, screen_h);
		if (al_key_down(state, ALLEGRO_KEY_ENTER) && status == 2)
		{
			struct hi_score* score = NULL;
			load_data(&score, atoi(al_get_config_value(cfg, "Difficulty", "Lvl")));
			sort(&score);
			print_hi_score(*font_sm, background, score, NULL, *screen_w, *screen_h);
			delete_all(&score);
		}
		al_flip_display();
	} while (!al_key_down(state, ALLEGRO_KEY_ENTER) || (status != 3 && status != 0));
	return status;
}