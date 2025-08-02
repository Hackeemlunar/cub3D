/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:00:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/07/03 19:00:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/**
 * Checks if character is valid for map content.
 */
bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

/**
 * Checks if character represents a walkable map position.
 */
bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Validates all characters in a map line are allowed.
 */
bool	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_map_char(line[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * Validates that a row contains only walls and spaces.
 */
bool	is_row_valid(char *row)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(row))
	{
		if (row[j] != '1' && row[j] != ' ')
			return (false);
		j++;
	}
	return (true);
}

/**
 * Checks if character is valid for side columns (walls or spaces).
 */
bool	check_side_column_char(char c)
{
	return (c == '1' || c == ' ');
}
