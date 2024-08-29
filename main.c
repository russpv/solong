#include "solong.h"

int main(int argc, char **argv)
{
	t_app app = {0};

	init_struct(&app);
	parse_args(argc, argv, &app);
	init_app(&app);
	check_paths(&app);
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.width * SCALE, \
			app.height * SCALE, "A MinilibX Game");
	if (!app.win_ptr)
		err("Window initialization error", &app);
	render_map(&app);
	mlx_hook(app.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &app);
	mlx_hook(app.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &app);
	mlx_loop(app.mlx_ptr);
	return (EXIT_SUCCESS);
}
