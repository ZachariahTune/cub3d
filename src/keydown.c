/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <ztune@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by ztune             #+#    #+#             */
/*   Updated: 2022/04/08 00:02:02 by ztune            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Перемещение вперед/назад
static void	cub_move_ws(t_all *all, double step)
{
	double	pos_x_temp;
	double	pos_y_temp;

	pos_x_temp = all->cam.px + all->cam.dx * step;
	if (all->map.tab[(int)floor(all->cam.py)][(int)floor(pos_x_temp)] != '1')
		all->cam.px = pos_x_temp;
	pos_y_temp = all->cam.py + all->cam.dy * step;
	if (all->map.tab[(int)floor(pos_y_temp)][(int)floor(all->cam.px)] != '1')
		all->cam.py = pos_y_temp;
}

//Перемещение влево/вправо
static void	cub_move_ad(t_all *all, double step)
{
	double	pos_x_temp;
	double	pos_y_temp;

	pos_x_temp = all->cam.px + all->cam.dy * step;
	if (all->map.tab[(int)floor(all->cam.py)][(int)floor(pos_x_temp)] != '1')
		all->cam.px = pos_x_temp;
	pos_y_temp = all->cam.py - all->cam.dx * step;
	if (all->map.tab[(int)floor(pos_y_temp)][(int)floor(all->cam.px)] != '1')
		all->cam.py = pos_y_temp;
}

//Повороты налево/направо
static void	cub_turn(t_all *all, double turn)
{
	all->cam.dx = all->cam.dx * cos(turn) - all->cam.dy * sin(turn);
	all->cam.dy = all->cam.dy * cos(turn) + all->cam.dx * sin(turn);
}

//Нажатие кнопок на клавиатуре
int	cub_keydown(int key, void *all)
{
	if (key == KEY_W)
		cub_move_ws(all, MOVE_STEP);
	if (key == KEY_S)
		cub_move_ws(all, -MOVE_STEP);
	if (key == KEY_A)
		cub_move_ad(all, MOVE_STEP);
	if (key == KEY_D)
		cub_move_ad(all, -MOVE_STEP);
	if (key == KEY_LEFT)
		cub_turn(all, -MOVE_TURN);
	if (key == KEY_RIGHT)
		cub_turn(all, MOVE_TURN);
	if (key == KEY_ESC)
		cub_close(all, 1);
	cub_draw(all);
	return (1);
}
