#include "fdf.h"

static bool convert_lines_to_map(t_list *lines, t_map *map);

bool parse_map(const char *file_path, t_map *map)
{
    int fd;
    char *line;
    t_list *lines;

    lines = NULL;
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        perror("The file is not opened.");
        return (false);
    }
    while ((line = get_next_line(fd)))
	    ft_lstadd_back(&lines, ft_lstnew(line));
    close(fd);
    if (!convert_lines_to_map(lines, map))
    {
        ft_lstclear(&lines, free);
        return (false);
    }
    ft_lstclear(&lines, free);
    return (true);
}

static bool convert_lines_to_map(t_list *lines, t_map *map)
{
    int height;
    char **split;
    int **height_map;
    int width;
    int i;
    int j;
    int k;
    t_list *curr;

    height = ft_lstsize(lines);
    height_map = malloc(height * sizeof(int *));
    width = -1;
    i = 0;
    curr = lines;
    while (curr)
    {
        split = ft_split((char *)curr->content, ' ');
        k = 0;
        while (split[k])
            k++;
        if (width == -1)
            width = k;
        if (width != k)
        {
            ft_putstr_fd("\nERROR: the map is corrupted.\n\n", 2);
            free_array(split);
            free_map_height(height_map, height); // возможно стоит объединить с free(map)
            return (false);
        }
        j = 0;
        height_map[i] = malloc(width * sizeof(int));
            if (!height_map[i])
            {
                free_array(split);
                free_map_height(height_map, height);
                return (false);
            }

        while (j < width)
        {
            height_map[i][j] = ft_atoi(split[j]);
            j++;
        }
        i++;
        free_array(split);
        curr=curr->next;
    }

    map->height_map = height_map;
    map->width = width;
    map->height = height;
    return (true);
}