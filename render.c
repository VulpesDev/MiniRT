/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/15 12:23:13 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include "matrix_math.h"
#include "vec3.h"

/**
 * range_x / WIDTH = canvas size of 1 pxl on x axis
 * range_x / WIDTH * ratio = canvas size of 1 pxl on y axis
 * added - to flip the axis
*/
// t_point_2d	to_canvas(t_pxl pxl)
// {
// 	t_point_2d	ret;
// 	float		range_x;
// 	float		ratio;

// 	range_x = CANV_MAX_X - CANV_MIN_X;
// 	ratio = WIDTH / HEIGHT;
// 	ret.x = -(range_x / WIDTH * pxl.x + CANV_MIN_X);
// 	ret.y = -(range_x / WIDTH * ratio * pxl.y + CANV_MIN_Y);
// 	return (ret);
// }

t_point_2d	to_canvas_new(t_pxl pxl, t_camera *c)
{
	t_point_2d	ret;
	float		range_x;
	float		range_y;

	range_x = c->top_right.x - c->bot_left.x;
	range_y = c->top_right.y - c->bot_left.y;
	ret.x = range_x / WIDTH * pxl.x + c->bot_left.x;
	ret.y = range_y / HEIGHT * pxl.y + c->bot_left.y;
	return (ret);
}

void	print_4x4(t_matrix_trans m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f\t", m[i][j]);
		printf("\n");
	}
	printf("\n");
}

void	set_proj_matrix(t_matrix_trans proj, t_camera *c)
{
	proj[0][0] = (2 * ZNEAR) / (c->top_right.x - c->bot_left.x);
	proj[0][1] = 0.0f;
	proj[0][2] = 0.0f;
	proj[0][3] = 0.0f;
	proj[1][0] = 0.0f;
	proj[1][1] = (2 * ZNEAR) / (c->top_right.y - c->bot_left.y);
	proj[1][2] = 0.0f;
	proj[1][3] = 0.0f;
	proj[2][0] = (c->top_right.x + c->bot_left.x) / (c->top_right.x - c->bot_left.x);
	proj[2][1] = (c->top_right.y + c->bot_left.y) / (c->top_right.y - c->bot_left.y);
	proj[2][2] = -((ZFAR + ZNEAR) / (ZFAR - ZNEAR));
	proj[2][3] = -1.0f;
	proj[3][0] = 0.0f;
	proj[3][1] = 0.0f;
	proj[3][2] = -((2 * ZFAR * ZNEAR) / (ZFAR - ZNEAR));
	proj[3][3] = 0.0f;
	print_4x4(proj);
}

/**
 * As in openGL, we state that the projection plane coinincides
 * with the near clipping plane.
 * https://www.scratchapixel.com/lessons/3d-basic-rendering
 * /perspective-and-orthographic-projection-matrix
 * /opengl-perspective-projection-matrix.html
*/
t_point_3d	world_to_cam(t_point_3d p, t_matrix_trans proj)
{
	return (transform(p, proj));
}

t_point_3d	world_to_cam_new(t_point_3d p, t_matrix transform)
{
	return (mx_mult(transform, p));
}

int	apply_ligthing_ratio(int trgb, float lighting_ratio)
{
	return (create_trgb(0, \
			lighting_ratio * ((trgb >> 16) & 0xFF),
			lighting_ratio * ((trgb >> 8) & 0xFF),
			lighting_ratio * (trgb & 0xFF)));
}

int	intersect_element(t_scene *scene, t_ray ray, int *color, float *min_t)
{
	int		i;
	int		ret;
	float	t;

	ret = 0;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		// printf("shape[%d] i: %d\n", scene->shape_count, i);
		if (scene->shape[i].intersect(scene, ray, &t, i) && t < *min_t && t > 0)
		{
			*min_t = t;
			*color = apply_ligthing_ratio(scene->shape[i].trgb, \
											sp_light_coeff(scene, t, ray, i));
			ret = 1;
		}
		i--;
	}
	return (ret);
}

// t_ray	ray_for_pixel(t_camera *c, t_pxl p)
// {
// 	float		world_x;
// 	float		world_y;
// 	t_tuple		pxl;
// 	t_tuple		origin;
// 	t_vector	direction;

// 	world_x = c->bot_left.x + (p.x * c->pixel_size);
// 	world_y = c->bot_left.y + (p.y * c->pixel_size);
// 	pxl = multiply_tp_mx(c->transform, create_point(world_x, world_y, -1));
// 	origin = multiply_tp_mx(c->transform, create_point(0, 0, 0));
// 	direction = vect_norm(vect_sub((t_vector){pxl.x, pxl.y, pxl.z},
// 				(t_vector){origin.x, origin.y, origin.z}));
// 	return ((t_ray){(t_point_3d){origin.x, origin.y, origin.z}, direction});
// }

/**
 * @returns a color as int
 * @math
 * circle = (x^2 - a) + (y^2 - b) - r^2 = 0 (a and b are the coord)
 * ray = a + bt (a: origin b: direction t: distance)
 * a : ray origin (scene->camera.pos)
 * b : ray direction (scene->camera.orientation)
 * r : radius (scene->sphere.diameter / 2)
 * t : hit distance
 * Substitute ray into circle and solve for t
 * (bx^2 + by^2 + bz^2)t^2 + (2(axbx + ayby + azbz))t
 * + (ax^2 +ay^2 + az^2 - r^2) = 0
 * Quadratic formula: (-b +- sqrt(b^2 - 4ac))/2a
 * Discriminant: b^2 - 4ac
*/
int	per_pixel(t_pxl p, t_scene *scene)
{
	t_point_2d		coord;
	t_ray			ray;
	float			t;
	int				color;
	t_point_3d		p3;

	t = RAY_LEN;
	coord = to_canvas_new(p, &scene->camera);
	p3 = (t_point_3d){coord.x, coord.y, -1.0f};
	p3 = world_to_cam_new(p3, scene->camera.transform);
	ray.origin = scene->camera.pos;
	ray.direction = vect_norm((t_vector){p3.x, p3.y, p3.z});
	// ray = ray_for_pixel(&scene->camera, p);
	if (intersect_element(scene, ray, &color, &t))
	{
		return (color);
	}
	return (apply_ligthing_ratio(scene->ambient.trgb, \
								scene->ambient.lighting_ratio));
}

/**
 * The trgb value of a pxl not intersecting a solid is each 8bit color
 * multiplied by the lighting ratio
*/
void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;
	int		color;

	data = scene->img;
	p.y = HEIGHT - 1;
	while (p.y >= 0)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			color = per_pixel(p, scene);
			my_mlx_pixel_put_d(data, p.x, p.y, color);
			p.x++;
		}
		p.y--;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

t_err	render_scene(t_scene *scene)
{
	if (!init_img(scene))
	{
		draw(scene);
		mlx_manage(scene);
		return (SUCCESS);
	}
	return (ft_error("render", "couldn't init image", MEM_FAIL, scene));
}
