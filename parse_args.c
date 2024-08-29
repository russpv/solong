#include "solong.h"

void	parse_args(int argc, char **argv, t_app *app);
int		_checkarg(const char *);
void	get_map(char*, int, t_app *);
int		get_line(int, char **);

/*
static void print_map_content(const char *map) {
    for (size_t i = 0; map[i] != '\0'; i++) {
        fprintf(stderr, "Character %zu: '%c' (ASCII: %d)\n", i, map[i], (unsigned char)map[i]);
    }
	fflush(stderr);
}
*/
/* Run simple format checks */
int		_checkarg(const char *filename)
{
	const size_t len = ft_strlen(filename);

	if (len < ft_strlen(EXTENSION)) 
		return (perror("Argument must be a "EXTENSION" map file"), FAILURE);
	if (ft_strncmp(&filename[len - 4], EXTENSION, 4) != 0)
		return (perror("Argument must be a .ber map file"), FAILURE);
	if (access(filename, F_OK) != 0)
		return (perror("Input file does not exist"), FAILURE);
	if (access(filename, R_OK) != 0)
		return (perror("Input file couldn't be read"), FAILURE);
	return (SUCCESS);
}

/* Read input file into buffer */
void	get_map(char *tmp, int fd, t_app *app)
{
	int 	bytes;
	char	*buf;
	char	*tmp2;

	buf = NULL;
	bytes = 0;
	while (1)
	{
		bytes = get_line(fd, &buf);
		if (bytes <= 0)
			break ;
		if (ft_strlcat(tmp, buf, BUFSZ) >= BUFSZ)
		{
			free(buf);
			close(fd);
			err("Aborted: map read buffer overflow", app);
		}
		else
		{
			tmp2 = ft_strtrim(tmp, "\r\0 ");
			ft_memset(tmp, 0, ft_strlen(tmp));
			ft_memmove(tmp, tmp2, ft_strlen(tmp2));
			free(tmp2);
		}
		free(buf);
		buf = NULL;
	}
	close(fd);
	if (bytes < 0)
		err("Aborted: problem reading map file", app);
}

/* Get a string line from input file */
int		get_line(int fd, char **buf)
{
	int 	i;
	int 	bytes;
	char	ch;

	*buf = malloc(sizeof(char) * BUFSZ);
	if (!(*buf))
		return (perror("Malloc error"), FAILURE);
	bytes = 0;
	i = -1;
	while (++i < BUFSZ - 2)
	{
		bytes += read(fd, &ch, 1);
		if (-1 == bytes)
		{
			free(*buf);
			return (perror("Read failed"), -2);
		}
		if (0 == bytes)
		{
			if (0 == i)
			{
				free(*buf);
				return (0);
			}
			break ;
		}
		(*buf)[i] = ch;
		if (ch == '\n' || ch == '\0' || ch == '\r')
			break ;
	}
	(*buf)[++i] = 0;
	return (bytes);
}

/* Takes .ber map file and reads it into a grid */
void	parse_args(int argc, char **argv, t_app *app)
{
	int		fd;
	char 	tmp[BUFSZ] = {0};

	if (argc == 1)
		err(RED"Aborted: Program requires an argument"DEFAULT, app);
	if (argc != 2)
		err(RED"Aborted: Program takes one argument only"DEFAULT, app);
	if (_checkarg(argv[1]) ==  FAILURE)
		err(RED"Aborted: Problem parsing .ber file", app);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
		err(RED"Aborted: Problem opening input file", app);
	get_map(tmp, fd, app);
	app->map_grid = ft_split(tmp, '\n'); // _trimstr(tmp, '\n');
	if (!app->map_grid)
		err(RED"Aborted: malloc error"DEFAULT, app);
	app->width = ft_strlen(app->map_grid[0]);
	app->height = arrlen(app->map_grid);
}
