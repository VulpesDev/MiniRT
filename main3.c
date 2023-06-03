/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:57:44 by tvasilev          #+#    #+#             */
/*   Updated: 2023/06/03 13:18:09 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"
#include "event_handler.h"
#include <math.h>

void	print_coord(char *name, t_point	point)
{
	printf("%s (%f, %f, %f)\n", name, point.x, point.y, point.z);
}

void	my_mlx_pixel_put_d(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x <= 0 || y >= HEIGHT || y <= 0)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

// n (plane normal vector)
// p0 (origin point of plane)
// l0 (vector origin)
// l (vector)
// t (vector distance)
int intersectPlane(const t_vector n, const t_vector p0, const t_vector l0, const t_vector l, float t)
{
    // assuming vectors are all normalized
	t_vector p0l0;
    float denom;

	denom = vect_dot(n, l);
    if (denom > 1e-6)
	{
        p0l0 = vect_sub(p0, l0);
        t = vect_dot(p0l0, n) / denom; 
        return (t >= 0);
    }
    return 0;
}

int intersectDisk(const t_vector n, const t_vector p0, const float radius, const t_vector l0, const t_vector l)
{
    float t = 500;
    if (intersectPlane(n, p0, l0, l, t)) {
        t_vector p = vect_sum(l0, vect_mult(l, t));
        t_vector v = vect_sub(p, p0);
        float d2 = vect_dot(v, v);
        return (sqrt(d2) <= radius);
     }

     return 0;
}

int	mlx_manage(t_img *data)
{

	//mouse hook
	//key hook
	mlx_key_hook(data->win_ptr, &key_handle, data);
	//any other special hooks
	mlx_hook(data->win_ptr, X_BUTTON, 0, &close_window, data);
	//put image
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	//loop
	mlx_loop(data->mlx_ptr);
	//3x destroy
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_display(data->mlx_ptr);
	//free mlx
	free(data->mlx_ptr);
	return (1);
}

void	shoot_rays(t_img *data, t_point cam, t_point p_top_l, t_point p_bot_r, t_vector n_plane, t_point c_plane)
{
	int x = p_top_l.x, y = p_top_l.y;
	t_vector ray;

	(void)data;
	while (y != p_bot_r.y)
	{
		x = p_top_l.x;
		while (x != p_bot_r.x)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 100;
			//print_coord("ray ", ray);
			ray = vect_sub(ray, cam);
			ray = vect_norm(ray);
			//print_coord("norm_ray ", ray);
			//printf("%d", intersectDisk(n_plane, c_plane, 210, cam, ray));
			if (intersectDisk(n_plane, c_plane, 210, cam, ray))
			{
				my_mlx_pixel_put_d(data, x + WIDTH/2, y + HEIGHT/2, 0xFF0000);
			}
			//printf("%d", intersectPlane(n_plane, c_plane, cam, ray, 0));
			x > p_bot_r.x ? x-- : x++;
		}
		printf("\n");
		y > p_bot_r.y ? y-- : y++;
	}
}

int	main(void)
{
	t_img	data;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");

	data.mlx_ptr = mlx;
	data.win_ptr = mlx_win;
	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);

	t_point	cam;
	t_point	canvas_center;
	t_point	p_top_left;
	t_point	p_bot_right;
	t_point plane_center;
	t_point plane_normal;


	plane_center.x = 0;
	plane_center.y = 0;
	plane_center.z = 300;

	plane_normal.x = 0;
	plane_normal.y = 0;
	plane_normal.z = 1;
	
	cam.x = 0;
	cam.y = 0;
	cam.z = 0;

	canvas_center.x = 0;
	canvas_center.y = 0;
	canvas_center.z = 100;

	p_top_left.x = canvas_center.x- WIDTH/2;
	p_top_left.y = canvas_center.y + HEIGHT/2;
	p_top_left.z = canvas_center.z;

	p_bot_right.x = canvas_center.x + WIDTH/2;
	p_bot_right.y = canvas_center.y - HEIGHT/2;
	p_bot_right.z = canvas_center.z;

	print_coord("cam", cam);
	print_coord("canvas_center", canvas_center);
	print_coord("top left point", p_top_left);
	print_coord("bot right point", p_bot_right);
	shoot_rays(&data, cam, p_top_left, p_bot_right, plane_normal, plane_center);

	mlx_manage(&data);
	return (1);
}