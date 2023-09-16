/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:41:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/16 23:18:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix_math.h"

#ifdef DEBUG

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
#endif

/**
 * @brief creates a ray from the camera to the canva
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
 * Former intersect_element function
 * @brief Checks if the ray hits any element in the scene
 * In the scene->shape[i].hit(&scene->shape[i], ray, rec) call
 * the ray is updated with hit distance, hit point, normal and color
*/
bool	hit_element(t_scene *scene, t_ray ray, t_hit_record *rec)
{
	bool	hit_anything;
	int		i;

	hit_anything = false;
	rec->t = RAY_LEN;
	i = scene->shape_count - 1;
	while (i >= 0)
	{
		if (scene->shape[i].hit(&scene->shape[i], ray, rec) && rec->t > EPSILON)
		{
			hit_anything = true;
		}
		i--;
	}
	return (hit_anything);
}

/**
 * @brief Creates a hit record that gets updated if the ray hits an element
 * @returns the color of the hit element
*/
t_color	ray_color(t_scene *scene, t_ray r)
{
	double			light;
	t_hit_record	rec;

	if (hit_element(scene, r, &rec))
	{
		light = light_coeff(scene, &rec);
		// if (light < 0 || light > 1)
		// 	printf("Light out of bound %f\n", light); // remember to remove
		return (apply_light_to_color(rec.color, light));
	}
	return (convert_color(scene->ambient.trgb));
}


// /**
//  * @brief Returns a hit record for a ray that doesn't hit anything
// */
// t_hit_record	miss(t_ray r)
// {

// };


// /**
//  * @brief Returns the closest hit record
//  * @param r: ray
//  * @param t: hit distance
//  * @param i: index of the shape
// */
// t_hit_record	closest_hit(t_ray r, double t, uint32_t i)
// {

// };

// /**
//  * @brief Returns a hit point payload
//  * @param r: ray
// */
// t_hit_record	trace_ray(t_scene *s, t_ray r)
// {
// 	t_hit_record	rec;

// 	if (hit_element(s, r, &rec))
// 	{

// 	}
// };

/**
 * @returns a color as int
 * @math:
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
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
*/
int	per_pixel(t_pxl p, t_scene *scene)
{
	t_ray	r;
	t_color	c;

	r = create_cam_ray(&scene->camera, p.x, p.y);
	c = ray_color(scene, r);
	c = apply_light_to_color(c, 1 + scene->ambient.lighting_ratio);
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
