/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/22 18:05:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix_math.h"
#include <time.h>

/**
 * @brief creates a ray from the camera to the canvas
*/
t_ray	create_cam_ray(t_camera *c, double int_x, double int_y)
{
	t_ray	ray;
	t_vec3	pxl_x;
	t_vec3	pxl_y;
	t_vec3	pxl_pos;

	ray.origin = c->pos;
	pxl_x = vec3_mult(c->pxl_size_hor, int_x);
	pxl_y = vec3_mult(c->pxl_size_ver, int_y);
	pxl_pos = vec3_sum(c->viewport_top_left, \
		vec3_mult(c->right, vec3_len(pxl_x)));
	pxl_pos = vec3_sum(pxl_pos, vec3_mult(vec3_inv(c->up), vec3_len(pxl_y)));
	ray.direction = vec3_sub(pxl_pos, ray.origin);
	ray.direction = vec3_unit(ray.direction);
	return (ray);
}

/**
 * @returns a color as int
*/
int	per_pixel(t_pxl p, t_scene *scene)
{
	t_ray		r;
	t_color		c;
	t_vec3		tot_col;
	double		rnd;
	static int	i = 0;

	tot_col = (t_vec3){0, 0, 0};
	while (i++ < RAYS_PER_PIXEL)
	{
		srand(time(NULL));
		rnd = (double)rand() / RAND_MAX;
		r = create_cam_ray(&scene->camera, p.x + rnd * 0.5f, p.y + rnd * 0.5f);
		c = ray_color(scene, r);
		tot_col = vec3_sum(tot_col, (t_vec3){c.r, c.g, c.b});
	}
	tot_col = vec3_div(tot_col, i);
	c = apply_light_to_color((t_color){0, tot_col.x, tot_col.y, tot_col.z}, \
		1 + scene->ambient.lighting_ratio);
	i = 0;
	return (convert_trgb(c));
}

void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;
	int		c;
	t_shape	*shape_ins;

	data = scene->img;
	cam_setup(&scene->camera);
	shape_ins = check_inside(scene);
	p.y = 0;
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			if (shape_ins)
				c = shape_ins->trgb;
			else
				c = per_pixel(p, scene);
			my_mlx_pixel_put_d(data, p.x, p.y, c);
			p.x++;
		}
		p.y++;
		print_progress((double)p.y / HEIGHT);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

t_err	render_scene(t_scene *scene)
{
	if (!init_img(scene))
	{
		draw(scene);
		printf("\n");
		mlx_manage(scene);
		return (SUCCESS);
	}
	return (ft_error("render", "couldn't init image", MEM_FAIL, scene));
}
