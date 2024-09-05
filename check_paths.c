#include "solong.h"

int			find_path(t_app *a, t_pos b, int c, int d);
int			check_paths(t_app *a);
static void	_new_blank_map(t_app *a);
static int	_valid_move(t_app *a, int b, int c);

/* Returns false if location is out-of-bounds */
static int	_valid_move(t_app *app, int row, int col)
{
	if ((app->map_grid[row][col] == WALL) || (app->map_grid[row][col] == BADGUY)
		|| (row < 0) || (col < 0) || (row + 1 > app->height) || (col
			+ 1 > app->width))
		return (FAILURE);
	return (SUCCESS);
}

/* Returns a new blank map; null-terminated due to free function */
static void	_new_blank_map(t_app *app)
{
	int	i;

	if (app->test_map)
		free_map_grid(app->test_map);
	app->test_map = malloc(sizeof(char *) * (app->height + 1));
	if (!app->test_map)
		err("Error\nMalloc error", app, -1, NULL);
	app->test_map[app->height] = NULL;
	i = -1;
	while (++i < app->height)
	{
		app->test_map[i] = malloc(sizeof(char) * (app->width + 1));
		if (!app->test_map[i])
			err("Error\nMalloc error", app, -1, NULL);
		ft_memset(app->test_map[i], NOTVISI, sizeof(char) * app->width);
		app->test_map[i][app->width] = '\0';
	}
}

/* Recursively moves through map until goal reached */
int	find_path(t_app *app, t_pos goal, int row, int col)
{
	t_pos	current;

	if (!_valid_move(app, row, col) || app->test_map[row][col] == VISITED)
		return (FAILURE);
	current.row = row;
	current.col = col;
	app->test_map[row][col] = VISITED;
	if (goal.row == current.row && goal.col == current.col)
		return (SUCCESS);
	if ((find_path(app, goal, row - 1, col)) || (find_path(app, goal, row + 1,
				col)) || (find_path(app, goal, row, col - 1)) || (find_path(app,
				goal, row, col + 1)))
		return (SUCCESS);
	app->test_map[row][col] = NOTVISI;
	return (FAILURE);
}

/* Tests that all loot and exit can be reached from start */
int	check_paths(t_app *app)
{
	int	i;

	_new_blank_map(app);
	if (!find_path(app, app->exit_pos, app->player.row, app->player.col))
		return (FAILURE);
	i = -1;
	while (++i < app->loots)
	{
		_new_blank_map(app);
		if (!find_path(app, app->loots_pos[i], app->player.row,
				app->player.col))
			return (free_map_grid(app->test_map), FAILURE);
	}
	free_map_grid(app->test_map);
	app->test_map = NULL;
	return (SUCCESS);
}
