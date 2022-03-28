/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:51:08 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/25 21:51:12 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;
	size_t	src_dest;

	src_dest = ft_strlen(dest);
	src_len = ft_strlen((char *)src);
	i = 0;
	if (destsize <= src_dest || destsize <= 0)
		return (src_len + destsize);
	while (src[i] != '\0' && (src_dest + i) < (destsize - 1))
	{
		dest[src_dest + i] = src[i];
		i++;
	}
	dest[src_dest + i] = '\0';
	return (src_dest + src_len);
}
