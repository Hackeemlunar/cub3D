/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:15:06 by sngantch          #+#    #+#             */
/*   Updated: 2025/07/24 19:56:12 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_texture_file(char *texture_path)
{
	FILE	*file;
	char	header[15];

	file = fopen(texture_path, "r");
	if (!file)
	{
		ft_printf("Warning: Texture file not found: %s\n", texture_path);
		return (0);
	}
	if (fgets(header, sizeof(header), file) == NULL)
	{
		fclose(file);
		return (0);
	}
	fclose(file);
	return (ft_strncmp(header, "/* XPM */", 9) == 0);
}

static void	fill_texture_with_color(t_game *game, int tex_index, int color)
{
	t_point	point;
	char	*pixel;

	point.y = 0;
	while (point.y < 64)
	{
		point.x = 0;
		while (point.x < 64)
		{
			pixel = game->textures[tex_index].addr + (point.y
					* game->textures[tex_index].line_length + point.x
					* (game->textures[tex_index].bpp / 8));
			*(int *)pixel = color;
			point.x++;
		}
		point.y++;
	}
}

void	create_fallback_texture(t_game *game, int tx_i)
{
	int		colors[4];
	int		color;
	char	*addr;

	printf("Creating fallback texture for index %d\n", tx_i);
	game->textures[tx_i].width = 64;
	game->textures[tx_i].height = 64;
	game->textures[tx_i].img_ptr = mlx_new_image(game->mlx_ptr, 64, 64);
	if (!game->textures[tx_i].img_ptr)
	{
		ft_printf("Error: Failed to create fallback texture\n");
		return ;
	}
	addr = mlx_get_data_addr(game->textures[tx_i].img_ptr,
			&game->textures[tx_i].bpp, &game->textures[tx_i].line_length,
			&game->textures[tx_i].endian);
	game->textures[tx_i].addr = addr;
	colors[0] = COLOR_RED;
	colors[1] = COLOR_GREEN;
	colors[2] = COLOR_BLUE;
	colors[3] = COLOR_YELLOW;
	color = colors[tx_i % 4];
	fill_texture_with_color(game, tx_i, color);
}

static void	get_texture_data_addr(t_game *game, int i)
{
	game->textures[i].addr = mlx_get_data_addr(game->textures[i].img_ptr,
			&game->textures[i].bpp, &game->textures[i].line_length,
			&game->textures[i].endian);
	if (!game->textures[i].addr)
		create_fallback_texture(game, i);
}

void	load_texture(t_game *game)
{
	int	i;

	initiate_texture(game);
	i = -1;
	while (++i < 4)
	{
		if (validate_texture_file(game->tex_paths[i]))
		{
			game->textures[i].img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
					game->tex_paths[i], &game->textures[i].width,
					&game->textures[i].height);
			if (game->textures[i].img_ptr)
				get_texture_data_addr(game, i);
			else
				create_fallback_texture(game, i);
			game->loading.textures_loaded++;
		}
		else
		{
			create_fallback_texture(game, i);
			game->loading.textures_loaded++;
		}
	}
	game->loading.loading_complete = true;
}

// void load_texture(t_game *game)
// {
//     int     i;
//     int     progress;
//     char    **texture_paths;

//     initiate_texture(game, &texture_paths);
//     printf("Debug: Loading textures from paths ...:\n");
//     i = 0;
//     while(i < 4)
//     {
//         progress = (i * 100) / 4;
//         show_loading_progress(game, progress);
//         if (validate_texture_file(texture_paths[i]))
//         {
//             game->textures[i].img_ptr = 
// mlx_xpm_file_to_image(game->mlx_ptr,
// texture_paths[i],
//                 &game->textures[i].width, &game->textures[i].height);
//             if (game->textures[i].img_ptr)
//             {
//                 game->textures[i].addr = 
// mlx_get_data_addr(game->textures[i].img_ptr,
//                                         &game->textures[i].bpp,
// &game->textures[i].line_length,
//                &game->textures[i].endian);
//                 if (game->textures[i].addr)
//                     game->loading.textures_loaded++;
//                 else
//                 {
//                     create_fallback_texture(game, i);
//                     game->loading.textures_loaded++;
//                 }
//             }
//             else
//             {
//                 create_fallback_texture(game, i);
//                 game->loading.textures_loaded++;
//             }
//         }
//         else
//         {
//             create_fallback_texture(game, i);
//             game->loading.textures_loaded++;
//         }
//         i++;
//     }
//     // Show completion
//     show_loading_progress(game, 100);
//     game->loading.loading_complete = true;
//     printf("Debug: All textures loaded successfully, total loaded: %d/%d\n",
// game->loading.textures_loaded, game->loading.total_textures);

// }

// void show_loading_progress( t_game *game , int progress)
// {
//     int bar_width;
//     int bar_height;
//     t_point bar;
//     t_point point;
//     int fill_width;

//     fast_clear_image(game);
//     bar_width = WINDOW_WIDTH / 2;
//     bar_height = 20;
//     bar.x = WINDOW_HEIGHT / 4;
//     bar.y  = WINDOW_WIDTH / 2 ;
//     //draw the loading bar background
//     point.y =  bar.y ;
//     while( point.y < bar.y + bar_height)
//     {
//         point.x = bar.x;
//         while(point.x < bar.x + bar_width)
//         {
//             put_pixel(point.x, point.y, COLOR_WHITE, game);
//             point.x++;
//         }
//         point.y++;
//     }
//     fill_width = (bar_width * progress) / 100;
//     point.y =  bar.y ;
//     while( point.y < bar.y + bar_height)
//     {
//         point.x = bar.x;
//         while(point.x < bar.x + fill_width)
//         {
//             put_pixel(point.x, point.y, COLOR_GREEN, game);
//             point.x++;
//         }
//         point.y++;
//     }
//     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
// game->win_img.img_ptr, 0, 0);
//     printf("Debug: Loading progress: %d%%\n", progress);
// }
