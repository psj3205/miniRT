/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:13:31 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/13 20:25:48 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	i = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	if (dst > src)
	{
		i = len;
		while (i != 0)
		{
			((char*)dst)[i - 1] = ((const char*)src)[i - 1];
			i--;
		}
	}
	else
	{
		while (i < len)
		{
			((char*)dst)[i] = ((const char*)src)[i];
			i++;
		}
	}
	return (dst);
}
