#include "solong.h"

t_img	new_sprite(void *, char *);
void	init_sprites(t_app *);
void	init_app(t_app *);
static int	_load_features(t_app *);

static int	_load_features(t_app *app)
{
	int i;
	int j;
	int ch;
	int exits;
	int starts;

	if (!app->map_grid)
		return (FAILURE);
	starts = 0;
	exits = 0;
	i = 0;
	while (app->map_grid[i])
	{
		j = 0;
		while (app->map_grid[i][j])
		{
			ch = app->map_grid[i][j];
			if (LOOT == ch)
				app->loots++;
			if (EXIT == ch)
			{
				app->exit_pos.row = i;
				app->exit_pos.col = j;
				exits++;
			}
			if (START == ch)
			{
				app->player.row = i;
				app->player.col = j;
				starts++;
			}
			j++;
		}
		i++;
	}
	if (exits == 1 && starts == 1 && app->loots > 0)
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
