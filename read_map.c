#include "solong.h"

static void	_do_trim(t_app *a, char **b, int c, char *d);
int			get_line(int a, char **b);
void		get_map(char *a, int b, t_app *c);

/* Trims any carriage returns */
static void	_do_trim(t_app *app, char **tmp, int fd, char *buf)
{
	char	*tmp2;

	tmp2 = ft_strtrim(*tmp, "\r\0 ");
	if (!tmp2)
		err(RED"Malloc error"DEFAULT, app, fd, buf);
	ft_memset(*tmp, 0, ft_strlen(*tmp));
	ft_memmove(*tmp, tmp2, ft_strlen(tmp2));
	free(tmp2);
}

/* Get a string line from input file */
int	get_line(int fd, char **buf)
{
	int		i;
	int		bytes_read;
	char	ch;

	*buf = malloc(sizeof(char) * BUFSZ);
	if (!(*buf))
		return (perror("Malloc error"), FAILURE);
	i = 0;
	while (i < BUFSZ - 2)
	{
		bytes_read = read(fd, &ch, 1);
		if (0 >= bytes_read)
		{
			if (0 == i)
				return (bytes_read);
			break ;
		}
		(*buf)[i++] = ch;
		if (ch == '\n' || ch == '\0' || ch == '\r')
			break ;
	}
	(*buf)[i] = 0;
	return (i);
}

/* Read input file into buffer */
void	get_map(char *tmp, int fd, t_app *app)
{
	int		bytes;
	char	*buf;

	while (1)
	{
		bytes = get_line(fd, &buf);
		if (bytes > 0)
		{
			if (ft_strlcat(tmp, buf, BUFSZ) >= BUFSZ)
				err(RED "Aborted: map read buffer overflow"DEFAULT, \
						app, fd, buf);
			else
				_do_trim(app, &tmp, fd, buf);
		}
		free(buf);
		if (bytes <= 0)
			break ;
	}
	close(fd);
	if (bytes < 0)
		err(RED "Aborted: problem reading map file" DEFAULT, app, \
				-1, NULL);
}
