/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:36:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/09/16 23:09:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
#include <stdio.h>

void	print_progress(double percentage)
{
	const int	val = (int)(percentage * 100);
	const int	lpad = (int)(percentage * PBWIDTH);
	const int	rpad = PBWIDTH - lpad;

	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}
