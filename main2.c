/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:42:10 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/02 14:53:43 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>

t_err	ft_error(char *msg, char *arg, int err_code)
{
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putchar_fd('\n', 2);
	exit (err_code);
}

void	print_coord(char *name, t_point	point)
{
	printf("%s (%f, %f, %f)\n", name, point.x, point.y, point.z);
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
    float t = 100;
    if (intersectPlane(n, p0, l0, l, t)) {
        t_vector p = vect_sum(l0, vect_mult(l, t));
        t_vector v = vect_sub(p, p0);
        float d2 = vect_dot(v, v);
        return (sqrt(d2) <= radius);
     }

     return 0;
}

void	shoot_rays(t_point cam, t_point p_top_l, t_point p_bot_r, t_vector n_plane, t_point c_plane)
{
	int x = p_top_l.x, y = p_top_l.y;
	t_vector ray;


	while (y != p_bot_r.y)
	{
		x = p_top_l.x;
		while (x != p_bot_r.x)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 1;
			//print_coord("ray ", ray);
			ray = vect_norm(ray);
			ray.z = 1;
			//print_coord("norm_ray ", ray);
			printf("%d", intersectDisk(n_plane, c_plane, 210, cam, ray));
			//printf("%d", intersectPlane(n_plane, c_plane, cam, ray, 0));
			x > p_bot_r.x ? x-- : x++;
		}
		printf("\n");
		y > p_bot_r.y ? y-- : y++;
	}
}

int	main(/*int ac, char **av*/)
{
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
	shoot_rays(cam, p_top_left, p_bot_right, plane_normal, plane_center);
	// (void) av;
	// if (ac != 2)	// shall we read from stdin if no args are given?
	// 	return (ft_error("miniRT", "bad arguments", 1));
	// if (parse_arg(av[1]))
	// 	return (1);
	return (0);
}
