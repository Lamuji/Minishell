/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:01:59 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:36:35 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_strnew(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	while (++j < s2_len)
		*(new_str + i++) = *(s2 + j);
	return (new_str);
}

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
