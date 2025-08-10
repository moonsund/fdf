/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:26:05 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 13:19:15 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	convert_lines_to_map(t_list *lines, t_map *map);
static bool	check_line(char **splited_line, t_map *map);
static bool	fill_map_cells(t_map *map, char **splited_line, int i);
static int parse_hex_color(char *str);

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
	if (!line)
	{
		close(fd);
		ft_putstr_fd("ERROR: map file is empty.\n", 2);
		return (false);
	}
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
			{
				close(fd);
				ft_putstr_fd("ERROR: empty line.\n", 2);
				return (false);
			}
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
	map->cells = malloc(map->height * sizeof(t_cell *));
	if (!map->cells)
		return (false);
	curr = lines;
	i = 0;
	while (curr != NULL)
	{
		splited_line = ft_split((char *)curr->content, ' ');
		if (splited_line == NULL)
		{
			free_map_cells(map->cells, i);
			return (false);
		}
		if (check_line(splited_line, map) == false)
		{
			free_array(splited_line);
			free_map_cells(map->cells, i);
			return (false);
		}
		if (fill_map_cells(map, splited_line, i) == false)
		{
			free_array(splited_line);
			free_map_cells(map->cells, i);
			return (false);
		}
		free_array(splited_line);
		curr = curr->next;
		i++;
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
		ft_putstr_fd("ERROR: the map is corrupted (inconsistent width).\n", 2);
		return (false);
	}
	return (true);
}

static bool	fill_map_cells(t_map *map, char **splited_line, int i)
{
	int	j;
	char	**splited_cell;

	map->cells[i] = malloc(map->width * sizeof(t_cell));
	if (!map->cells[i])
	{
		free_array(splited_line);
		free_map_cells(map->cells, i);
		return (false);
	}
	j = 0;
	while (j < map->width)
	{
		splited_cell = ft_split(splited_line[j], ',');
		if (splited_cell == NULL)
        {
            free(map->cells[i]);
            map->cells[i] = NULL;
            ft_putstr_fd("ERROR: allocation failed.\n", 2);
            return (false);
        }
		map->cells[i][j].height = ft_atoi(splited_cell[0]);
		if (splited_cell[1] != NULL)
			map->cells[i][j].colour = parse_hex_color(splited_cell[1]);
		else
			map->cells[i][j].colour = 0xFFFFFF;
		free_array(splited_cell);
		j++;
	}
	return (true);
}

static int parse_hex_color(char *str)
{
    int         i;
    unsigned    val;
    char        *p;

    if (str == NULL)
        return (0xFFFFFF); // лишее
    p = str;
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
        p++;
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
        p += 2;
    i = 0;
    val = 0;
    while (i < 6 && p[i] != '\0')
    {
        char c = p[i];
        unsigned d;

        if (c >= '0' && c <= '9')
            d = (unsigned)(c - '0');
        else if (c >= 'a' && c <= 'f')
            d = (unsigned)(c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            d = (unsigned)(c - 'A' + 10);
        else
            return (0xFFFFFF);
        val = (val << 4) | d;
        i++;
    }
    if (i != 6)
        return (0xFFFFFF);
    return ((int)val);
}
