/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:15:14 by sngantch          #+#    #+#             */
/*   Updated: 2025/07/17 21:44:32 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	int	i;

	printf("Debug: Closing game...\n");
	game->game_running = false;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures[i].img_ptr);
			game->textures[i].img_ptr = NULL;
			printf("Debug: Texture %d destroyed\n", i);
		}
		i++;
	}
	free(game->tex_paths);
	if (game->win_img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->win_img.img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	printf("Debug: Game closed successfully\n");
	exit(EXIT_SUCCESS);
}

// Performance monitoring functions

void	update_timing(t_game *game)
{
	double	current_time;

	current_time = get_time();
	game->timing.delta_time = current_time - game->timing.last_frame_time;
	game->timing.last_frame_time = current_time;
	if (game->timing.delta_time > 0.1)
		game->timing.delta_time = 0.1;
	game->timing.fps = 1.0 / game->timing.delta_time;
}
