#include "solong.h"

void	cleanup(t_app *);
void	free_map_grid(char **);

/* Exits if called prior to init_app */
void	_free_sprites(t_app *app)
{
	int	i;
	int	j;

	if (!app->mlx_ptr)
		return ;
	mlx_destroy_image(app->mlx_ptr, app->wall.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->loot.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->exit.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_right.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_left.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_up.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_down.xpm_ptr);
	if (app->enemy.xpm_ptr)
		mlx_destroy_image(app->mlx_ptr, app->enemy.xpm_ptr);
	if (!app->space.xpm_ptr)
		return ;
	mlx_destroy_image(app->mlx_ptr, app->space.xpm_ptr);
	i = -1;
	while (++i < NUM_DIRECTIONS)
	{
		j = -1;
		while (++j < NUM_FRAMES)
			mlx_destroy_image(app->mlx_ptr, app->frames[i][j].xpm_ptr);
	}
}

void	cleanup(t_app *app)
{
	free_map_grid(app->map_grid);
	free_map_grid(app->test_map);
	if (app->loots_pos)
		free(app->loots_pos);
	_free_sprites(app);
	if (app->win_ptr)
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	if (app->mlx_ptr)
	{
		mlx_destroy_display(app->mlx_ptr);
		free(app->mlx_ptr);
	}
}

void	free_map_grid(char **arr)
{
	char	**ptr;

	ptr = arr;
	if (ptr)
	{
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(arr);
	}
}
