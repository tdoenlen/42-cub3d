#include "cub3d.h"

void	vect3_mult_k(t_vect3 *vect3, double k)
{
	vect3->x *= k;
	vect3->y *= k;
	vect3->z *= k;
}
