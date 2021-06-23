int	get_color_from_argb(int a, int r, int g, int b)
{
	return (a << 0x18 | r << 0x10 | g << 0x08 | b << 0x00);
}

int	get_t_from_color(unsigned int color)
{
	return (color & (0xFF << 0x18));
}

int	get_r_from_color(unsigned int color)
{
	return (color & (0xFF << 0x10));
}

int	get_g_from_color(unsigned int color)
{
	return (color & (0xFF << 0x08));
}

int	get_b_from_color(unsigned int color)
{
	return (color & (0xFF << 0x00));
}
