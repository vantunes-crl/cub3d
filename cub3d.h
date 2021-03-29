#ifndef CUB3D_H
# define CUB3D_H


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17

typedef struct keys {

	int y;
	int x;

}	t_keys;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}
               t_data;
#endif