#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>

void	print_err_intro(void);
void	print_err_outro(void);
int		print_err(char *msg);
int		print_err_fstr(char *msg, char *s);
int		print_err_infile(char *msg, t_data *data);
int		print_err_atline(char *msg, int i, t_data *data);

#endif
