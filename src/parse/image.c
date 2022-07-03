/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:35:36 by juhur             #+#    #+#             */
/*   Updated: 2022/07/03 11:14:10 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	set_image_from_xpm(void *mlx, char *path, struct s_image *image)
{
	image->img = mlx_xpm_file_to_image(mlx, path, &(image->w), &(image->h));
	if (image->img == NULL)
		quit_program(STATUS_ERROR_INVALID_MAP);
}

static char	*get_path(const char **ss)
{
	char	*path;
	int		i;
	int		len;

	len = 1;
	while (ss[len] != NULL)
		++len;
	path = NULL;
	i = 0;
	while (++i < len)
	{
		path = _strexpand(path, ss[i]);
		if (i < len - 1)
			path = _strexpand(path, " ");
	}
	return (path);
}

bool	set_image(t_game *game, char *data)
{
	const char	*direction[MAX_IMAGE] = {"NO", "SO", "WE", "EA"};
	const char	**ss = _split(data, ' ');
	int			i;

	i = -1;
	while (++i < MAX_IMAGE)
	{
		if (ss[0] == NULL)
			break ;
		if (!_strcmp(ss[0], direction[i]))
		{
			if (game->wall[i].path != NULL)
				quit_program(STATUS_ERROR_INVALID_MAP);
			game->wall[i].path = get_path(ss);
			set_image_from_xpm(game->mlx, game->wall[i].path, &game->wall[i]);
			_free_double_pointer((void ***)&ss);
			return (true);
		}
	}
	_free_double_pointer((void ***)&ss);
	return (false);
}
