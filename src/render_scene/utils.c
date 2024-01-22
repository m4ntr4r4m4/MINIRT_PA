#include "ray.h"

double	ft_max(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}

double	ft_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	ft_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
