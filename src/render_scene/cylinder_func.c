#include "ray.h"


int cylinder_intersaction(t_parameters *vars, t_ray ray, long double *t, t_cylinder cylinder)
{
	t_vector oc;
	t_vector axis;
	
	axis = normalize(cylinder.direction);
	t_vector acaled_ray_axis =  multiply(axis, dot_product(ray.direction, axis)) ;
	t_vector scaled_oc_axis =  multiply(axis, dot_product(oc, axis)) ;
	oc = substract(ray.origin, cylinder.geometric_center);
	double a = dot_product(substract(ray.direction, acaled_ray_axis ), substract(ray.direction, acaled_ray_axis)); 
	double b = 2.0 * dot_product(substract(ray.direction , acaled_ray_axis), substract(oc , acaled_ray_axis));
	double c = dot_product(substract(oc, scaled_oc_axis), substract(oc, scaled_oc_axis)) - 0.25 * cylinder.diameter * cylinder.diameter;


	double dicriminant = (b * b) - (4*a*c);

	if (dicriminant < 0)
	{
		return(0);
	}
//	printf("this t_cylinder %f\n", dicriminant);
	double t1 = (-b - sqrt(dicriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(dicriminant)) / (2.0 * a);
	t_vector point1 = add(ray.origin, multiply(ray.direction, t1));
	t_vector point2 = add(ray.origin, multiply(ray.direction, t2));
	double h1 = dot_product(substract(point1, cylinder.geometric_center), cylinder.direction);
	double h2 = dot_product(substract(point2, cylinder.geometric_center), cylinder.direction);
//	printf("this t_cylinder %f\n", h1);
	if (t1 > 0.0001 && h1 > 0.0 && h1 <= cylinder.height)
	{
            *t = t1;
	    return 1;
	}
	if (t2 > 0.0001 && h2 > 0.0 && h2 <= cylinder.height)
	{
            *t = t2;
	    return 1;
	}
	return (0);
}

void calculate_diffuse_cy(t_vector p, t_vector n, t_parameters *vars , t_cylinder cylinder)
{
	t_vector lightDirection = normalize(substract(vars->light.position , p)); // Direction to the spotlight

    double cosAngle = dot_product(n, lightDirection);
    if (cosAngle > 0.0)
    {
	    if (!shadowed(vars, p, vars->light))
		    vars->color = color_add(vars->color, color_multiply(cylinder.color, cosAngle * vars->light.brightness));
    }
}

t_vector  cy_normal(t_vector p, t_cylinder cylinder)
{
    t_vector cp = substract(p , cylinder.geometric_center);
    double projection = dot_product(cp, cylinder.direction);
    t_vector alongAxis = multiply(cylinder.direction , projection);
    return ( normalize(substract(cp, alongAxis)));
}

int	calculate_cylinder_color(t_ray ray, t_parameters *vars, t_cylinder cylinder, long double t_cylinder)
{
	calculate_ambient(vars);

	t_vector intersection = add(ray.origin , multiply(ray.direction ,t_cylinder));
	t_vector cylinder_normal = cy_normal(intersection, cylinder); 

//	printf("this t_cylinder %f\n", t_cylinder);
	calculate_diffuse_cy(intersection, cylinder_normal, vars, cylinder);
	return ( (unsigned)vars->color.r << 16 | (unsigned)vars->color.g << 8 | (unsigned)vars->color.b);
}
