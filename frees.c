#include "solong.h"

void	cleanup(t_app *);
void	free_map_grid(t_app *);

void	cleanup(t_app *app)
{
	free_map_grid(app);
	free(app);
}

void	free_map_grid(t_app *app)
{
	char **ptr;

	ptr = app->map_grid;
	if (ptr)
	{
		while (*ptr)
			free((*ptr)++);
	}
	free(ptr);
}
