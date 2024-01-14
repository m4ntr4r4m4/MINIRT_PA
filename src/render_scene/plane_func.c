#include "ray.h"

int	 plane_intersaction(t_parameters *vars, t_ray ray, long double *t, t_plane plane)
{
	double dot;

	dot = dot_product(plane.normal, ray.direction);
	if (fabs(dot) < 1e-8)
		return 0;
	*t  = dot_product(plane.normal, multiply(substract(plane.position, ray.origin), 1 / dot));
	if (*t < 0.0)
		return 0;
	return 1;
}
void calculate_diffuse_plane(t_vector p, t_vector n, t_parameters *vars , t_plane plane)
{
	t_vector lightDirection = normalize(substract(vars->light.position , p));

    long double dotProduct = dot_product( n, lightDirection);
    long double cosAngle = dot_product(n, lightDirection);
    vars->color = (t_color){.t = 0, .r = 255, .g = 0, .b = 0};
    if (cosAngle > 0.0)
    {
	    if (!shadowed(vars, p, vars->light))
	    {
		    vars->color = color_add(vars->color, color_multiply(plane.color, cosAngle * vars->light.brightness));
	    }
    }

}

int	calculate_plane_color(t_ray ray, t_parameters *vars, t_plane plane, long double t_plane)
{
	calculate_ambient(vars);

	t_vector intersection = add(ray.origin , multiply(ray.direction ,t_plane));

	calculate_diffuse_plane(intersection, plane.normal, vars, plane);
	return ( (unsigned)vars->color.r << 16 | (unsigned)vars->color.g << 8 | (unsigned)vars->color.b);
}
