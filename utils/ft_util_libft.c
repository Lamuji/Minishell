/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:01:59 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/23 15:12:03 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

int	verify_char(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	verify_dquote(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
