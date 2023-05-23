/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:45:57 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/23 14:10:47 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
# define WIDTH 500
# define HEIGHT 500

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point {
	int	x;
	int	y;
}				t_point;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	setup(void **mlx, void **mlx_win, t_data *img)
{
	*mlx = mlx_init();
	*mlx_win = mlx_new_window(*mlx, WIDTH, HEIGHT, "miniRT");
	img->img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
}

void	put_rect(t_point p1, t_point p2,  t_data *img, int color)
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if (x > p1.x && y > p1.y && x < p2.x && y < p2.y)
			 my_mlx_pixel_put(img, x, y, color);
		}
	}
	
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point p1, p2;

	p1.x = 10;
	p1.y = 10;
	p2.x = 150;
	p2.y = 200;
	setup(&mlx, &mlx_win, &img);
	put_rect(p1, p2, &img, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
