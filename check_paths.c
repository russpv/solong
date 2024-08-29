#include "solong.h"

int		find_path(t_app*, t_pos, int, int);
static void	_new_blank_map(t_app*);
int		check_paths(t_app*);
static int	_valid_move();

static int	_valid_move();
{
	//TODO
}

/* Returns a new blank map */
static void	_new_blank_map(t_app *app)
{
	int i;

	if (app->test_map)
		free_map_grid(app->test_map);
	app->test_map = malloc(sizeof(char *) * (app->height + 1));
	if (!app->test_map)
		err("Malloc error", app);
	app->test_map[app->height] = NULL;
	i = -1;
	while (app->test_map[++i])
	{
		app->test_map[i] = malloc(sizeof(char) * (app->width + 1));
		if (!app->test_map[i])
			err("Malloc error", app);
		ft_memset(app->test_map[i], NOTVISI, sizeof(char) * app->width);
	}
	app->test_map[app->height][app->width] = '\0';
}

/* Recursively moves through map until goal reached */
int	find_path(t_app *app, t_pos goal, int row, int col)
{
	t_pos current;

	if (!valid_move(app, row, col))
		return (FAILURE);
	current.row = row;
	current.col = col;
	app->test_map[row][col] = VISITED;
	if (goal.row == current.row && goal.col == current.col)
		return (SUCCESS);
	if ((find_path(app, goal, row - 1, col)) ||
		(find_path(app, goal, row + 1, col)) ||
		(find_path(app, goal, row, col - 1)) ||
		(find_path(app, goal, row, col + 1)))
		return (SUCCESS);
	app->test_map[row][col] = NOTVISI;
	return (FAILURE);
}

/* Tests that all loot and exit can be reached from start */
int	check_paths(t_app *app)
{
	int i;

	_new_blank_map(app);
	if (!find_path(app, app->exit_pos, app->player.row, app->player.col))
		return (FAILURE);
	i = -1;
	while (++i < app->loots)
	{
		_new_blank_map(app);
		if (!find_path(app, app->loots_pos[i], app->player.row, app->player.col))
			return (FAILURE);
	}
	free_map_grid(app->test_map);
	app->test_map = NULL;	
	return (SUCCESS);
}
