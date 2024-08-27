#include "solong.h"

void	err(char *msg, t_app *app);
void	_cleanup(t_app*);
void	print_map(t_app*);
size_t	arrlen(char **);

size_t	arrlen(char **arr)
{
	size_t i;
	
	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

/* Test function TODO delete */
void	print_map(t_app *app)
{
	const char **ptr = (const char **)app->map_grid;

	if (!ptr)
		return ;
	if (!*ptr)
		return ;
	while (*ptr)
		ft_printf("%s\n", *ptr++);
}

void	err(char *msg, t_app *app)
{
	// TODO: custom "Error: msg" printingi
	errno = EINVAL;
	perror(msg);
	_cleanup(app);
	exit(1);
}

void	_cleanup(t_app *app)
{
	if (app->map_grid)
		free_map_grid(app);
}

void	init_struct(t_app *app)
{
	app->img_ptr = NULL;
	app->mlx_ptr = NULL;
	app->win_ptr = NULL;
	app->map_grid = NULL;
	app->width = 0;
	app->height = 0;
	app->moves = 0;
}

