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
#define RED "\033[91m"
#define DEFAULT "\033[0m"
#define BUFSZ 1024
#define FAILURE -1
#define SUCCESS 0

#define XPM SPRITEDIR "trophy.xpm"
#define WALL_XPM SPRITEDIR "wall_spine.xpm"
#define LOOT_XPM SPRITEDIR "coins.xpm"
#define EXIT_XPM SPRITEDIR "trophy.xpm"

#define PLAYER_RIGHT_XPM SPRITEDIR "pecboy_0.xpm"
#define PLAYER_LEFT_XPM SPRITEDIR "pecboy_left.xpm"
#define PLAYER_UP_XPM SPRITEDIR "pecboy_up.xpm"
#define PLAYER_DOWN_XPM SPRITEDIR "pecboy_down.xpm"

#define SPACE '0'
#define WALL '1'
#define LOOT 'C'
#define EXIT 'E'
#define START 'P'

#define ARROW_UP_KEY 65362  
#define ARROW_DOWN_KEY 65364
#define ARROW_LEFT_KEY 65361
#define ARROW_RIGHT_KEY 65363
#define ESCAPE 65307

#define	P_UP 'U'
#define P_DOWN 'D'
#define P_LEFT 'L'
#define P_RIGHT 'R'

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
	void *img_ptr;

	char	**map_grid;
	int	width;
	int	height;

	t_img	wall;
	t_img	loot;
	t_img	exit;
	t_img	player_right;
	t_img	player_left;
	t_img	player_up;
	t_img	player_down;
	t_pos	player;
	int		moves;
}	t_app;


/* events */
int		on_destroy(void *);
int		on_keypress(int, void*);

/* parse_args */
void	parse_args(int argc, char **argv, t_app *app);
int		get_line(int fd, char **buf);

/* init_app */
t_img	new_sprite(void *, char *);
void	init_sprites(t_app *);
void	init_app(t_app *);

/* render_map */
int		render_map(t_app*);
int		render_player(int, t_app*);
void	scale_sprite();

/* frees */
void	free_map_grid(t_app *app);

/* utils */
void	init_struct();
void	err(char*, t_app*);
void	print_map(t_app*);
size_t	arrlen(char **);
