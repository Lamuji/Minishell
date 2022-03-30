/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:10:36 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:23:30 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_ch_int(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find == NULL || str == NULL)
		return (0);
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == to_find[i])
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			j = 0;
			while (to_find[j] == str[i + j])
			{
				if (to_find[j + 1] == '\0')
				{
					return (str + i);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

int	ft_strchr_env(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == to_find[i])
			i++;
		else
			return (0);
	}
	if (!to_find[i])
		return (1);
	else
		return (0);
}

char	*ft_str_chr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)str + i);
	return (NULL);
}
