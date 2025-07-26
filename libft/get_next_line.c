/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:48:30 by lorlov            #+#    #+#             */
/*   Updated: 2025/07/21 20:48:06 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *stash)
{
	size_t	i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*trim_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + i + 1);
	free(stash);
	return (new_stash);
}

static char	*read_and_append(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes;

	buf = (char *)malloc(10 + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	if (!stash)
	stash = ft_strdup("");
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, 10);
		if (bytes < 0)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes] = '\0';
		tmp = ft_strjoin(stash, buf);
		if (!tmp)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = tmp;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || 10 <= 0)
	{
		return (NULL);
	}
	stash = read_and_append(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}
