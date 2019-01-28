#ifndef _WOLF3D_H_
# define _WOLF3D_H_

/////////////////////DEL////
# include <stdio.h>/////////
////////////////////////////
# include <errno.h> // ??????????


# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>

# define WINDOW_WIDTH 1100
# define WINDOW_HEIGHT 600
# define SCREEN_WIDTH 1100
# define SCREEN_HEIGHT 800

# define TEXTURES 10
# define THREADS 8
# define WALL_NUM 59
# define SPRITE_NUM 46
# define WEAPON_NUM 5

/*
* keydown
*/
# define KEY e.type == SDL_KEYDOWN && e.key.keysym.sym

/* for death anim? */
# define X_BOOST SCREEN_WIDTH / 300
# define Y_BOOST SCREEN_HEIGHT / 200
# define SQUARE ((SCREEN_HEIGHT * SCREEN_WIDTH) >> 16)

# define SPRITE_WIDTH (wolf->sprite[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].sprite].sur->w)
# define SPRITE_HEIGHT (wolf->sprite[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].sprite].sur->h)
# define CURRENT_SPRITE (wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].sprite)
# define WALL_WIDTH (wolf->wall[get_cardinal(wolf)].sur->w)
# define WALL_HEIGHT (wolf->wall[get_cardinal(wolf)].sur->h)
# define FLOOR_WIDTH (wolf->wall[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].floor].sur->w)
# define FLOOR_HEIGHT (wolf->wall[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].floor].sur->h)
# define CURRENT_FLOOR (wolf->map[(int)f1_y * wolf->m_width + (int)f1_x].floor)
# define CEIL_WIDTH (wolf->wall[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].ceil].sur->w)
# define CEIL_HEIGHT (wolf->wall[wolf->map[wolf->m_y * wolf->m_width + wolf->m_x].ceil].sur->h)
# define CURRENT_CEIL (wolf->map[(int)f1_y * wolf->m_width + (int)f1_x].ceil)

/*
* from radians to degrees
*/
# define RAD(a) ((double)a * M_PI / 180.0)

/*
* direction
*/
# define GO_FORWARD 1
# define GO_BACK -1
# define STRAFE_LEFT -1
# define STRAFE_RIGHT 1

/*
* cardinal directions
*/
# define NORTH 1
# define SOUTH 3
# define WEST 0
# define EAST 2

/*
* SDL_Rect for cursor
*/
# define NEW_GAME  420, 360, menu->cursor.sur->w, menu->cursor.sur->h
# define SELECT_LEVEL 420, 428, menu->cursor.sur->w, menu->cursor.sur->h
# define CONTROLS 420, 545, menu->cursor.sur->w, menu->cursor.sur->h
# define EXIT 420, 625, menu->cursor.sur->w, menu->cursor.sur->h
# define LEVEL_1 420, 360, menu->cursor.sur->w, menu->cursor.sur->h
# define LEVEL_2 420, 421, menu->cursor.sur->w, menu->cursor.sur->h
# define LEVEL_3 420, 483, menu->cursor.sur->w, menu->cursor.sur->h
# define LEVEL_4 420, 545, menu->cursor.sur->w, menu->cursor.sur->h
# define BACK 420, 625, menu->cursor.sur->w, menu->cursor.sur->h

/*
* errors
*/
# define MAP_FILE 1
# define MAP 2
# define POSITION_ERR 3
# define SDL_INIT_ERR 4
# define WALL_ERR 5
# define SPRITE_ERR 6
# define PISTOL_ERR 7
# define KNIFE_ERR 8
# define WIN_ERR 9
# define REN_ERR 10
# define TEX_ERR 11
# define FONT_ERR 12
# define BUFF_ERR 13
# define HERO_ERR 14
# define FACE_ERR 15
# define WOLF_ERR 16

/*
* lvl
*/
# define LVL1 1
# define LVL2 2
# define LVL3 3
# define LVL4 4
# define BONUS1 5

/*
*	w == wall
*	s == sprite
*	c == collision
*	d == door
*/
typedef struct	s_map
{
	int			w;
	int			s;
	int			c;
	int			d;
	int			north;
	int			south;
	int			west;
	int			east;
	int			sprite;
	int			floor;
	int			ceil;
}				t_map;

typedef struct	s_texture
{
	SDL_Surface *sur;
	Uint32 *pixels;
}				t_texture;

typedef struct	s_stats
{
	int			health;
	int			score;
	int			bullet;
}				t_stats;

typedef struct	s_door
{
	int opened;
	int x;
	int y;
	double *p_x;
	double *p_y;
}				t_door;

typedef struct	s_menu
{
	t_texture	menu[2];
	t_texture	level[2];
	t_texture	start[3];
	t_texture	cursor;
	Mix_Music	*music;
	Mix_Chunk	*toggle;
	Mix_Chunk	*select;
	Mix_Chunk	*achtung;
}				t_menu;

typedef struct	s_wolf
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	SDL_Texture *tex;
	SDL_PixelFormat format;
	Uint32 *buff;
	t_texture icon;
	TTF_Font *font;

	const Uint8 *keyboard;

	Mix_Music *lvl_music;
	int volume;
	t_menu	menu;
	Mix_Chunk *chunk[9];
	t_texture wall[WALL_NUM];
	t_texture sprite[SPRITE_NUM];
	t_texture pistol[WEAPON_NUM];
	t_texture knife[WEAPON_NUM];
	t_texture face[80];
	SDL_Color color;

	t_stats *hero;
	t_door	door;

	int m_height;
	int m_width;

	t_map *map;

	int pause;
	int weapon;
	int shot;
	Mix_Chunk *left_click;
	double sens;

	double start_frame;
	double end_frame;
	double frame;
	double fps;

	double p_x;
	double p_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double ray_dir_x;
	double ray_dir_y;
	double cam_x;
	double side_x;
	double side_y;
	double d_x;
	double d_y;
	double dist;
	double ms;
	double rs;
	double w_x;
	double f_x;
	double f_y;
	double w;



	int sp_start;
	int sp_end;
	double inv;
	double sp_x;
	double sp_y;
	double spt_x;
	double spt_y;
	int ssx;
	int sp_h;

	int m_x;
	int m_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int draw_h;
	int draw_start;
	int draw_end;
	int t_x;
	int t_y;
	int fc_x;
	int fc_y;
	int d;

	int old_mouse_x;
	int new_mouse_x;
	int mouse_y;

	int start;
	int end;

}				t_wolf;
/*	main.c	*/
int hbp(t_wolf *wolf, t_stats *hero, int s);

/*	rotation.c	*/
void rotate(t_wolf *wolf);
void step(t_wolf *wolf, int dir);
void rot_dir(t_wolf *wolf, double rs);
void rot_plane(t_wolf *wolf, double rs);
void strafe(t_wolf *wolf, int dir);

/*	event.c	*/
int event(t_wolf *wolf, int (*end)(t_wolf *wolf));
void open_door(t_wolf *wolf);
void close_door(t_wolf *wolf);
void changes(t_wolf *wolf, SDL_Event e);


/* cast.c	*/
void cast(t_wolf *wolf);
int		cast_door(t_wolf *wolf);
int			cast_enemy(t_wolf *wolf);

/*	draw.c	*/
void draw(t_wolf *wolf, int x);
void draw_wall(t_wolf *wolf, int x);
void draw_floor(t_wolf *wolf, int x);
void draw_x(t_wolf *wolf);
void draw_door(t_wolf *wolf, int x);
void		draw_d(t_wolf *wolf, int x);

/*	init.c	*/
int pre_init(t_wolf *wolf);
void free_garbage_1(t_wolf *wolf);
void post_init(t_wolf *wolf);
int load_face(t_texture *face);
int free_face(t_texture *face);
void prepare_face(t_texture *face);

/*	other.c	*/
void get_color(t_texture *tex, SDL_Color *color, int x, int y);
void set_pixel(t_wolf *wolf, SDL_Color *color, int x, int y);
void set_pixel_s(t_wolf *wolf, SDL_Color *color, int x, int y);
void clear_buffer(t_wolf *wolf);
// void	clear_buffer(t_wolf *wolf, SDL_Color *c);
void screen_upd(t_wolf *wolf);
int get_cardinal(t_wolf *wolf);

/*	sprite.c	*/
void draw_sprite(t_wolf *wolf, int x);

// /*	animation.c	*/
// void death_anim(t_wolf *wolf);
// void death(t_wolf *wolf);

/*	menu.c	*/
void menu_anim(t_wolf *wolf, t_texture *menu, Uint32 new_time);
int menu_event(t_wolf *wolf, t_menu *menu, int *m, SDL_Event e);
void draw_cursor_in_menu(t_wolf *wolf, t_menu *menu, int m, char m_or_l);
int m_menu(t_wolf *wolf, t_menu *menu);

/*	menu_lvl.c	*/
int show_controls(void);
int level_event(t_wolf *wolf, t_menu *menu, int *m, SDL_Event e);
int level(t_wolf *wolf, t_menu *menu);
void	draw_cursor(t_wolf *wolf, t_texture *tex, SDL_Rect *rect);

/*	menu_resource.c	*/
int		free_menu_screen(t_menu *menu);
int		init_menu_screen(t_menu *menu);
int		init_menu_sound(t_menu *menu);
int		free_menu_sound(t_menu *menu);
int		start_menu(t_wolf *wolf, t_menu *menu);

/*	intro.c	*/
void	cp_tex_to_buff(t_wolf *wolf, t_texture *tex);
void	intro_anim(t_wolf *wolf, t_texture *intro);
void	intro(t_wolf *wolf);

/*	texture.c	*/
int free_textures(t_texture *texture, int num);
int textures(t_texture *texture, int num, char *p);
int load_texture(t_texture *tex, char *path);
void destroy_texture(t_texture *tex);

/*	map.c	*/
int map(t_wolf *wolf, char *path);

/*	map_check.c	*/
int check_word(t_map *map, char *word);

/*	map_trash.c	*/
int matrix_height(char **mat);
void matrix_del(char **m);
int get_number(char a, char b);
int		check_digit(char *word);
int	check_player_xy(t_wolf *wolf);

/*	loading.c	*/
void	loading(t_wolf *wolf, int persent);

/*	face.c	*/
void			face(t_wolf *wolf);

/*	hud.c	*/
void			draw_hud(t_wolf *wolf);

/*	lvl1.c	*/
void start_lvl_1(t_wolf *wolf);

/*	lvl2.c	*/
int end_lvl2(t_wolf *wolf);
void start_lvl_2(t_wolf *wolf);

/*	death.c	*/
int death(t_wolf *wolf);

/*	get_error.c	*/
int get_error(int error);

/*	fight	*/
void weapon(t_wolf *wolf);

/*	game.c	*/
void check_item(t_wolf *wolf);
void cast_loop(t_wolf *wolf);
void fps(t_wolf *wolf);
int		pause_frame(t_wolf *wolf, Uint32 pause);

#endif
