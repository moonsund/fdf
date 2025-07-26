/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:15:33 by lorlov            #+#    #+#             */
/*   Updated: 2025/05/29 13:54:45 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_array(char *arr, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		arr[i] = s2[j];
		j++;
		i++;
	}
	arr[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*arr;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2);
	if (total_size == 0)
	{
		arr = (char *) malloc(1);
		if (!arr)
			return (NULL);
		arr[0] = '\0';
		return (arr);
	}
	arr = (char *) malloc(sizeof(char) * (total_size + 1));
	if (arr == NULL)
		return (NULL);
	fill_array(arr, s1, s2);
	return (arr);
}
