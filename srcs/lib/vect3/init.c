#include "cub3d.h"

t_vect3	*new_null_vect3(void)
{
	t_vect3	*ret;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return (NULL);
	ret->x = 0.;
	ret->y = 0.;
	ret->z = 0.;
	return (ret);
}

t_vect3	*new_vect3(double x, double y, double z)
{
	t_vect3	*ret;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

void	set_vect3(t_vect3 *vect3, double x, double y, double z)
{
	vect3->x = x;
	vect3->y = y;
	vect3->z = z;
}
