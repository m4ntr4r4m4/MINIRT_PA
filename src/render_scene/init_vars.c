#include "ray.h"

t_ray	init_ray(t_vars *vars, double u, double v)
{
	t_ray	ray;

	ray.origin = vars->camera.origin;
	ray.direction = vecnormalize(vecplus(vars->camera.direction, \
					vecplus(vecscale(vars->camera.right, u), \
					vecscale(vars->camera.up, v))));
	return (ray);
}

void	ft_check_pl(t_vars *vars, t_ray ray)
{
	double	t;
	size_t	i;

	i = 0;
	while (i < vars->pl_size)
	{
		if (plane_intersaction(ray, &t, vars->planes[i]) && t < vars->closest_t)
		{
			vars->closest_t = t;
			vars->sphere_idx = -1;
			vars->plane_idx = i;
			vars->cy_idx = -1;
		}
		i++;
	}
}

void	ft_check_cy(t_vars *vars, t_ray ray)
{
	double	t;
	size_t	i;

	i = 0;
	while (i < vars->cy_size)
	{
		if (cylinder_intersaction(ray, &t, vars->cylanders[i]) && t < vars->closest_t)
		{
			vars->closest_t = t;
			vars->sphere_idx = -1;
			vars->plane_idx = -1;
			vars->cy_idx = i;
		}
		i++;
	}
}

void	ft_check_sp(t_vars *vars, t_ray ray)
{
	double	t;
	size_t	i;

	i = 0;
	while (i < vars->sp_size)
	{
		if (sphere_intersaction(ray, &t, vars->spheres[i]) && t < vars->closest_t)
		{
			vars->closest_t = t;
			vars->sphere_idx = i;
			vars->plane_idx = -1;
			vars->cy_idx = -1;
		}
		i++;
	}
}

unsigned int	ft_color_obj(t_vars *vars, t_ray ray)
{
	double	t;

	t = 0;
	if (vars->sphere_idx != -1)
	{
		sphere_intersaction(ray, &t, vars->spheres[vars->sphere_idx]);
		return (calculate_sphere_color(ray, \
			vars, vars->spheres[vars->sphere_idx], t));
	}
	if (vars->plane_idx != -1)
	{
		plane_intersaction(ray, &t, vars->planes[vars->plane_idx]);
		return (calculate_plane_color(ray, \
			vars, vars->planes[vars->plane_idx], t));
	}
	if (vars->cy_idx != -1)
	{
		cylinder_intersaction(ray, &t, vars->cylanders[vars->cy_idx]);
		return (calculate_cylinder_color(ray, vars, \
			vars->cylanders[vars->cy_idx], t));
	}
	return (0);
}
