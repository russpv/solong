#include "libft/libft.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define SCALE 48
#define TILEW 48
#define TILEH 48
#define SPRITEDIR "assets/"
#define EXTENSION ".ber"
#define RED "\033[91m"
#define DEFAULT "\033[0m"
#define BUFSZ 1024
#define FAILURE -1
#define SUCCESS 0

#define XPM SPRITEDIR "trophy.xpm"
#define WALL_XPM SPRITEDIR "wall_spine.xpm"
#define LOOT_XPM SPRITEDIR "coins.xpm"
#define EXIT_XPM SPRITEDIR "trophy.xpm"
#define SPACE_XPM SPRITEDIR "black_tile.xpm"
#define ENEMY_XPM SPRITEDIR "enemy_green.xpm"

#define NUM_DIRECTIONS 4
#define NUM_FRAMES 3
#define TARGET_FPS 10
#define TARGET_DELAY (1.0 / TARGET_FPS)
#define PLAYER_RIGHT_XPM SPRITEDIR "pecboy_0.xpm"
#define PLAYER_RIGHT_2_XPM SPRITEDIR "pecboy_1.xpm"
#define PLAYER_RIGHT_3_XPM SPRITEDIR "pecboy_2.xpm"
#define PLAYER_LEFT_XPM SPRITEDIR "pecboy_left.xpm"
#define PLAYER_LEFT_2_XPM SPRITEDIR "pecboy_1_left.xpm"
#define PLAYER_LEFT_3_XPM SPRITEDIR "pecboy_2_left.xpm"
#define PLAYER_UP_XPM SPRITEDIR "pecboy_up.xpm"
#define PLAYER_UP_2_XPM SPRITEDIR "pecboy_1_up.xpm"
#define PLAYER_UP_3_XPM SPRITEDIR "pecboy_2_up.xpm"
#define PLAYER_DOWN_XPM SPRITEDIR "pecboy_down.xpm"
#define PLAYER_DOWN_2_XPM SPRITEDIR "pecboy_1_down.xpm"
#define PLAYER_DOWN_3_XPM SPRITEDIR "pecboy_2_down.xpm"
#define ENEMY_FPS 1
#define ENEMY_DELAY (1.0 / ENEMY_FPS)

#define SPACE '0'
#define WALL '1'
#define LOOT 'C'
#define EXIT 'E'
#define START 'P'
#define VISITED 'X'
#define NOTVISI '.'
#define BADGUY 'B'

#define ARROW_UP_KEY 65362  
#define ARROW_DOWN_KEY 65364
#define ARROW_LEFT_KEY 65361
#define ARROW_RIGHT_KEY 65363
#define ESCAPE 65307

#define	P_UP 'U'
#define P_DOWN 'D'
#define P_LEFT 'L'
#define P_RIGHT 'R'

#define STATSX 10
#define STATSY 10

enum e_moves {
	up,
	down,
	left,
	right
};

typedef struct s_img
{
	void	*xpm_ptr;
	int	x;
	int y;
}	t_img;

typedef struct s_pos
{
	int row;
	int col;
}	t_pos;

typedef struct s_app
{
	void *mlx_ptr;
	void *win_ptr;

	char	**map_grid;
	char	**test_map;
	int	width;
	int	height;

	t_img	wall;
	t_img	loot;
	t_img	exit;
	t_img	space;
	t_img	player_right;
	t_img	player_left;
	t_img	player_up;
	t_img	player_down;
	t_img	frames[NUM_DIRECTIONS][NUM_FRAMES];
	t_img	enemy;
	t_pos	player;
	t_pos	exit_pos;
	t_pos	start_pos;
	t_pos	*loots_pos;
	t_pos	enemy_pos;
	clock_t		time;
	clock_t		enemy_timestamp;
	int		frame;
	int		player_facing;
	int		moves;
	int		loots;
	int		loots_size;
	int		exits;
	int		starts;
	int		enemies;
}	t_app;


/* events */
int		on_destroy(void *, int);
int		on_keypress(int, void*);
int		move_enemy(int, int, t_app*);
int		move_player(char, int, int, t_app*);
int		check_valid_move(int, int, t_app*);

/* parse_args */
void	parse_args(int argc, char **argv, t_app *app);

/* init_app */
t_img	new_sprite(void *, char *);
void	init_sprites(t_app *);
void	init_app(t_app *);

/* animation */
int		update_game(void *);
int		init_animation(t_app*);
double	get_time_elapsed(clock_t);

/* check paths */
int		check_paths(t_app*);

/* render_map */
int		render_map(t_app*);
int		render_player(int, t_app*);

/* frees */
void	free_map_grid(char**);
void	cleanup(t_app *);

/* utils */
void	init_struct();
void	err(char*, t_app*);
size_t	arrlen(char **);
int		get_player_direction(t_app*);
int		on_a_loot(t_app*,t_pos);
int		remove_loot(t_app*, int, int);
