/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 18:50:08 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/04 20:11:39 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*unsigned_s1;
	unsigned char	*unsigned_s2;

	i = 0;
	unsigned_s1 = (unsigned char*)s1;
	unsigned_s2 = (unsigned char*)s2;
	while (i < n && (unsigned_s1[i] || unsigned_s2[i]))
	{
		if (unsigned_s1[i] != unsigned_s2[i])
			return (unsigned_s1[i] - unsigned_s2[i]);
		i++;
	}
	return (0);
}
