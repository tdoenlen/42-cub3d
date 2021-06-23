#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "struct.h"
# include "mlx.h"
# include "error.h"
# include "lib.h"
# include "parsing.h"
# include "events.h"
# include "display.h"

# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PIX_NB 262144

# define FOV 60.

# define SPEED 2.5
# define RSPEED 160.

# define WALL_OFFSET 0.001

# define SIZE 0.65
# define CROUCH_SIZE 0.4
# define CROUCH_TIME 0.1

# define MMAP_MARGIN 0.05
# define MMAP_SIZE 0.4
# define MMAP_CLR_WALL 0x777777
# define MMAP_CLR_FLOOR 0x333333
# define MMAP_CLR_PLR 0x9F4545

#endif
