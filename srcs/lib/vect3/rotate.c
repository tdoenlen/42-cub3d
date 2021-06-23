#include "cub3d.h"

t_vect3	get_vect3_rotate_z(t_vect3 *v, double c, double s)
{
	static double	last_c = 1.;
	static double	last_s = 0.;
	t_vect3			u;

	if (isnan(c))
		c = last_c;
	else
		last_c = c;
	if (isnan(s))
		s = last_s;
	else
		last_s = s;
	u.x = v->x * c - v->y * s;
	u.y = v->x * s + v->y * c;
	u.z = v->z;
	return (u);
}

t_vect3	get_vect3_rotate_x(t_vect3 *v, double c, double s)
{
	static double	last_c = 1.;
	static double	last_s = 0.;
	t_vect3			u;

	if (isnan(c))
		c = last_c;
	else
		last_c = c;
	if (isnan(s))
		s = last_s;
	else
		last_s = s;
	u.x = v->x;
	u.y = v->y * c - v->z * s;
	u.z = v->y * s + v->z * c;
	return (u);
}
