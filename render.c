/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/07/31 16:00:23 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
// #include "vector_math.h"
#include "matrix_math.h"

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

// t_point_2d	to_canvas_new(t_pxl pxl, t_camera *c)
// {
// 	t_point_2d	ret;
// 	float		range_x;
// 	float		range_y;

// 	range_x = c->top_right.x - c->bot_left.x;
// 	range_y = c->top_right.y - c->bot_left.y;
// 	ret.x = range_x / WIDTH * pxl.x + c->bot_left.x;
// 	ret.y = range_y / HEIGHT * pxl.y + c->bot_left.y;
// 	return (ret);
// }

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

// void	set_proj_matrix(t_matrix_trans proj, t_camera *c)
// {
// 	proj[0][0] = (2 * ZNEAR) / (c->top_right.x - c->bot_left.x);
// 	proj[0][1] = 0.0f;
// 	proj[0][2] = 0.0f;
// 	proj[0][3] = 0.0f;
// 	proj[1][0] = 0.0f;
// 	proj[1][1] = (2 * ZNEAR) / (c->top_right.y - c->bot_left.y);
// 	proj[1][2] = 0.0f;
// 	proj[1][3] = 0.0f;
// 	proj[2][0] = (c->top_right.x + c->bot_left.x) / (c->top_right.x - c->bot_left.x);
// 	proj[2][1] = (c->top_right.y + c->bot_left.y) / (c->top_right.y - c->bot_left.y);
// 	proj[2][2] = -((ZFAR + ZNEAR) / (ZFAR - ZNEAR));
// 	proj[2][3] = -1.0f;
// 	proj[3][0] = 0.0f;
// 	proj[3][1] = 0.0f;
// 	proj[3][2] = -((2 * ZFAR * ZNEAR) / (ZFAR - ZNEAR));
// 	proj[3][3] = 0.0f;
// 	print_4x4(proj);
// }

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

t_color	apply_light_to_color(t_color c, double light)
{
	// printf("color: %f %f %f\n", c.r, c.g, c.b);
	return (color(0.0, c.r * light, c.g * light, c.b * light));
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

/**
 * @brief converts an int in trgb format to a color struct with double values
 * in range [0, 1]
 * @param trgb int in trgb format
 * @return color struct
*/
t_color	convert_color(int trgb)
{
	t_color	c;

	c.t = ((trgb >> 24) & 0xFF) / 255.999;
	c.r = ((trgb >> 16) & 0xFF) / 255.999;
	c.g = ((trgb >> 8) & 0xFF) / 255.999;
	c.b = (trgb & 0xFF) / 255.999;
	return (c);
}

/**
 * @brief converts a color struct with double values in range [0, 1]
 * to an int in trgb format
 * @param c color struct
 * @return int in trgb format
*/
int	convert_trgb(t_color c)
{
	int		t;
	int		r;
	int		g;
	int		b;

	t = (int)(c.t * 255.999);
	r = (int)(c.r * 255.999);
	g = (int)(c.g * 255.999);
	b = (int)(c.b * 255.999);
	return (t << 24 | r << 16 | g << 8 | b);
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

t_ray	create_cam_ray(t_camera *c, double u, double v)
{
	t_ray	ray;
	t_vec3	temp;
	t_vec3	gradient_hor;
	t_vec3	gradient_ver;

	ray.origin = c->pos;
	gradient_hor = vec3_mult(c->horizontal, u);
	gradient_ver = vec3_mult(c->vertical, v);
	temp = vec3_sum(gradient_hor, gradient_ver);
	ray.direction = vec3_sub(c->lower_left_corner, ray.origin);
	ray.direction = vec3_sum(ray.direction, temp);
	return (ray);
}

bool	hit_element(t_scene *scene, t_ray ray, t_hit_record *rec)
{
	bool	hit_anything;
	int		i;

	hit_anything = false;
	rec->t = RAY_LEN;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].hit(&scene->shape[i], ray, rec) && rec->t > 0.001f)
		{
			hit_anything = true;
		}
		i--;
	}
	return (hit_anything);
}

/**
 * A lerp is always of the form
 * blendedValue=(1−t)⋅startValue+t⋅endValue,
*/
t_color	ray_color(t_scene *scene, t_ray r)
{
	t_vec3			unit_direction;
	double			t;
	t_vec3			blend;
	t_hit_record	rec;

	// return (color(0.5, (normal.x + 1) * 0.5, (normal.y + 1) * 0.5, (normal.z + 1) * 0.5));
	if (hit_element(scene, r, &rec))
	{
		double light = ft_fmax((vec3_dot(rec.normal, vec3_inv(vec3_unit(scene->light.pos)))), 0.0f);
		// rec.trgb = ft_fmax(rec.trgb * light, 0.0f);
		return (apply_light_to_color(rec.color, light));
	}
	unit_direction = vec3_unit(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	blend = vec3_sum(vec3_mult(vec3(1, 1, 1), 1.0 - t), vec3_mult(vec3(0.5, 0.7, 1.0), t));
	return (color(0, blend.x, blend.y, blend.z));
}

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
	double	u;
	double	v;
	t_ray	r;
	t_color	c;

	// Between 0 and 1
	u = (double)p.x / (WIDTH - 1);
	v = (double)p.y / (HEIGHT - 1);
	r = create_cam_ray(&scene->camera, u, v);
	c = ray_color(scene, r);
	return (convert_trgb(c));
}

/**
 * The trgb value of a pxl not intersecting a solid is each 8bit color
 * multiplied by the lighting ratio
*/
void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;
	int		c;

	data = scene->img;
	cam_setup(&scene->camera);
	p.y = 0;
	while (p.y < HEIGHT)
	{
		// printf("Scanlines remaining: %d\n", HEIGHT - 1 - p.y);
		p.x = 0;
		while (p.x < WIDTH)
		{
			// c = convert_trgb(color(0, (double)p.x / (WIDTH - 1), (double)p.y / (HEIGHT - 1), 0.25));
			c = per_pixel(p, scene);
			my_mlx_pixel_put_d(data, p.x, p.y, c);
			p.x++;
		}
		p.y++;
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
