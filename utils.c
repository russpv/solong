#include "solong.h"

void			err(char *a, t_app *b, int c, char *d);
size_t			arrlen(char **a);
static void		_init_struct_secondaries(t_app *a);
void			init_struct(t_app *a);
void			update_player_direction(t_app *a, char b);

size_t	arrlen(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

/* fd and new are optional args */
void	err(char *msg, t_app *app, int fd, char *new)
{
	errno = EINVAL;
	perror(msg);
	cleanup(app);
	if (fd >= 0)
		close(fd);
	if (new)
		free(new);
	exit(1);
}

static void	_init_struct_secondaries(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	while (++i < NUM_DIRECTIONS)
	{
		j = -1;
		while (++j < NUM_FRAMES)
			app->frames[i][j].xpm_ptr = NULL;
	}
	app->space.xpm_ptr = NULL;
}

void	init_struct(t_app *app)
{
	app->mlx_ptr = NULL;
	app->win_ptr = NULL;
	app->map_grid = NULL;
	app->width = 0;
	app->height = 0;
	app->moves = 0;
	app->loots = 0;
	app->loots_size = 0;
	app->enemies = 0;
	app->frame = 0;
	app->exits = 0;
	app->starts = 0;
	app->player_facing = right;
	app->loots_pos = NULL;
	app->test_map = NULL;
	_init_struct_secondaries(app);
}

void	update_player_direction(t_app *app, char direction)
{
	app->map_grid[app->player.row][app->player.col] = direction;
	if (P_UP == app->map_grid[app->player.row][app->player.col])
		app->player_facing = up;
	if (P_DOWN == app->map_grid[app->player.row][app->player.col])
		app->player_facing = down;
	if (P_LEFT == app->map_grid[app->player.row][app->player.col])
		app->player_facing = left;
	if (P_RIGHT == app->map_grid[app->player.row][app->player.col])
		app->player_facing = right;
}
