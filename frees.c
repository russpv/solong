#include "solong.h"

void	cleanup(t_app *);
void	free_map_grid(char **);

void	_free_sprites(t_app *app)
{
	mlx_destroy_image(app->mlx_ptr, app->wall.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->loot.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->exit.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_right.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_left.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_up.xpm_ptr);
	mlx_destroy_image(app->mlx_ptr, app->player_down.xpm_ptr);
}

void	cleanup(t_app *app)
{
	free_map_grid(app->map_grid);
	free_map_grid(app->test_map);
	_free_sprites(app);
	mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	mlx_destroy_display(app->mlx_ptr);
	free(app->mlx_ptr);
}

void	free_map_grid(char **arr)
{
	char **ptr;

	ptr = arr;
	if (ptr)
	{
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
	}
	free(arr);
}

