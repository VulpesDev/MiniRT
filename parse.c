/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:24:43 by tfregni           #+#    #+#             */
/*   Updated: 2023/06/02 12:18:54 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_unique(char **el)
{
	(void) el;
	printf("UNIQUE\n");
}

void	handle_solid(char **el)
{
	(void) el;
	printf("SOLID\n");
}

int	parse_element(char *line)
{
	char	**el;

	el = ft_split_by_sep(line, SPACE);
	if (!el)
		return (ft_error("minirt: invalid element", el[0], INVALID_ELEMENT));
	if (el[0] && el[0][0])
	{
		if (ft_isalpha(el[0][0]) && el[0][0] <= 'Z')
			handle_unique(el);
		else if (ft_isalpha(el[0][0]) && el[0][0] >= 'a')
			handle_solid(el);
	}
	ft_free_str_arr(el);
	return (0);
}

int	parse_arg(char *filename)
{
	int		len;
	int		fd;
	char	*line;

	len = ft_strlen(filename);
	if (ft_strncmp(".rt", &filename[len - 3], 4))
		return (ft_error("miniRT", "invalid file extension", FILE_EXTENSION));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error("miniRT: could not open", filename, INVALID_FILE));
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
			continue ;
		parse_element(line);
		free(line);
	}
	close(fd);
	return (0);
}
