# Files
SRCS	= \
	data/free.c \
	data/init.c \
	error/error.c \
	error/format.c \
	lib/vect3/calc.c \
	lib/vect3/init.c \
	lib/vect3/rotate.c \
	lib/allocation.c \
	lib/char.c \
	lib/color.c \
	lib/extension.c \
	lib/get_next_line.c \
	lib/img.c \
	lib/lset.c \
	lib/str.c \
	parse/elements/color.c \
	parse/elements/elements.c \
	parse/elements/resolution.c \
	parse/elements/texture.c \
	parse/elements/scene.c \
	parse/map/map_utils.c \
	parse/map/map.c \
	parse/map/planes.c \
	parse/file.c \
	window/display/cast_ray/cast_ray.c \
	window/display/cast_ray/init_cast_info.c \
	window/display/minimap.c \
	window/display/screen_rays.c \
	window/display/update_minimap.c \
	window/display/update_vs.c \
	window/display/update.c \
	window/input/check_pressed_keys.c \
	window/input/events.c \
	main.c
SRCS	:= $(SRCS:%.c=srcs/%.c)
OBJS	= $(SRCS:%.c=%.o)
INCS	= \
	headers/cub3d.h \
	headers/display.h \
	headers/error.h \
	headers/events.h \
	headers/lib.h \
	headers/parsing.h \
	headers/struct.h \
	mlx/mlx.h
NAME	= cub3D

# mlx files
MLX_PATH	= mlx/
MLX			= $(MLX_PATH)libmlx.dylib
MLX_MODULES	= mlx_image.swift mlx_window.swift mlx_init.swift
MLX_SRCS	= interface.swift $(MLX_MODULES)
MLX_SRCS	:= $(MLX_SRCS:%.swift=$(MLX_PATH)%.swift)
MLX_CSRCS	= mlx_xpm.c mlx_png.c mlx_string_put.c
MLX_CSRCS	:= $(MLX_CSRCS:%.c=$(MLX_PATH)%.c)
MLX_OBJS	= \
	$(MLX_MODULES:.swift=.swiftmodule) \
	$(MLX_SRCS:.swift=.o) \
	$(MLX_CSRCS:.c=.o)

# Compilation
CC		= gcc
LDFLAGS	= -Lmlx -Iheaders -Imlx -lmlx -march=native
CFLAGS	= -Wall -Wextra -Werror -Iheaders -Imlx -Ofast -march=native

# Colors
ERASE		= \033[2K\r
RED			= \033[31m
GREEN		= \033[32m
CYAN		= \033[36m
WHITE		= \033[37m
DEFAULT		= \033[0m
BOLD		= \033[1m

# Messages
INTRO_W		= $(BOLD)$(ERASE)$(RED)$(NAME)$(WHITE) : 
INTRO_G		= $(INTRO_W)$(GREEN)
E			= $(DEFAULT)
FORM_NAME	= $(CYAN)'$(NAME)'$(WHITE)
$(shell printf "" > .compiled_files)

# Norme
NORME_DIRS	= srcs headers

$(NAME):	$(OBJS) $(MLX)
	count=$$(cat .compiled_files | wc -w | sed -e 's/ //g'); \
	if [ "$$count" = "0" ]; then \
		printf "$(INTRO_W)No object compiled$(E)\n"; \
	else \
		printf "$(INTRO_G)$$count object(s) compiled$(E)\n"; \
	fi
	rm -rf .compiled_files
	printf "$(INTRO_W)Compiling $(CYAN)'$@'$(WHITE)...$(E)"
	$(CC) $(LDFLAGS) $^ -o $@
	printf "$(INTRO_G)Made$(E)\n"

bonus:	$(NAME)

all:	$(NAME)

%.o:	%.c $(INCS)
	printf "$(INTRO_W)Compiling $(CYAN)'$@'$(WHITE)...$(E)"
	$(CC) $(CFLAGS) -c $< -o $@
	echo $@ >> .compiled_files

$(MLX):
	make -C $(MLX_PATH)

clean:
	printf "$(INTRO_W)Removing files...$(E)"
	count=$$(rm -rfv $(OBJS) | wc -w | sed -e 's/ //g'); \
	if [ "$$count" = "0" ]; then \
		printf "$(INTRO_W)No file$(E)\n"; \
	else \
		printf "$(INTRO_G)$$count file(s) deleted$(E)\n"; \
	fi
	$(MAKE) -C $(MLX_PATH) $@

fclean:	clean
	printf "$(INTRO_W)Removing $(FORM_NAME)...$(E)"
	count=$$(rm -rfv $(NAME) | wc -w | sed -e 's/ //g'); \
	if [ "$$count" = "0" ]; then \
		printf "$(INTRO_W)No file $(FORM_NAME)$(E)\n"; \
	else \
		printf "$(INTRO_G)$(FORM_NAME)$(GREEN) deleted$(E)\n"; \
	fi
	$(MAKE) -C $(MLX_PATH) $@

re:	fclean all

n:
	printf "Checking norme in $$(printf "$(NORME_DIRS)" | sed "s/ /, /g").\n"
	NORM=$$(/usr/bin/norminette $(NORME_DIRS)); \
	NORM_ERR=$$(printf "$$NORM" | grep -e Error\: | wc -l \
			| sed "s/ //g"); \
	if [ "$$NORM_ERR" = "0" ]; then \
			printf "Everything seems normed!\n"; \
	else \
			NORM_FIL=$$(printf "$$NORM" | grep -e Error\! \
					| wc -l | sed "s/ //g"); \
			printf "\n\t$$NORM_ERR error(s) in $$NORM_FIL file(s):\n\n"; \
			printf "$$(printf "$$NORM" | grep -e Error)\n"; \
	fi

.PHONY:		all clean fclean re n
.SILENT:	$(NAME) $(OBJS) $(MLX) all clean fclean n
