/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:24:22 by priezu-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:24:24 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SCENE_H
# define RENDER_SCENE_H

# include "../parameters/parameters.h"
# include "mlx.h"

typedef struct s_img_data
{
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_hook_parameters
{
	t_parameters	parameters;
	void			*connection_id;
	void			*window_id;
	void			*img_id;
}	t_hook_parameters;

void			render_scene(t_parameters parameters);
void			render_scene_in_buffer(t_parameters parameters,
					unsigned int *buffer, int height, int width);

#endif
