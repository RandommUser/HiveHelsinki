/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:28:31 by phakakos          #+#    #+#             */
/*   Updated: 2020/09/15 13:28:32 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include "libft.h"

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>

	# include <stdio.h>

# define ESC_KEY 53
# define PG_UP 116
# define PG_DW 121

# define AR_UP 126
# define AR_DW 125
# define AR_LF 123
# define AR_RG 124

# define NUM_1 83
# define NUM_2 84
# define NUM_4 86
# define NUM_6 88
# define NUM_8 91
# define NUM_9 92
# define NUM_P 69
# define NUM_M 78
# define NUM_A 67

# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_B 11
# define K_LCN 256
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21
# define K_5 23
# define K_MI 27
# define K_PL 24
# define K_P 35
# define K_T 17
# define K_R 15
# define K_ENT 36
# define K_COM 43
# define K_DOT 47
# define K_COL 41
# define K_QUO 39
# define K_SBS 33
# define K_SBC 30
# define K_TAB 48

# define MOU_L 1
# define MOU_R 2
# define MOU_S_U 5
# define MOU_S_D 4

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MIN_WIDTH 200
# define MIN_HEIGHT 100
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440

# define THREADS 1

# define ERR_MEMORY 4
# define ERR_MAP 5
# define ERR_MLX 3
# define USAGE 1
# define ERR_THREAD_VAL 2
# define ESC_EXIT 0

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	int		*img_dat;
	int		bpp;
	int		size_line;
	int		endian;
	int		height;
	int		width;
	int		mode;
	int		verbose;
}					t_mlx;


void				run_exit(int code, char *spot);

t_mlx				*mlx_start(int argc, char **argv);


#endif