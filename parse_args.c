#include "solong.h"

static int	_checkarg(const char *_);
static int	_check_map_square(t_app *_);
void		parse_args(int argc, char **argv, t_app *_);

/* Run simple argument format checks */
static int	_checkarg(const char *filename)
{
	const size_t	len = ft_strlen(filename);

	if (len < ft_strlen(EXTENSION))
		return (perror("Error\nArgument must be a "EXTENSION" map file") \
				, FAILURE);
	if (ft_strncmp(&filename[len - 4], EXTENSION, 4) != 0)
		return (perror("Error\nArgument must be a .ber map file"), FAILURE);
	if (access(filename, F_OK) != 0)
		return (perror("Error\nInput file does not exist"), FAILURE);
	if (access(filename, R_OK) != 0)
		return (perror("Error\nInput file couldn't be read"), FAILURE);
	return (SUCCESS);
}

/* Ensures all rows are same length */
static int	_check_map_square(t_app *app)
{
	int	i;

	if (!app->map_grid)
		return (FAILURE);
	i = -1;
	while (++i < app->height)
		if (ft_strlen(app->map_grid[i]) != (size_t)app->width)
			return (FAILURE);
	return (SUCCESS);
}

/* Takes .ber map file and reads it into a grid */
void	parse_args(int argc, char **argv, t_app *app)
{
	int		fd;
	char	tmp[BUFSZ];

	ft_memset(tmp, 0, sizeof(tmp));
	if (argc != 2)
		err(RED "Error\nProgram requires exactly one argument" DEFAULT, \
				app, -1, NULL);
	if (_checkarg(argv[1]) == FAILURE)
		err(RED "Error\nProblem parsing .ber file" DEFAULT, app, -1, NULL);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		err(RED "Error\nProblem opening input file" DEFAULT, app, -1, NULL);
	get_map(tmp, fd, app);
	app->map_grid = ft_split(tmp, '\n');
	if (!app->map_grid)
		err(RED "Error\nmalloc error" DEFAULT, app, -1, NULL);
	app->width = ft_strlen(app->map_grid[0]);
	app->height = arrlen(app->map_grid);
	if (_check_map_square(app) == FAILURE)
		err(RED "Error\nmap not square" DEFAULT, app, -1, NULL);
}
