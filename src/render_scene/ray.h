#ifndef RAY_H
#define RAY_H
#include "../vector/vector.h"
#include "../parameters/parameters.h"
#include <math.h>

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_ambient {
	double ratio;
	double	r;
	double	g;
	double	b;
}			t_ambient;

typedef struct s_ablight {
	t_vec	origin;
	double ratio;
	double	r;
	double	g;
	double	b;
}			t_ablight;

typedef struct s_acamera {
	t_vec	origin;
	t_vec	direction;
	t_vec	up;
	t_vec	right;
	double	fov;
}			t_acamera;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_ray {
	t_vec	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_sp {
	t_vec	center;
	double	radius;
	int	color;
	int		r;
	int		g;
	int		b;
}			t_sp;

typedef struct s_pl {
	t_vec	point;
	t_vec	normal;
	int		r;
	int		g;
	int		b;
}			t_pl;

typedef struct s_cy {
	t_vec	center;
	t_vec	axis;
	double	diameter;
	double	height;
	int		r;
	int		g;
	int		b;
}			t_cy;

typedef struct s_acolor {
	double r;
	double g;
	double b;
} 			t_acolor;

typedef struct s_vars {
	t_acamera	camera;
	int		hook;
	t_ambient 	ambient;
	t_ablight 	light;
	t_acolor		color;

	t_sp		*spheres;
	t_pl 		*planes;
	t_cy 		*cylanders;
	size_t 		sp_size;
	size_t 		pl_size;
	size_t 		cy_size;
	double		closest_t;
	int		sphere_idx;
	int		plane_idx;
	int		cy_idx;

}				t_vars;

// PLANE FUNCTIONS
//
int	 plane_intersaction(t_vars *vars, t_ray ray, double *t, t_pl plane);
int	calculate_plane_color(t_ray ray, t_vars *vars, t_pl plane, double t_plane);
// SPHERE FUNCTIONS
//
int	 cylinder_intersaction(t_vars *vars, t_ray ray, double *t, t_cy cylinder);
int	calculate_cylinder_color(t_ray ray, t_vars *vars, t_cy cylinder, double t_cylinder);

// SPHERE FUNCTIONS
//
int	 sphere_intersaction(t_vars *vars, t_ray ray, double *t, t_sp sphere);
int	calculate_sphere_color(t_ray ray, t_vars *vars, t_sp sphere, double t_sphere);
int	shadowed(t_vars *vars, t_vec p, t_ablight light, char *add);
void	calculate_diffuse(t_vec p, t_vec n, t_vars *vars , t_sp sphere);
void	calculate_ambient(t_vars *vars);
// VECTOR FUNCTIONS
//
t_vec	at(t_ray ray, double t);
t_vec	vecplus(t_vec vec1, t_vec vec2);
t_vec	vecminus(t_vec vec1, t_vec vec2);
t_vec	vecscale(t_vec vec, double scaler);
t_vec	vecdiv(t_vec vec, double divider);
double	vecdot(t_vec vec1, t_vec vec2);
t_vec	vecnormalize(t_vec vec);
t_vec	veccross(t_vec vec1, t_vec vec2);
double	veclength(t_vec vec);
t_vec	vec(double x, double y, double z);
// MATH FUNCTIONS
//
double	ft_min(double x , double y);
double	ft_max(double x , double y);
double ft_clamp(double x , double min , double max);
// MLX FUNCTIONS
int	create_trgb(int t, int r, int g, int b);
#endif
