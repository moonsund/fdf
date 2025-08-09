/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:26:05 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/08 12:44:37 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	convert_lines_to_map(t_list *lines, t_map *map);
static bool	check_line(char **splited_line, t_map *map);
static bool	fill_map_heights(t_map *map, char **splited_line, int i);

bool	parse_map(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	t_list	*lines;
	bool	result;

	lines = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("The file is not opened.");
		return (false);
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	map->width = -1;
	result = convert_lines_to_map(lines, map);
	ft_lstclear(&lines, free);
	return (result);
}

static bool	convert_lines_to_map(t_list *lines, t_map *map)
{
	t_list	*curr;
	char	**splited_line;
	int		i;

	map->height = ft_lstsize(lines);
	map->map_heights = malloc(map->height * sizeof(int *));
	if (!map->map_heights)
		return (false);
	curr = lines;
	i = 0;
	while (curr)
	{
		splited_line = ft_split((char *)curr->content, ' ');
		if (!check_line(splited_line, map))
		{
			free_array(splited_line);
			free_map_heights(map->map_heights, i);
			return (false);
		}
		if (!fill_map_heights(map, splited_line, i++))
			return (false);
		curr = curr->next;
	}
	return (true);
}

static bool	check_line(char **splited_line, t_map *map)
{
	int	k;

	k = 0;
	while (splited_line[k])
		k++;
	if (map->width == -1)
		map->width = k;
	else if (map->width != k)
	{
		ft_putstr_fd("\nERROR: the map is corrupted.\n\n", 2);
		return (false);
	}
	return (true);
}

static bool	fill_map_heights(t_map *map, char **splited_line, int i)
{
	int	j;

	map->map_heights[i] = malloc(map->width * sizeof(int));
	if (!map->map_heights[i])
	{
		free_array(splited_line);
		free_map_heights(map->map_heights, i);
		return (false);
	}
	j = 0;
	while (j < map->width)
	{
		map->map_heights[i][j] = ft_atoi(splited_line[j]);
		j++;
	}
	free_array(splited_line);
	return (true);
}
