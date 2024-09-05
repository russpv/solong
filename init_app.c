#include "solong.h"

void		init_app(t_app *a);
static int	_load_map_features(t_app *a);
static void	_do_loop_ops(t_app *a, char b, int c, int d);
static void	_store_pos(t_pos *a, int b, int c, int *d);
static void	_store_loot_pos(t_app *a, int b, int c, int *d);

/* realloc loot entity positions stored as array of structs */
static void	_store_loot_pos(t_app *app, int row, int col, int *loots)
{
	t_pos	*ptr;
	int		i;

	(*loots)++;
	app->loots_size++;
	ptr = malloc(sizeof(t_pos) * (*loots));
	if (!ptr)
		err("Malloc error", app, -1, NULL);
	i = -1;
	if (*loots > 1)
		while (++i < *loots - 1)
			ft_memcpy(&ptr[i], &app->loots_pos[i], sizeof(t_pos));
	ptr[*loots - 1].row = row;
	ptr[*loots - 1].col = col;
	if (app->loots_pos)
		free(app->loots_pos);
	app->loots_pos = ptr;
}

static void	_store_pos(t_pos *pos, int row, int col, int *counter)
{
	pos->row = row;
	pos->col = col;
	(*counter)++;
}

static void	_do_loop_ops(t_app *app, char ch, int i, int j)
{
	if (LOOT == ch)
		_store_loot_pos(app, i, j, &app->loots);
	else if (EXIT == ch)
		_store_pos(&app->exit_pos, i, j, &app->exits);
	else if (START == ch)
		_store_pos(&app->player, i, j, &app->starts);
	else if (BADGUY == ch)
		_store_pos(&app->enemy_pos, i, j, &app->enemies);
	else if (!(SPACE == ch || WALL == ch))
		err(RED "Invalid map character found" DEFAULT, app, -1, NULL);
}

/* Ensures required map features are present and sets counters */
static int	_load_map_features(t_app *app)
{
	int	i;
	int	j;

	if (!app->map_grid)
		return (FAILURE);
	i = -1;
	while (app->map_grid[++i])
	{
		j = -1;
		while (app->map_grid[i][++j])
			_do_loop_ops(app, app->map_grid[i][j], i, j);
	}
	if (app->exits == 1 && app->starts == 1 && app->loots > 0
		&& app->enemies <= 1)
		return (SUCCESS);
	return (FAILURE);
}

/* Create the game pointer */
void	init_app(t_app *app)
{
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		err(RED "mlx_init() failed" DEFAULT, app, -1, NULL);
	init_sprites(app);
	if (_load_map_features(app) == FAILURE)
		err(RED "Invalid map" DEFAULT, app, -1, NULL);
}
