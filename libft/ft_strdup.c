/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:15:42 by lorlov            #+#    #+#             */
/*   Updated: 2025/05/29 13:54:16 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;	
	int		i;
	int		length;

	length = ft_strlen(s1);
	ptr = (char *) malloc((length + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (length > i)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
