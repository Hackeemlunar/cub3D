/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:00:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/07/03 19:00:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

/**
 * Prints error message to stderr with "Error" prefix.
 */
void	print_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}

/**
 * Skips whitespace characters and returns pointer to first non-whitespace.
 */
char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

/**
 * Removes trailing newline character from string if present.
 */
char	*trim_newline(char *str)
{
	int	len;

	if (!str)
		return (str);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

/**
 * Prepares content by skipping offset characters and trimming whitespace.
 */
char	*prepare_content(char *line, int offset)
{
	char	*content;

	content = skip_whitespace(line + offset);
	trim_newline(content);
	return (content);
}

/**
 * Checks if line contains only whitespace or is empty.
 */
bool	is_empty_line(char *line)
{
	char	*trimmed;

	trimmed = skip_whitespace(line);
	if (!*trimmed || *trimmed == '\n')
		return (true);
	return (false);
}
