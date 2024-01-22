#include <stdlib.h>
#include <stdio.h>
#include "ray.h"

int sphere_intersaction(t_vars *vars, t_ray ray, double *t, t_sp sphere)
{
	t_vec oc;

	oc = vecminus(ray.origin, sphere.center);
	double a = vecdot(ray.direction, ray.direction);
	double b = 2.0 *  vecdot(oc, ray.direction);
	double c = (double)vecdot(oc, oc) - (sphere.radius * sphere.radius);
	double dicriminant = (b * b) - (4*a*c);
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



void calculate_diffuse(t_vec p, t_vec n, t_vars *vars , t_sp sphere)
{
	t_vec lightDirection = vecnormalize(vecminus(vars->light.origin , p)); // Direction to the spotlight

    double dotProduct = vecdot( n, lightDirection);
    double cosAngle = vecdot(n, lightDirection);
    if (cosAngle > 0.0)
    {
	    if (!shadowed(vars, p, vars->light, (char *)&sphere))
	    {
		vars->color.r += (sphere.r * cosAngle) * vars->light.ratio;
		vars->color.g += (sphere.g * cosAngle) * vars->light.ratio;
		vars->color.b += (sphere.b * cosAngle) * vars->light.ratio;
	    }
	vars->color.r = ft_clamp(vars->color.r, 0, 255);
	vars->color.g = ft_clamp(vars->color.g, 0, 255);
	vars->color.b = ft_clamp(vars->color.b, 0, 255);
    }

}

double vecsquaredlength(t_vec v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

void calculate_ambient(t_vars *vars)
{
	vars->color.r = vars->ambient.ratio * vars->ambient.r; 
	vars->color.g = vars->ambient.ratio * vars->ambient.g; 
	vars->color.b = vars->ambient.ratio * vars->ambient.b; 
}

int shadowed(t_vars *vars, t_vec p, t_ablight light, char *add)
{
	double t;
	t_vec lightDirection = vecnormalize(vecminus(light.origin , p)); // Direction to the spotlight
	t_ray shadow;
	double t_sphere;
	shadow.origin = p;
	shadow.direction = lightDirection;
	t = 0;
    for (int i = 0; i < vars->sp_size; i++) {

	    if (strlen(add) && !strcmp((char *)&vars->spheres[i], add))
	    {
	    	continue;
	    }
        sphere_intersaction(vars,shadow, &t, vars->spheres[i]);
        if (t > 1e-4 && t < veclength(vecminus(light.origin, p)))
            return 1; // Point is in shadow
        }

    for (int i = 0; i < vars->pl_size; i++) {
          if (strlen(add) && !strcmp((char *)&vars->planes[i], add))
          {
      	    continue;
          }
        plane_intersaction(vars,shadow, &t, vars->planes[i]);
        if (t > 1e-4 && t < veclength(vecminus(light.origin, p)))
        {
            return 1; // Point is in shadow
        }
    }

    for (int i = 0; i < vars->cy_size; i++) {
	    if (strlen(add) && !strcmp((char *)&vars->cylanders[i], add))
	    {
      	    	continue;
	    }
        cylinder_intersaction(vars,shadow, &t, vars->cylanders[i]);
        if (t > 1e-4 && t < veclength(vecminus(light.origin, p)))
        {
            return 1; // Point is in shadow
        }
    }

	return 0;
}

int	calculate_sphere_color(t_ray ray, t_vars *vars, t_sp sphere, double t_sphere)
{
	calculate_ambient(vars);

	t_vec intersection = vecplus(ray.origin , vecscale(ray.direction ,t_sphere));
	t_vec sphere_normal = vecnormalize(vecminus(intersection , sphere.center));

	calculate_diffuse(intersection, sphere_normal, vars, sphere);
	return (create_trgb(0, vars->color.r,  vars->color.g, vars->color.b));
}
