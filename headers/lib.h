#ifndef LIB_H
# define LIB_H

int		get_next_line(int fd, char **line);

int		ft_strlen(char *s);
char	to_upper(char c);
int		is_in_str(char c, char *s);
int		str_is_eq(char *s1, char *s2);
int		ft_atoi(char *s);
int		get_ni(char *s, int i);
int		check_ext(char *file, char *ext, char is_case_s);

int		get_color_from_argb(int a, int r, int g, int b);
int		get_t_from_color(unsigned int color);
int		get_r_from_color(unsigned int color);
int		get_g_from_color(unsigned int color);
int		get_b_from_color(unsigned int color);

void	*safe_free(void *ptr);
char	**safe_free_str_tab(char **tab);
char	*set_str_len(char *str, int new_len);
char	**append_str_tab(char **tab, char *str);
char	**pop_str_tab(char **tab);

int		format_img(t_img *img, int w, int h);
void	img_addr_pixel_put(t_img *img, int clr, int i);
void	img_pixel_put(t_img *img, int clr, int x, int y);
int		get_img_addr_pixel(t_img *img, int i);
int		get_img_pixel(t_img *img, int x, int y);

#endif
