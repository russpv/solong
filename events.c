#include "solong.h"

int	on_keypress(int, void*);
int	on_destroy(void*, int);
int	move_player(char, int, int, t_app*);
static int	_check_valid_move(int, int, t_app *);

int on_keypress(int keycode, void *param)
{
	t_app *app;
   
	app = (t_app *)param;
	if (keycode == ARROW_UP_KEY)
		move_player(P_UP, app->player.row - 1, app->player.col, app);
	else if (keycode == ARROW_DOWN_KEY)
		move_player(P_DOWN, app->player.row + 1, app->player.col, app);
	else if (keycode == ARROW_LEFT_KEY)
		move_player(P_LEFT, app->player.row, app->player.col - 1, app);
	else if (keycode == ARROW_RIGHT_KEY)
		move_player(P_RIGHT, app->player.row, app->player.col + 1, app);
	else if (keycode == ESCAPE)
		on_destroy(param, FAILURE);
	else
		;
	return (0);
}

int on_destroy(void *param, int cond)
{
	t_app *app;
   
	app = (t_app *)param;
	if (cond == SUCCESS)
		ft_printf("YOU WIN!\n");
	cleanup(app);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	_check_valid_move(int row, int col, t_app *app)
{
	const char ch = app->map_grid[row][col]; 
	
	if ((row < 0 || row >= app->height) || (col < 0 || col >= app->width))
		return (FAILURE);
	if (ch == SPACE || ch == LOOT || ch == EXIT)
		return (SUCCESS);
	return (FAILURE);
}

int	move_player(char direction, int newrow, int newcol, t_app *app)
{
	const char tile_dest = app->map_grid[newrow][newcol];
	char * const tile_orig = &app->map_grid[app->player.row][app->player.col];
	
	if (_check_valid_move(newrow, newcol, app) == SUCCESS)
	{
		if (app->player.row == app->exit_pos.row && app->player.col == app->exit_pos.col)
			*tile_orig = EXIT;
		else
			*tile_orig = SPACE;
		app->player.row = newrow;
		app->player.col = newcol;
		if (tile_dest == LOOT)
			app->loots--;
		app->moves++;
	}
	app->map_grid[app->player.row][app->player.col] = direction;
	render_map(app);
	if (tile_dest == EXIT && app->loots == 0)
		on_destroy(app, SUCCESS);
	return (SUCCESS);
}
