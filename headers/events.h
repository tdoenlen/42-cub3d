#ifndef EVENTS_H
# define EVENTS_H

# include "cub3d.h"

enum
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_ENTER = 36,
	KEY_M = 46,
	KEY_SPACE = 49,
	KEY_ESC = 53,
	KEY_NPENTER = 76,
	KEY_NP0 = 82,
	KEY_NP1 = 83,
	KEY_NP2 = 84,
	KEY_NP3 = 85,
	KEY_NP4 = 86,
	KEY_NP5 = 87,
	KEY_NP6 = 88,
	KEY_NP7 = 89,
	KEY_NP8 = 91,
	KEY_NP9 = 92,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
	KEY_LCTRL = 256,
	KEY_LSHIFT = 257,
	KEY_RSHIFT = 258,
	KEY_CMD = 259,
	KEY_LALT = 261,
	KEY_RALT = 262,
	KEY_RCTRL = 269,
	KEY_CAPS = 272
};

enum
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
};

int		quit(t_data *data);
int		key_pressed(int key, t_data *data);
int		key_released(int key, t_data *data);

void	check_pressed_keys(t_data *data);

#endif
