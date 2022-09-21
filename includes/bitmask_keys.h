/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_keys.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:50:15 by dmalesev          #+#    #+#             */
/*   Updated: 2022/09/21 13:00:51 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMASK_KEYS_H
# define BITMASK_KEYS_H

enum e_bitmask_keys
{
	BITMASK_UP = 1L << 0,
	BITMASK_LEFT = 1L << 1,
	BITMASK_RIGHT = 1L << 2,
	BITMASK_DOWN = 1L << 3,
	BITMASK_ESC = 1L << 4,
	BITMASK_DOT = 1L << 5,
	BITMASK_T = 1L << 6,
	BITMASK_RIGHT_BUTTON = 1L << 7,
	BITMASK_SPACE = 1L << 8,
	BITMASK_L_SHIFT = 1L << 9,
	BITMASK_A = 1L << 10,
	BITMASK_S = 1L << 11,
	BITMASK_D = 1L << 12,
	BITMASK_W = 1L << 13,
	BITMASK_R = 1L << 14,
	BITMASK_NUM_PLUS = 1L << 15,
	BITMASK_NUM_MINUS = 1L << 16,
	BITMASK_DEL = 1L << 17,
	BITMASK_BACKSPACE = 1L << 18
};

#endif
