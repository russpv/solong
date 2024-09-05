#include "solong.h"

int	on_keypress(int a, void *b);
int	on_destroy(void *a, int b);
int	move_player(char a, int b, int c, t_app *d);
int	move_enemy(int a, int b, t_app *c);
int	check_valid_move(int a, int b, t_app *c);

int	move_enemy(int newrow, int newcol, t_app *app)
{
	const char	tile_dest = app->map_grid[newrow][newcol];
	char *const	tile_orig = \
		&app->map_grid[app->enemy_pos.row][app->enemy_pos.col];

	if (app->enemy_pos.row == app->exit_pos.row
		&& app->enemy_pos.col == app->exit_pos.col)
		*tile_orig = EXIT;
	else if (on_a_loot(app, app->enemy_pos) == SUCCESS)
		*tile_orig = LOOT;
	else
		*tile_orig = SPACE;
	app->enemy_pos.row = newrow;
	app->enemy_pos.col = newcol;
	app->map_grid[app->enemy_pos.row][app->enemy_pos.col] = BADGUY;
	render_map(app);
	if (P_UP == tile_dest || P_DOWN == tile_dest || P_LEFT == tile_dest
		|| P_RIGHT == tile_dest)
		on_destroy(app, FAILURE);
	return (SUCCESS);
}

int	on_keypress(int keycode, void *param)
{
	t_app	*app;

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
	return (0);
}

int	on_destroy(void *param, int cond)
{
	t_app	*app;

	app = (t_app *)param;
	if (cond == SUCCESS)
		ft_printf("YOU WIN!\n");
	else
		ft_printf("YOU LOSSSST\n");
	cleanup(app);
	exit(EXIT_SUCCESS);
	return (0);
}

int	check_valid_move(int row, int col, t_app *app)
{
	char	ch;

	if ((row < 0 || row >= app->height) || (col < 0 || col >= app->width))
		return (FAILURE);
	ch = app->map_grid[row][col];
	if (ch == BADGUY || P_UP == ch || P_DOWN == ch || P_LEFT == ch
		|| P_RIGHT == ch)
		return (SUCCESS);
	if (ch == SPACE || ch == LOOT || ch == EXIT)
		return (SUCCESS);
	return (FAILURE);
}

int	move_player(char direction, int newrow, int newcol, t_app *app)
{
	const char	tile_dest = app->map_grid[newrow][newcol];
	char *const	tile_orig = &app->map_grid[app->player.row][app->player.col];

	if (check_valid_move(newrow, newcol, app) == SUCCESS)
	{
		if (app->player.row == app->exit_pos.row
			&& app->player.col == app->exit_pos.col)
			*tile_orig = EXIT;
		else
			*tile_orig = SPACE;
		app->player.row = newrow;
		app->player.col = newcol;
		if (tile_dest == LOOT)
			remove_loot(app, newrow, newcol);
		app->moves++;
	}
	update_player_direction(app, direction);
	render_map(app);
	if (tile_dest == BADGUY)
		on_destroy(app, FAILURE);
	if (tile_dest == EXIT && app->loots == 0)
		on_destroy(app, SUCCESS);
	return (SUCCESS);
}
