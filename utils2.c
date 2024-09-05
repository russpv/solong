#include "solong.h"

t_img		new_sprite(void *a, char *b);
int			on_a_loot(t_app *a, t_pos b);
int			remove_loot(t_app *a, int b, int c);
void		init_sprites(t_app *a);
int			check_map_walled(t_app*a);

t_img	new_sprite(void *ptr, char *filename)
{
	t_img	img;

	img.xpm_ptr = mlx_xpm_file_to_image(ptr, filename, &img.x, &img.y);
	return (img);
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

/* Replaces valid loot position with out-of-bounds position 
 * and decrements counter */
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

/* Create all sprites */
void	init_sprites(t_app *app)
{
	void	*ptr;

	ptr = app->mlx_ptr;
	app->wall = new_sprite(ptr, WALL_XPM);
	app->loot = new_sprite(ptr, LOOT_XPM);
	app->exit = new_sprite(ptr, EXIT_XPM);
	app->enemy = new_sprite(ptr, ENEMY_XPM);
	app->player_right = new_sprite(ptr, PLAYER_RIGHT_XPM);
	app->player_left = new_sprite(ptr, PLAYER_LEFT_XPM);
	app->player_up = new_sprite(ptr, PLAYER_UP_XPM);
	app->player_down = new_sprite(ptr, PLAYER_DOWN_XPM);
}

/* Ensures contiguous wall map border */
int	check_map_walled(t_app *app)
{
	int i;

	i = -1;
	while (++i < app->width)
		if (WALL != app->map_grid[0][i])
			return (FAILURE);
	i = -1;
	while (++i < app->height)
		if (WALL != app->map_grid[i][0])
			return (FAILURE);
	i = -1;
	while (++i < app->width)
		if (WALL != app->map_grid[app->height - 1][i])
			return (FAILURE);
	i = -1;
	while (++i < app->height)
		if (WALL != app->map_grid[i][app->width - 1])
			return (FAILURE);
	return (SUCCESS);
}
