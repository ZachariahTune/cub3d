/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by khestia           #+#    #+#             */
/*   Updated: 2022/04/08 00:02:02 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Закрытие программы (из-за ошибки карты или крестиком/esc)
int	cub_close(t_all *all, int win_destroy)
{
	int	i;

	i = 0;
	while (i < all->map.y)
		free(all->map.tab[i++]);
	free(all->map.tab);
	free(all->tex.no);
	free(all->tex.so);
	free(all->tex.we);
	free(all->tex.ea);
	if (win_destroy == 1)
		mlx_destroy_window(all->mlx.ptr, all->win.ptr);
	write(1, "Exit: Program closed\n", 21);
	exit(0);
	return (1);
}

//В этой функции программа завершает свою работу
static void	cub_init_struct_three(t_all all, char *file)
{
	t_cam	cam;
	int		win_height;

	win_height = (int)floor(WIN_WIDTH / 16 * 9);
	cam.px = 0;
	cam.py = 0;
	cam.dx = 0;
	cam.dy = 0;
	all.cam = cam;
	all.mlx.ptr = mlx_init();
	if (cub_parse(&all, file) == -1)
		cub_close(&all, 0);
	all.win.ptr = mlx_new_window(all.mlx.ptr, WIN_WIDTH, win_height, "cub3D");
	cub_draw(&all);
	mlx_hook(all.win.ptr, 2, 0, cub_keydown, &all);
	mlx_hook(all.win.ptr, 17, 0, cub_close, &all);
	mlx_loop(all.mlx.ptr);
}

//Инициализация структур (продолжение)
static void	cub_init_struct_two(t_all all, char *file)
{
	t_map	map;
	t_tex	tex;

	map.tab = NULL;
	map.x = 0;
	map.y = 0;
	tex.no = NULL;
	tex.so = NULL;
	tex.we = NULL;
	tex.ea = NULL;
	tex.f = 0;
	tex.c = 0;
	all.map = map;
	all.tex = tex;
	cub_init_struct_three(all, file);
}

//Инициализация структур
static void	cub_init_struct_one(char *file)
{
	t_all	all;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	all.mlx = mlx;
	all.win = win;
	all.img = img;
	all.err = err;
	cub_init_struct_two(all, file);
}

//Основная функция программы
int	main(int argc, char **argv)
{
	if (argc != 2 || cub_filename_ext(argv[1], "cub") == 0)
		write(2, "Error: Invalid argument\n", 24);
	else
		cub_init_struct_one(argv[1]);
	return (0);
}
