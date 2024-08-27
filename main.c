#include "solong.h"

int main(int argc, char **argv)
{
	t_app app = {0};

	init_struct(&app);
	parse_args(argc, argv, &app);
	print_map(&app);
	init_app(&app);
	//ft_printf("creaing window %d x %d|", app.width * SCALE, app.height * SCALE);	
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.width * SCALE, app.height * SCALE, "hi :)");
	if (!app.win_ptr)
		return (free(app.mlx_ptr), 1);
	//ft_printf("created window|");
	fflush(stdout);	
	fprintf(stderr, "|%zu|", ft_strlen(app.map_grid[0])); 
	fflush(stderr); 
	render_map(&app);
	// TODO delete
	//int rgb = 201 << 16 | 62 << 8 | 62;
	//mlx_pixel_put(app.mlx_ptr, app.win_ptr, 1, 1, rgb);
	//char *str = "Eat a bag of dicks!";
   	//mlx_string_put(app.mlx_ptr, app.win_ptr, 2, 2, rgb, str);	

	mlx_hook(app.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &app);
	mlx_hook(app.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &app);
	mlx_loop(app.mlx_ptr);
	return (0);
}
