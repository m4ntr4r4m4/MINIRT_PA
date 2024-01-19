#include "ray.h"


int cylinder_intersaction(t_vars *vars, t_ray ray, double *t, t_cy cylinder)
{
	t_vec oc;
	t_vec axis;
	
	oc = vecminus(ray.origin, cylinder.center);
	axis = vecnormalize(cylinder.axis);
	t_vec acaled_ray_axis =  vecscale(axis, vecdot(ray.direction, axis)) ;
	t_vec scaled_oc_axis =  vecscale(axis, vecdot(oc, axis)) ;
	double a = vecdot(vecminus(ray.direction, acaled_ray_axis ), vecminus(ray.direction, acaled_ray_axis)); 
	double b = 2.0 * vecdot(vecminus(ray.direction , acaled_ray_axis), vecminus(oc , acaled_ray_axis));
	double c = vecdot(vecminus(oc, scaled_oc_axis), vecminus(oc, scaled_oc_axis)) - 0.25 * cylinder.diameter * cylinder.diameter;


	double dicriminant = (b * b) - (4*a*c);

	if (dicriminant < 0)
	{
		return(0);
	}
//	printf("this t_cylinder %f\n", dicriminant);
	double t1 = (-b - sqrt(dicriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(dicriminant)) / (2.0 * a);
	t_vec point1 = vecplus(ray.origin, vecscale(ray.direction, t1));
	t_vec point2 = vecplus(ray.origin, vecscale(ray.direction, t2));
	double h1 = vecdot(vecminus(point1, cylinder.center), cylinder.axis);
	double h2 = vecdot(vecminus(point2, cylinder.center), cylinder.axis);
//	printf("this t_cylinder %f\n", h1);
	if (t1 > 1e-6 && h1 > 0.0 && h1 <= cylinder.height)
	{
            *t = t1;
	    return 1;
	}
	if (t2 > 1e-6  && h2 > 0.0 && h2 <= cylinder.height)
	{
            *t = t2;
	    return 1;
	}
	return (0);
}

void calculate_diffuse_cy(t_vec p, t_vec n, t_vars *vars , t_cy cylinder)
{
	t_vec lightDirection = vecnormalize(vecminus(vars->light.origin , p)); // Direction to the spotlight

    double cosAngle = vecdot(n, lightDirection);
    if (cosAngle > 0.0)
    {
	    if (!shadowed(vars, p, vars->light, (char *)&cylinder))
	    {
		vars->color.r += (cylinder.r * cosAngle) * vars->light.ratio;
		vars->color.g += (cylinder.g * cosAngle) * vars->light.ratio;
		vars->color.b += (cylinder.b * cosAngle) * vars->light.ratio;
	    }
	vars->color.r = ft_clamp(vars->color.r, 0, 255);
	vars->color.g = ft_clamp(vars->color.g, 0, 255);
	vars->color.b = ft_clamp(vars->color.b, 0, 255);
    }

}

t_vec  cy_normal(t_vec p, t_cy cylinder)
{
    // Calculate vector from the center of the cylinder to the intersection point
    t_vec cp = vecminus(p , cylinder.center);

    // Calculate the component of the vector along the cylinder's axis
    double projection = vecdot(cp, cylinder.axis);

    // Calculate the projection vector along the axis
    t_vec alongAxis = vecscale(cylinder.axis , projection);

    // Calculate the surface normal by subtracting the projection vector
    return ( vecnormalize(vecminus(cp, alongAxis)));
}

int	calculate_cylinder_color(t_ray ray, t_vars *vars, t_cy cylinder, double t_cylinder)
{
	calculate_ambient(vars);

	t_vec intersection = vecplus(ray.origin , vecscale(ray.direction ,t_cylinder));
	t_vec cylinder_normal = cy_normal(intersection, cylinder); 

//	printf("this t_cylinder %f\n", t_cylinder);
	calculate_diffuse_cy(intersection, cylinder_normal, vars, cylinder);
	return (create_trgb(0, vars->color.r,  vars->color.g, vars->color.b));
}
