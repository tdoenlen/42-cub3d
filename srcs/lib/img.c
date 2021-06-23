#include "cub3d.h"

int	format_img(t_img *img, int w, int h)
{
	if (img->ptr == NULL)
		return (-1);
	img->w = w;
	img->h = h;
	img->addr = mlx_get_data_addr(img->ptr, &(img->p), &(img->l), &(img->e));
	img->p /= 8;
	printf("pixel bytes: %d, line size: %d\n", img->p, img->l);
	return (0);
}

void	img_addr_pixel_put(t_img *img, int clr, int i)
{
	*((unsigned int *)
			(img->addr + (i / img->w) * img->l + (i % img->w) * img->p)) = clr;
}

void	img_pixel_put(t_img *img, int clr, int x, int y)
{
	*((unsigned int *)(img->addr + y * img->l + x * img->p)) = clr;
}

int	get_img_addr_pixel(t_img *img, int i)
{
	return (*((int *)
			(img->addr + (i / img->w) * img->l + (i % img->w) * img->p)));
}

int	get_img_pixel(t_img *img, int x, int y)
{
	return (*((int *)(img->addr + y * img->l + x * img->p)));
}
