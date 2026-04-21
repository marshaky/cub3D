/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:58:57 by aramarak          #+#    #+#             */
/*   Updated: 2026/04/21 20:56:30 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_blank_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_file_readable(char *path)
{
	int	fd;

	if (!path)
		return (ERROR);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	close(fd);
	return (0);
}
