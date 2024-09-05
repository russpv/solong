#include "solong.h"

void	print_map(t_app *);

void	err(char *msg, t_app *app);
size_t	arrlen(char **);
void	init_struct(t_app *);
int		get_player_direction(t_app *);
int		on_a_loot(t_app *, t_pos);
int		remove_loot(t_app *, int, int);

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

/* Test function TODO delete */
void	print_map(t_app *app)
{
	const char	**ptr = (const char **)app->map_grid;

	if (!ptr)
		return ;
	if (!*ptr)
		return ;
	while (*ptr)
		ft_printf("%s\n", *ptr++);
}

void	err(char *msg, t_app *app)
{
	errno = EINVAL;
	perror(msg);
	cleanup(app);
	exit(1);
}

void	init_struct(t_app *app)
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
	app->player_facing = right;
}

int	get_player_direction(t_app *app)
{
	if (P_UP == app->map_grid[app->player.row][app->player.col])
		return (up);
	if (P_DOWN == app->map_grid[app->player.row][app->player.col])
		return (down);
	if (P_LEFT == app->map_grid[app->player.row][app->player.col])
		return (left);
	if (P_RIGHT == app->map_grid[app->player.row][app->player.col])
		return (right);
	return (-1);
}

int	on_a_loot(t_app *app, t_pos pos)
{
	int	i;

	i = -1;
	while (++i < app->loots)
		if (pos.row == app->loots_pos[i].row
			&& pos.col == app->loots_pos[i].col)
			return (SUCCESS);
	return (FAILURE);
}

/* Replaces valid loot position with out-of-bounds position and decrements counter */
int	remove_loot(t_app *app, int row, int col)
{
	int	i;

	i = -1;
	while (++i < app->loots_size)
	{
		if (row == app->loots_pos[i].row && col == app->loots_pos[i].col)
		{
			app->loots_pos[i].row = -1;
			app->loots_pos[i].col = -1;
			app->loots--;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
