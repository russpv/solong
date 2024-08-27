#include "solong.h"

int		render_sprite(t_app*, t_img, int , int);
int		render_map(t_app*);
int		render_player(int, t_app*);
void	get_sprite(t_app *, int, int);

int	render_sprite(t_app *app, t_img sprite, int row, int col)
{
	return (mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, sprite.xpm_ptr, col * SCALE, row * SCALE));
}

void	get_sprite(t_app *app, int col, int row)
{
	const unsigned int code = app->map_grid[row][col];

	if (code == WALL)
		render_sprite(app, app->wall, row, col);
	else if (code == SPACE)
		;
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

int	render_map(t_app *app)
{
	int col;
	int row;

	col = -1;
	mlx_clear_window(app->mlx_ptr, app->win_ptr);
	while (++col < app->height) // traverse rows
	{
		row = -1;
		while (++row < app->width) { //traverse columns
			ft_printf("doing_%dx%d|", row, col);
			get_sprite(app, row, col); }
	}
	return (SUCCESS);
}
/*
int	render_player(int direction, t_app *app)
{
	if (direction == up)
		render_sprite(app, app->player_up, app->player.row, app->player.col);
	else if (direction == down)
		render_sprite(app, app->player_down, app->player.row, app->player.col);
	else if (direction == left)
		render_sprite(app, app->player_left, app->player.row, app->player.col);
	else
		render_sprite(app, app->player_right, app->player.row, app->player.col);
	return (SUCCESS);
}*/
