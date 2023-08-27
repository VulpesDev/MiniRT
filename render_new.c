/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:51:17 by tfregni           #+#    #+#             */
/*   Updated: 2023/08/27 13:56:36 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix_math.h"

/* Here is the explanation for the code below:
1. We are dividing x and y by 4 because we want to cast 4 rays per pixel
2. We are adding 0.5 to the x and y to get the middle of the pixel
3. We are subtracting 1 from the y to get the top of the pixel
4. We are multiplying the x by the aspect ratio and the fov
5. We are multiplying the y by the fov
6. We are returning the vector */
t_vec3	ray_pixel_to_world(t_camera *c, int x, int y)
{
	double	aspect_ratio;
	double	fov;
	double	p_x;
	double	p_y;

	fov = tanf((double)c->fov / 2 * M_PI / 180);
	printf("fov: %f\n", fov);
	aspect_ratio = (double)WIDTH / HEIGHT;
	p_x = (2 * (x + 0.5) / WIDTH - 1) * aspect_ratio * fov;
	p_y = (1 - 2 * (y + 0.5) / HEIGHT) * fov;
	return (vec3(-p_x, p_y, 1));
}

/* Here is the explanation for the code below:
1. We calculate the ray's direction in world coordinate by using the
camera's matrix.
2. We calculate the ray's origin in world coordinate by using the camera's
position.
3. We calculate the ray's direction by substracting the ray's origin to the
ray's destination.
4. We normalize the ray's direction.
5. We return the ray. */
t_ray	get_ray(t_camera *c, int x, int y)
{
	t_vec3	shooting_direction;
	t_ray	ray;

	if (c->vert_up.x == 0 && (c->vert_up.y == 1
			|| c->vert_up.y == -1))
		c->vert_up.x = EPSILON;
	shooting_direction = ray_pixel_to_world(c, x, y);
	shooting_direction = mx_mult(c->mx, shooting_direction);
	shooting_direction = vec3_sub(shooting_direction, c->pos);
	shooting_direction = vec3_unit(shooting_direction);
	ray.origin = c->pos;
	ray.direction = shooting_direction;
	return (ray);
}

/* Here is the explanation for the code below:
1. We create a vector (random) pointing upwards (0, 1, 0).
2. We calculate the vector pointing to the right of the camera by doing the
cross product between the random vector and the normal vector of the camera.
3. We normalize the vector.
4. We calculate the vector pointing upwards by doing the cross product between
the normal vector of the camera and the vector pointing to the right of the
camera.
5. We normalize the vector.
6. If the length of the vector pointing upwards is equal to 0, it means that
the camera is pointing upwards and not to the direction of the normal vector
of the camera. In this case we do the same thing as in step 1 to 5 but with
the z-axis (0, 0, 1) instead of the y-axis (0, 1, 0).
7. The two vectors calculated (right and up) are the two vectors that will be
used to calculate the rays for each pixel of the image. */
void	calculate_camera_vectors(t_scene *s, t_vec3 *right, t_vec3 *up)
{
	t_vec3	random;

	random = vec3(0, 1, 0);
	*right = vec3_cross(random, s->camera.vert_up);
	*right = vec3_unit(*right);
	*up = vec3_cross(s->camera.vert_up, *right);
	*up = vec3_unit(*up);
	if (vec3_len_squared(*up) == 0)
	{
		random = vec3(0, 0, 1);
		*right = vec3_cross(random, s->camera.vert_up);
		*right = vec3_unit(*right);
		*up = vec3_cross(s->camera.vert_up, *right);
	}
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

/* Here is the explanation for the code below:
1. The first thing to do is to calculate the right vector. This is
done by taking the cross product of the up vector and the look vector.
2. The second step is to calculate the up vector. This is done by taking
the cross product of the look vector and the right vector.
3. The third step is to fill in the rest of the matrix. The right, up
and look vectors are the first three rows of the matrix. The fourth
row contains the translation vector. */
void	matrix_look_at(t_scene *s)
{
	t_camera	*c;

	c = &s->camera;
	calculate_camera_vectors(s, &c->right, &c->up);
	c->mx.size = 16;
	c->mx.matrix[0][0] = c->right.x;
	c->mx.matrix[0][1] = c->right.y;
	c->mx.matrix[0][2] = c->right.z;
	c->mx.matrix[0][3] = 0;
	c->mx.matrix[1][0] = c->up.x;
	c->mx.matrix[1][1] = c->up.y;
	c->mx.matrix[1][2] = c->up.z;
	c->mx.matrix[1][3] = 0;
	c->mx.matrix[2][0] = c->vert_up.x;
	c->mx.matrix[2][1] = c->vert_up.y;
	c->mx.matrix[2][2] = c->vert_up.z;
	c->mx.matrix[2][3] = 0;
	c->mx.matrix[3][0] = c->pos.x;
	c->mx.matrix[3][1] = c->pos.y;
	c->mx.matrix[3][2] = c->pos.z;
	c->mx.matrix[3][3] = 1;
}

int	per_pixel(t_pxl p, t_scene *scene)
{
	t_ray	ray;
	int		color;
	float	t;

	t = RAY_LEN;
	ray = get_ray(&scene->camera, p.x, p.y);
	vec3_print(ray.direction);
	if (intersect_element(scene, ray, &color, &t))
	{
		return (color);
	}
	return (apply_lighting_ratio(scene->ambient.trgb, \
								scene->ambient.lighting_ratio));
}

void	draw(t_scene *scene)
{
	t_pxl	p;
	t_img	*data;
	int		color;

	data = scene->img;
	matrix_look_at(scene);
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIDTH)
		{
			color = per_pixel(p, scene);
			my_mlx_pixel_put_d(data, p.x, p.y, color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}
