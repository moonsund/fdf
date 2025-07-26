/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:00:49 by lorlov            #+#    #+#             */
/*   Updated: 2025/05/28 13:02:42 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	unsigned int	ndx;
	int				length;

	ndx = 0;
	if (dstsize > 0)
	{
		while (src[ndx] != '\0' && ndx < dstsize - 1)
		{
			dst[ndx] = src[ndx];
			ndx++;
		}
		dst[ndx] = '\0';
	}
	length = 0;
	while (src[length])
		length++;
	return (length);
}
