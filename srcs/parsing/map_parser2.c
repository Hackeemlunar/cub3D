/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:00:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/07/26 22:02:28 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/**
 * Validates the overall structure of the parsed map.
 */
bool	validate_map_structure(t_config *config)
{
	if (!find_player_position_p(config))
	{
		print_error("Map must contain exactly one player (N, S, E, or W)");
		return (false);
	}
	if (!is_map_closed(config))
	{
		print_error("Map must be closed/surrounded by walls");
		return (false);
	}
	return (true);
}

/**
 * Main function to parse map section from linked list.
 */
bool	parse_map(t_list *map_start, t_config *config, t_arena *arena)
{
	int	row_count;

	row_count = count_map_rows_p(map_start);
	if (row_count == 0)
	{
		print_error("Empty map");
		return (false);
	}
	if (!allocate_map_board(config, row_count, arena))
		return (false);
	if (!populate_map_board(map_start, config, arena))
		return (false);
	return (validate_map_structure(config));
}

/**
 * Builds a linked list of file lines after validation.
 */
t_list	*build_map_line_list(char *filename)
{
	if (!validate_file_extension(filename))
		return (NULL);
	if (!can_open_file(filename))
		return (NULL);
	return (read_file_to_list(filename));
}

/**
 * Checks if line contains direction/color elements and parses them.
 */
bool	check_direction(char *trimmed, t_list *current, t_config *config,
		t_arena *arena)
{
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3)
		|| !ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
	{
		if (!parse_element((char *)current->content, config, arena))
			return (false);
	}
	return (true);
}
