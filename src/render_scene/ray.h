#ifndef RAY_H
#define RAY_H
#include "../vector/vector.h"
#include "../parameters/parameters.h"
#include "../color/color.h"
#include <math.h>

 typedef struct s_ray
{
	t_vector origin;
	t_vector direction;
}t_ray;

// PLANE FUNCTIONS
//
int	 plane_intersaction(t_parameters *vars, t_ray ray, long double *t, t_plane plane);
int	calculate_plane_color(t_ray ray, t_parameters *vars, t_plane plane, long double t_plane);
// CYLINDER FUNCTIONS
//
int	 cylinder_intersaction(t_parameters *vars, t_ray ray, long double *t, t_cylinder cylinder);
int	calculate_cylinder_color(t_ray ray, t_parameters *vars, t_cylinder cylinder, long double t_cylinder);

// SPHERE FUNCTIONS
//
int	 sphere_intersaction(t_parameters *vars, t_ray ray, long double *t, t_sphere sphere);
int	calculate_sphere_color(t_ray ray, t_parameters *vars, t_sphere sphere, long double t_sphere);
int	shadowed(t_parameters *vars, t_vector p, t_light light);
void	calculate_diffuse(t_vector p, t_vector n, t_parameters *vars , t_sphere sphere);
void	calculate_ambient(t_parameters *vars);
#endif
