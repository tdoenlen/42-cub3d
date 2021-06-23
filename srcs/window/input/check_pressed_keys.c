#include "cub3d.h"

static void	move_pos(t_vect3 *move, t_data *data)
{
	data->pos.x += move->x;
	if (data->map[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
	{
		if (move->x >= 0.)
			data->pos.x = floor(data->pos.x) - WALL_OFFSET;
		else
			data->pos.x = floor(data->pos.x + 1.) + WALL_OFFSET;
	}
	data->pos.y += move->y;
	if (data->map[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
	{
		if (move->y >= 0.)
			data->pos.y = floor(data->pos.y) - WALL_OFFSET;
		else
			data->pos.y = floor(data->pos.y + 1.) + WALL_OFFSET;
	}
}

static void	check_move_keys(t_data *data)
{
	t_vect3	move;
	double	speed;

	speed = SPEED;
	if (lset_has_val(data->pk, KEY_LALT))
		speed *= 0.3;
	else if (lset_has_val(data->pk, KEY_LSHIFT))
		speed *= 2.;
	set_vect3(&move, 0., 0., 0.);
	if (lset_has_val(data->pk, KEY_W))
		move.y -= speed * data->delta;
	if (lset_has_val(data->pk, KEY_S))
		move.y += speed * data->delta;
	if (lset_has_val(data->pk, KEY_A))
		move.x -= speed * data->delta;
	if (lset_has_val(data->pk, KEY_D))
		move.x += speed * data->delta;
	move = get_vect3_rotate_z(&move, cos(data->za), sin(data->za));
	move_pos(&move, data);
}

static void	check_rotate_keys(t_data *data)
{
	if (lset_has_val(data->pk, KEY_LEFT))
	{
		data->za -= RSPEED * M_PI_4 / 30 * data->delta;
	}
	if (lset_has_val(data->pk, KEY_RIGHT))
	{
		data->za += RSPEED * M_PI_4 / 30 * data->delta;
	}
}

void	check_pressed_keys(t_data *data)
{
	if (lset_has_val(data->pk, KEY_LALT))
		data->pos.z = data->pos.z
			+ (data->delta / CROUCH_TIME) * (CROUCH_SIZE - SIZE);
	else
		data->pos.z = data->pos.z
			+ (data->delta / CROUCH_TIME) * (SIZE - CROUCH_SIZE);
	if (data->pos.z < CROUCH_SIZE)
		data->pos.z = CROUCH_SIZE;
	if (data->pos.z > SIZE)
		data->pos.z = SIZE;
	check_move_keys(data);
	check_rotate_keys(data);
}
