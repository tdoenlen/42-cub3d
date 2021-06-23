#ifndef DISPLAY_H
# define DISPLAY_H

# include "cub3d.h"

int				update(t_data *data);
unsigned int	cast_ray_from_pos(t_vect3 *dir, t_data *data);
int				calc_base_screen_rays(t_data *data);
int				calc_minimap(t_data *data);
void			calc_screen_rays(t_data *data);
void			update_minimap(t_data *data);
void			update_vs(t_data *data);

void			init_cast_info(t_cast_info *info, t_vect3 *dir, t_data *data);

#endif