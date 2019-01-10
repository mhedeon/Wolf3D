#ifndef _WOLF3D_H_
# define _WOLF3D_H_

/////////////////////DEL////
# include <stdio.h>/////////
////////////////////////////


# include "SDL.h"
# include "SDL_image.h"
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
# define WALL_NUM 58
# define SPRITE_NUM 43


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
*	w == wall
*	s == sprite
*	c == collision
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
	int			healh;
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

typedef struct	s_wolf
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	SDL_Texture *tex;
	SDL_PixelFormat format;
	Uint32 *buff;

	const Uint8 *keyboard;

	t_texture wall[WALL_NUM];
	t_texture sprite[SPRITE_NUM];
	SDL_Color color;

	t_stats *hero;
	t_door	door;

	int m_height;
	int m_width;

	t_map *map;

	int pause;

	double start_frame;
	double end_frame;
	double frame;
	double fps;

	double sensitivity;
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
int hbp(t_stats *hero, int s);
void check_item(t_wolf *wolf);
void raycast(t_wolf *wolf);

// /*	rotation.c	*/
// void rotate(t_wolf *wolf);
// void step(t_wolf *wolf, int dir);
// void rot_dir(t_wolf *wolf, double rs);
// void rot_plane(t_wolf *wolf, double rs);
// void strafe(t_wolf *wolf, int dir);

// /*	event.c	*/
// int event(t_wolf *wolf);
// void open_door(t_wolf *wolf);
// void close_door(t_wolf *wolf);

// /* cast.c	*/
// void cast(t_wolf *wolf);
// int		cast_door(t_wolf *wolf);

// /*	draw.c	*/
// void draw(t_wolf *wolf, int x);
// void draw_wall(t_wolf *wolf, int x);
// void draw_floor(t_wolf *wolf, int x);
// void draw_x(t_wolf *wolf);
// void draw_door(t_wolf *wolf, int x);
// void		draw_d(t_wolf *wolf, int x);

/*	init.c	*/
void init(t_wolf *wolf);
int textures(t_wolf *wolf);
int sprites(t_wolf *wolf);
void load_texture(t_wolf *wolf, t_texture *tex, char *path);
void destroy_texture(t_texture *tex);
void close_win(t_wolf *wolf);

/*	other.c	*/
void get_color(t_texture *tex, SDL_Color *color, int x, int y);
void set_pixel(t_wolf *wolf, SDL_Color *color, int x, int y);
void set_pixel_s(t_wolf *wolf, SDL_Color *color, int x, int y);
void clear_buffer(t_wolf *wolf);
void screen_upd(t_wolf *wolf);
int get_cardinal(t_wolf *wolf);

// /*	map.c	*/
// int read_map(t_wolf *wolf, char *path);

// /*	trash.c	*/
// int matrix_height(char **mat);
// void matrix_del(char **m);

// /*	create_map.c	*/
// int check_word(t_map *map, char *word);

// /*	sprite.c	*/
// void draw_sprite(t_wolf *wolf, int x);

// /*	animation.c	*/
// void death_anim(t_wolf *wolf);
// void death(t_wolf *wolf);


#endif
