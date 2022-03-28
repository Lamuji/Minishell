/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:04:11 by hkrifa            #+#    #+#             */
/*   Updated: 2022/03/23 15:13:08 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_c(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*dest;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && find_c(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && find_c(s1[end - 1], set))
		end--;
	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dest[i] = s1[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}

static int	verify_quo(char const *s1, int start)
{
	if (s1[start] == '"')
		start++;
	return (start);
}

char	*ft_strtrim2(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*dest;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && find_c(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && find_c(s1[end - 1], set))
		end--;
	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		start = verify_quo(s1, start);
		dest[i++] = s1[start++];
	}
	dest[i] = 0;
	return (dest);
}
