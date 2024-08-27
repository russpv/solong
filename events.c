#include "solong.h"

int	on_keypress(int, void*);
int	on_destroy(void*);
int	move_player(char, int, int, t_app*);

int on_keypress(int keycode, void *param)
{
	t_app *app = (t_app *)param;
	if (keycode == ARROW_UP_KEY)
		move_player(P_UP, app->player.row - 1, app->player.col, app);
	else if (keycode == ARROW_DOWN_KEY)
		move_player(P_DOWN, app->player.row + 1, app->player.col, app);
	else if (keycode == ARROW_LEFT_KEY)
		move_player(P_LEFT, app->player.row, app->player.col - 1, app);
	else if (keycode == ARROW_RIGHT_KEY)
		move_player(P_RIGHT, app->player.row, app->player.col + 1, app);
	else if (keycode == ESCAPE)
		on_destroy(param);
	else
		printf("Pressed key: %d\\n", keycode);
	fflush(stdout);
	return (0);
}

int on_destroy(void *param)
{
	t_app *app = (t_app *)param;
	mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	mlx_destroy_display(app->mlx_ptr);
	cleanup(app);
	// TODO call proper cleanup function
	exit(EXIT_SUCCESS);
	return (0);
}

int	check_valid_move(int row, int col, t_app *app)
{
	const char ch = app->map_grid[row][col]; 
	if ((row < 0 || row >= app->height) || (col < 0 || col >= app->width))
		return (1);
	if (ch == SPACE || ch == LOOT || ch == EXIT)
		return (0);
	return (1);
}

/* Checks for valid move */
int	move_player(char direction, int newrow, int newcol, t_app *app)
{
	const char ch = app->map_grid[newrow][newcol];

	app->map_grid[app->player.row][app->player.col] = SPACE;
	if (check_valid_move(newrow, newcol, app) == 0)
	{
		app->player.row = newrow;
		app->player.col = newcol;
	}
	app->map_grid[app->player.row][app->player.col] = direction;
	render_map(app);
	if (ch == EXIT)
		on_destroy(app);
	return (SUCCESS);
}
