#include "ray.h"
#include <stdio.h>


int sphere_intersaction(t_parameters *vars, t_ray ray, long double *t, t_sphere sphere)
{
	t_vector oc;

	oc = substract(ray.origin, sphere.center);
	long double a = dot_product(ray.direction, ray.direction);
	long double b = 2.0 *  dot_product(oc, ray.direction);
	long double c = dot_product(oc, oc) - ((sphere.diameter / 2)* (sphere.diameter / 2));
	long double dicriminant = (b * b) - (4*a*c);
	if (dicriminant < 0)
	{
		return(0);
	}
	float t1 = (-b - sqrt(dicriminant)) / (2.0 * a);
        float t2 = (-b + sqrt(dicriminant)) / (2.0 * a);

	if (t1 > 0 && (t1 < t2 || t2 <= 0)) {
            *t = t1;
        } else {
            *t = t2;
        }
	return (1);
}

void calculate_diffuse(t_vector p, t_vector n, t_parameters *vars , t_sphere sphere)
{
	t_vector lightDirection = normalize(substract(vars->light.position , p));

    long double dotProduct = dot_product( n, lightDirection);
    long double cosAngle = dot_product(n, lightDirection);
    if (cosAngle > 0.0)
    {
	    if (!shadowed(vars, p, vars->light))
	    {
    		printf("color %c %c %c\n", vars->color.r, vars->color.g, vars->color.b);
		    vars->color = color_add(vars->color, color_multiply(sphere.color, cosAngle * vars->light.brightness));
  printf("color %c %c %c\n", vars->color.r, vars->color.g, vars->color.b);
	    }
    }

}


void calculate_ambient(t_parameters *vars)
{
	vars->color = color_multiply(vars->ambient_lighting.color, vars->ambient_lighting.initialized); 
}

int shadowed(t_parameters *vars, t_vector p, t_light light)
{
	long double t;
	t_vector lightDirection = normalize(substract(light.position , p));
	t_ray shadow;
	long double t_sphere;
	shadow.origin = p;
	shadow.direction = lightDirection;
    for (int i = 0; i < vars->sphere_list.size; i++) {
        sphere_intersaction(vars,shadow, &t, vars->sphere_list.spheres[i]);
	if (t > 1e-4 && t < get_magnitude(substract(light.position, p)))
            return 1;
    }

    for (int i = 0; i < vars->plane_list.size; i++) {
        plane_intersaction(vars,shadow, &t, vars->plane_list.planes[i]);
	if (t > 1e-4 && t < get_magnitude(substract(light.position, p)))
            return 1;
    }
    for (int i = 0; i < vars->cylinder_list.size; i++) {
        cylinder_intersaction(vars,shadow, &t, vars->cylinder_list.cylinders[i]);
	if (t > 1e-4 && t < get_magnitude(substract(light.position, p)))
            return 1;
    }
	return 0;
}

int	calculate_sphere_color(t_ray ray, t_parameters *vars, t_sphere sphere, long double t_sphere)
{
	calculate_ambient(vars);

	t_vector intersection = add(ray.origin , multiply(ray.direction ,t_sphere));
	t_vector sphere_normal = normalize(substract(intersection , sphere.center));
	calculate_diffuse(intersection, sphere_normal, vars, sphere);
	return ( (unsigned)vars->color.r << 16 | (unsigned)vars->color.g << 8 | (unsigned)vars->color.b);
}
