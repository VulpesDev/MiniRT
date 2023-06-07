/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:24:43 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/07 13:54:02 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Prints the current status of the unique elements flag
*/
// static void	print_flag(int *flag)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 3)
// 		ft_printf("%d\t", flag[i++]);
// 	ft_printf("\n");
// }

/**
 * I pass it a triple flag as int array to check that the unique
 * elements are not set multiple times.
*/
t_err	handle_unique(t_scene *scene, char **el, uint8_t *flag)
{
	if (!ft_strcmp(el[0], "A"))
	{
		ft_printf("Ambient\n");
		if (flag[AMBIENT])
			return (ft_warning("Ambient already set", NULL, INVALID_DUP));
		if (validate_ambient(scene, el) == SUCCESS)
			flag[AMBIENT] = 1;
	}
	else if (!ft_strcmp(el[0], "C"))
	{
		ft_printf("Camera\n");
		if (flag[CAMERA])
			return (ft_warning("Camera already set", NULL, INVALID_DUP));
		if (validate_camera(scene, el) == SUCCESS)
			flag[CAMERA] = 1;
	}
	else if (!ft_strcmp(el[0], "L"))
	{
		ft_printf("Light\n");
		if (flag[LIGHT])
			return (ft_warning("Light already set", NULL, INVALID_DUP));
		if (validate_light(scene, el) == SUCCESS)
			flag[LIGHT] = 1;
	}
	else
		ft_printf("Element not recognized\n");
	return (SUCCESS);
}

/**
 * In case of invalid solid we throw a warning
 * and move on to the next line
*/
void	handle_solid(t_scene *scene, char **el)
{
	if (!ft_strcmp(el[0], "sp"))
	{
		if (!validate_sphere(scene, el))
			ft_printf("Sphere\n");
	}
	else if (!ft_strcmp(el[0], "pl"))
	{
		if (!validate_plane(scene, el))
			ft_printf("Plane\n");
	}
	else if (!ft_strcmp(el[0], "cy"))
	{
		if (!validate_cylinder(scene, el))
			ft_printf("Cylinder\n");
	}
	else
		ft_printf("Solid not recognized\n");
}

/**
 * Added support to comment # to make testing scenes easier
 * @returns 0 for success, > 0 for err_code
*/
int	parse_element(t_scene *scene, char *line, uint8_t *flag)
{
	char	**el;

	el = ft_split_by_sep(line, SPACE);
	if (!el)
		return (ft_warning("invalid element: ", el[0], \
							INVALID_ELEMENT));
	if (el[0] && el[0][0] && el[0][0] != '#')
	{
		if (ft_isalpha(el[0][0]) && el[0][0] <= 'Z')
			handle_unique(scene, el, flag);
		else if (ft_isalpha(el[0][0]) && el[0][0] >= 'a')
			handle_solid(scene, el);
	}
	ft_free_str_arr(el);
	return (SUCCESS);
}

/**
 * @returns 0 for success, > 0 for err_code
 * It will return an error if the scene doesn't have
 * an Ambient or a Light or a Camera
*/
int	parse_args(t_scene *scene, char *filename)
{
	int					fd;
	char				*line;
	static uint8_t		flag[3] = {0};

	if (ft_strncmp(".rt", &filename[ft_strlen(filename) - 3], 4))
		return (ft_warning("invalid file ext", NULL, FILE_EXTENSION));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_warning("could not open", filename, INVALID_FILE));
	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
			continue ;
		parse_element(scene, line, flag);
	}
	close(fd);
	if (flag[0] && flag[1] && flag[2])
	{
		// while ((*scene->sp).diameter)
		// {
		// 	printf("SPHERE\n");
		// 	scene->sp++;
		// }
		// exit (printf("Render\n"));
		return (render_scene(scene));
	}
	return (ft_warning("cannot render", "missing element", MISS_UNIQUE));
}
