/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_libft4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:15 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/16 17:36:54 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_countwordsall(char const *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (!is_space(str[i]) && str[i] != '\0')
			count++;
		while (!is_space(str[i]) && str[i] != '\0')
			i++;
	}
	return (count);
}

int	ft_countwords(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	get_word_len(char const *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	while (!is_space(str[i]) && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_strsplitall(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	**str2;

	str2 = (char **)malloc(sizeof(*str2) * (ft_countwordsall(s) + 1));
	if (!s || !str2)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_countwordsall(s))
	{
		k = 0;
		str2[i] = ft_strnew(get_word_len(&s[j]) + 1);
		if (!str2[i])
			str2[i] = NULL;
		while (is_space(s[j]))
			j++;
		while (!is_space(s[j]) && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
