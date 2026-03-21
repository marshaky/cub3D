/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_outputs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:31:20 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 10:51:53 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_OUTPUTS_H
# define ERROR_OUTPUTS_H

/* ************************************************************************** */
/*     src/parser                     parser.c                                */
/* ************************************************************************** */
# define MUL_PLAYER_POS		"Error\nMultiple player positions\n"
# define NO_PLAYER_POS		"Error\nNo player position found\n"

/* ************************************************************************** */
/*     src/parser            parser_validate.c                                */
/* ************************************************************************** */
# define OPEN_FILE_ERR		"Error\nCannot open file: %s\n"
# define CONFIG_ERR			"Error\nInvalid config (need NO,SO,WE,EA,F,C)\n"
# define MAP_FIND_ERR		"Error\nNo map found in file\n"

/* ************************************************************************** */
/*     src/parser            parser_utils.c                                   */
/* ************************************************************************** */
# define COL_ERR			"Error\nInvalid color format\n"
# define COL_VAL_ERR		"Error\nColor values must be 0-255\n"
# define COL_DUB_ERR		"Error\nDuplicate or invalid config line\n"
#endif