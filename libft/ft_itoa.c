/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:36:03 by lorlov            #+#    #+#             */
/*   Updated: 2025/05/29 14:15:27 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_digit_length(unsigned long long n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			is_negative;
	long long	lln;
	int			len;

	lln = n;
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		lln = -lln;
	}
	len = get_digit_length(lln) + is_negative;
	result = (char *)malloc(sizeof(char) * (len +1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > is_negative)
	{
		result[len] = (lln % 10) + '0';
		lln = lln / 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}
