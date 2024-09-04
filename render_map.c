#include "solong.h"

int		render_sprite(t_app*, t_img, int , int);
int		render_map(t_app*);
int		render_player(int, t_app*);
int		render_stats(t_app*, int, const char *, int);
void	get_sprite(t_app *, int, int);

int	render_sprite(t_app *app, t_img sprite, int row, int col)
{
	return (mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, sprite.xpm_ptr, col * SCALE, row * SCALE));
}

int	render_map(t_app *app)
{
	int col;
	int row;

	col = -1;
	mlx_clear_window(app->mlx_ptr, app->win_ptr);
	while (++col < app->height)
	{
		row = -1;
		while (++row < app->width) {
			get_sprite(app, row, col); }
	}
	if (render_stats(app, app->moves, "Player Moves: ", 0) == FAILURE)
		return (FAILURE);
	if (render_stats(app, app->loots, "Loots: ", 20) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	render_stats(t_app *app, int stat, const char *pre, int adj)
{
	const char *suf = ft_itoa(stat);
	const char *str = ft_strjoin(pre, suf);
	const int rgb = 201 << 16 | 62 << 8 | 62;
	int result;

	free((void *)suf);
	result = mlx_string_put(app->mlx_ptr, app->win_ptr, STATSX + adj, STATSY + adj, rgb, (char *)str);
   	free((void *)str);
	return (result);
}

void	get_sprite(t_app *app, int col, int row)
{
	const unsigned int code = app->map_grid[row][col];

	if (code == WALL)
		render_sprite(app, app->wall, row, col);
	else if (code == SPACE)
		;
	else if (code == BADGUY)
		render_sprite(app, app->enemy, row, col);
	else if (code == LOOT)
		render_sprite(app, app->loot, row, col);
	else if (code == EXIT)
		render_sprite(app, app->exit, row, col);
	else if (code == START && app->moves == 0)
	{
		app->player.row = row;
		app->player.col = col;
		render_sprite(app, app->player_right, app->player.row, app->player.col);
	}
	else if (code == P_RIGHT)
		render_sprite(app, app->player_right, app->player.row, app->player.col);
	else if (code == P_LEFT)
		render_sprite(app, app->player_left, app->player.row, app->player.col);
	else if (code == P_UP)
		render_sprite(app, app->player_up, app->player.row, app->player.col);
	else if (code == P_DOWN)
		render_sprite(app, app->player_down, app->player.row, app->player.col);
}

