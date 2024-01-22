/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:27:16 by ahammoud          #+#    #+#             */
/*   Updated: 2024/01/22 12:31:46 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 960
#define HEIGHT 720

typedef struct s_img_data
{
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img_data;

typedef struct s_hook_parameters
{
	t_parameters	parameters;
	void			*connection_id;
	void			*window_id;
	void			*img_id;
}t_hook_parameters;

static void	stablish_conection(void **connection_id, void **window_id,
		void **img_id)
{
	*connection_id = mlx_init();
	if (connection_id == NULL)
	{
		perror("Error\nFailed to stablish a connection with the X server");
		return ;
	}
	*window_id = mlx_new_window(*connection_id, WIDTH, HEIGHT, "Minirt");
	if (*window_id == NULL)
	{
		perror("Error\nFailed to create a window");
//		mlx_destroy_display(*connection_id);
		return ;
	}
	*img_id = mlx_new_image(*connection_id, WIDTH, HEIGHT);
	if (*img_id == NULL)
	{
		perror("Error\nFailed to create a buffer");
		mlx_destroy_window(*connection_id, *window_id);
	//	mlx_destroy_display(*connection_id);
		return ;
	}
}

static int	redraw(void *parameters_ptr)
{
	const t_hook_parameters	parameters = *(t_hook_parameters *)parameters_ptr;
	t_img_data				img_data;

	img_data.addr = mlx_get_data_addr(parameters.img_id,
			&img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);
	mlx_put_image_to_window(parameters.connection_id, parameters.window_id,
		parameters.img_id, 0, 0);
	return (0);
}

static int	destroy_and_exit(void *parameters_ptr)
{
	const t_hook_parameters	parameters = *(t_hook_parameters *)parameters_ptr;

	mlx_destroy_image(parameters.connection_id, parameters.img_id);
	mlx_destroy_window(parameters.connection_id, parameters.window_id);
//	mlx_destroy_display(parameters.connection_id);
	destroy_parameters(parameters.parameters);
	exit(0);
}

static int	check_for_esc(int keycode, void *parameters_ptr)
{
	if (keycode == 53 || keycode == 65307)
		destroy_and_exit(parameters_ptr);
	return (0);
}

void	render_scene(t_parameters parameters)
{
	void						*connection_id;
	void						*window_id;
	void						*img_id;
	t_img_data					img_data;
	static t_hook_parameters	hook_parameters;

	stablish_conection(&connection_id, &window_id, &img_id);
	if (connection_id == NULL || window_id == NULL || img_id == NULL)
		return ;
	hook_parameters = (t_hook_parameters){.connection_id = connection_id,
		.window_id = window_id, .img_id = img_id, .parameters = parameters};
	img_data.addr = mlx_get_data_addr(img_id, &img_data.bits_per_pixel,
			&img_data.line_length, &img_data.endian);
	if (img_data.bits_per_pixel == 32 && img_data.endian == 0)
	{
		render_scene_in_buffer(parameters, img_data.addr, HEIGHT, WIDTH);
		mlx_hook(window_id, 12, 0, redraw, &hook_parameters);
		mlx_hook(window_id, 2, 1, check_for_esc, &hook_parameters);
		mlx_hook(window_id, 17, 0, destroy_and_exit, &hook_parameters);
		mlx_put_image_to_window(connection_id, window_id, img_id, 0, 0);
		mlx_loop(connection_id);
	}
	write(STDERR_FILENO, "This system not supported, aborting\n", 35);
	destroy_and_exit(&hook_parameters);
}
