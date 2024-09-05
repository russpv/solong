#include "solong.h"
#include <time.h>

int			update_game(void *);
int			init_animation(t_app *);
double		get_time_elapsed(clock_t);

static int	_animate_player(t_app *);
static int	_enemy_move_timer(t_app *);

/* Returns relative time elapsed in seconds */
double	get_time_elapsed(clock_t time)
{
	return ((double)(clock() - time) / CLOCKS_PER_SEC);
}

int	update_game(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	_animate_player(app);
	if (app->enemies > 0)
		_enemy_move_timer(app);
	return (SUCCESS);
}

static int	_animate_player(t_app *app)
{
	if (get_time_elapsed(app->time) <= TARGET_DELAY)
		return (FAILURE);
	app->time = clock();
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->space.xpm_ptr,
		app->player.col * SCALE, app->player.row * SCALE);
	if (NUM_FRAMES == ++app->frame)
		app->frame = 0;
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->frames[app->player_facing][app->frame].xpm_ptr, app->player.col
		* SCALE, app->player.row * SCALE);
	return (SUCCESS);
}

int	init_animation(t_app *app)
{
	void	*ptr;

	ptr = app->mlx_ptr;
	if (!app)
		return (FAILURE);
	app->space = new_sprite(ptr, SPACE_XPM);
	app->frames[right][0] = new_sprite(ptr, PLAYER_RIGHT_XPM);
	app->frames[right][1] = new_sprite(ptr, PLAYER_RIGHT_2_XPM);
	app->frames[right][2] = new_sprite(ptr, PLAYER_RIGHT_3_XPM);
	app->frames[up][0] = new_sprite(ptr, PLAYER_UP_XPM);
	app->frames[up][1] = new_sprite(ptr, PLAYER_UP_2_XPM);
	app->frames[up][2] = new_sprite(ptr, PLAYER_UP_3_XPM);
	app->frames[down][0] = new_sprite(ptr, PLAYER_DOWN_XPM);
	app->frames[down][1] = new_sprite(ptr, PLAYER_DOWN_2_XPM);
	app->frames[down][2] = new_sprite(ptr, PLAYER_DOWN_3_XPM);
	app->frames[left][0] = new_sprite(ptr, PLAYER_LEFT_XPM);
	app->frames[left][1] = new_sprite(ptr, PLAYER_LEFT_2_XPM);
	app->frames[left][2] = new_sprite(ptr, PLAYER_LEFT_3_XPM);
	app->time = clock();
	app->enemy_timestamp = app->time;
	srand(time(NULL));
	return (SUCCESS);
}

static int	_enemy_move_timer(t_app *app)
{
	int	rnum;
	int	row;
	int	col;

	if (get_time_elapsed(app->enemy_timestamp) < ENEMY_DELAY)
		return (FAILURE);
	row = -1;
	col = -1;
	while (FAILURE == check_valid_move(row, col, app))
	{
		row = app->enemy_pos.row;
		col = app->enemy_pos.col;
		rnum = rand() % 4;
		if (up == rnum)
			row++;
		else if (down == rnum)
			row--;
		else if (right == rnum)
			col++;
		else if (left == rnum)
			col--;
	}
	app->enemy_timestamp = clock();
	move_enemy(row, col, app);
	return (SUCCESS);
}
