/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 12:21:04 by tfregni           #+#    #+#             */
/*   Updated: 2023/09/09 10:57:07 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
/*
Keymap
*/
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define Q 12
# define W 13
# define E 14
# define A 0
# define S 1
# define D 2
# define R 15
# define F 3
# define C 8
# define PLUS 30
# define MINUS 44
/*
Mouse map
*/
# define LEFT_BUTTON 1
# define RIGHT_BUTTON 2
# define CENTER_BUTTON 3
# define WHEEL_UP 4
# define WHEEL_DOWN 5
/*
Events
*/
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

#endif
