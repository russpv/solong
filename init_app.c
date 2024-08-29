#include "solong.h"

t_img	new_sprite(void*, char*);
void	init_sprites(t_app*);
void	init_app(t_app*);

static int	_load_features(t_app*);
static void _store_pos(t_pos*, int, int, int*);
static void _store_loot_pos(t_app*, int, int, int*);

/* realloc position array of structs */
static void	_store_loot_pos(t_app *app, int row, int col, int *loots)
{
	t_pos *ptr;
	int i;

	(*loots)++;
	ptr = malloc(sizeof(t_pos) * (*loots));
	if (!ptr)
		err("Malloc error", app);
	i = -1;
	while (++i < *loots - 1)
		ft_memcpy(&ptr[i], &app->loots_pos[i], sizeof(t_pos));
	ptr[*loots - 1].row = row;
	ptr[*loots - 1].col = col;
	free(app->loots_pos);
	app->loots_pos = ptr;
}

static void	_store_pos(t_pos *pos, int row, int col, int *counter)
{
	pos->row = row;
	pos->col = col;
	(*counter)++;
}

static int	_load_features(t_app *app)
{
	int i;
	int j;
	int ch;

	if (!app->map_grid)
		return (FAILURE);
	i = 0;
	while (app->map_grid[i])
	{
		j = 0;
		while (app->map_grid[i][j])
		{
			ch = app->map_grid[i][j];
			if (LOOT == ch)
				_store_loot_pos(app, i, j, &app->loots);
			if (EXIT == ch)
				_store_pos(&app->exit_pos, i, j, &app->exits);
			if (START == ch)
				_store_pos(&app->player, i, j, &app->starts);
			j++;
		}
		i++;
	}
	if (app->exits == 1 && app->starts == 1 && app->loots > 0)
		return (SUCCESS);
	return (FAILURE);
}

t_img	new_sprite(void *ptr, char *filename)
{
	t_img img;

	img.xpm_ptr = mlx_xpm_file_to_image(ptr, filename, &img.x, &img.y);
	return (img);
}

/* Create all sprites */
void	init_sprites(t_app *app)
{
	void *ptr;

	ptr = app->mlx_ptr;
	app->wall = new_sprite(ptr, WALL_XPM);
	app->loot = new_sprite(ptr, LOOT_XPM);
	app->exit = new_sprite(ptr, EXIT_XPM);
	app->player_right = new_sprite(ptr, PLAYER_RIGHT_XPM);
	app->player_left = new_sprite(ptr, PLAYER_LEFT_XPM);
	app->player_up = new_sprite(ptr, PLAYER_UP_XPM);
	app->player_down = new_sprite(ptr, PLAYER_DOWN_XPM);
}

/* Create the game pointer */
void	init_app(t_app *app)
{
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		err("mlx_init() fail", app);
	init_sprites(app);
	if (_load_features(app) == FAILURE)
		err("Invalid map", app);
}
