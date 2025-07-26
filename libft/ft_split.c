/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:51:31 by lorlov            #+#    #+#             */
/*   Updated: 2025/05/28 16:27:05 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;
	size_t		len;
	char		*word;

	while (**s == c)
		(*s)++;
	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		(*s)++;
		len++;
	}
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	free_result(char **result)
{
	size_t	i;

	i = 0;
	while (result && result[i])
		free(result[i++]);
	free(result);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**result;
	size_t	i;

	count = count_words(s, c);
	result = malloc((count + 1) * sizeof(char *));
	i = 0;
	if (!s || !result)
		return (NULL);
	while (i < count)
	{
		result[i] = next_word(&s, c);
		if (!result[i])
			return (free_result(result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
