/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:19:07 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Handles key press events and updates movement flags in the main data 
 * structure.
 * Sets the corresponding movement or rotation flag to 1 when a key is pressed.
 * Exits the program if ESC is pressed.
 *
 * @param keycode The code of the pressed key.
 * @param param   Pointer to the main data structure (t_data).
 * @return        Always returns 0.
 */
int	on_keydown(int keycode, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (keycode == KEY_ESC)
		clean_exit(d, 0);
	if (keycode == KEY_W)
		d->move.forward = 1;
	if (keycode == KEY_S)
		d->move.backward = 1;
	if (keycode == KEY_A)
		d->move.strafe_left = 1;
	if (keycode == KEY_D)
		d->move.strafe_right = 1;
	if (keycode == KEY_AR_L)
		d->move.turn_left = 1;
	if (keycode == KEY_AR_R)
		d->move.turn_right = 1;
	return (0);
}

/**
 * Handles key release events and updates movement flags in the main data 
 * structure.
 * Sets the corresponding movement or rotation flag to 0 when a key is released.
 *
 * @param keycode The code of the released key.
 * @param param   Pointer to the main data structure (t_data).
 * @return        Always returns 0.
 */
int	on_keyup(int keycode, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (keycode == KEY_W)
		d->move.forward = 0;
	if (keycode == KEY_S)
		d->move.backward = 0;
	if (keycode == KEY_A)
		d->move.strafe_left = 0;
	if (keycode == KEY_D)
		d->move.strafe_right = 0;
	if (keycode == KEY_AR_L)
		d->move.turn_left = 0;
	if (keycode == KEY_AR_R)
		d->move.turn_right = 0;
	return (0);
}

/**
 * Handles the window destroy event (e.g., when the user closes the window).
 * Cleans up resources and exits the program.
 *
 * @param param Pointer to the main data structure (t_data).
 * @return      Always returns the result of clean_exit (typically 0).
 */
int	on_destroy(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	return (clean_exit(d, 0));
}
