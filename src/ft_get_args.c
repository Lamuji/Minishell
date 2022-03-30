/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:49:20 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:34:11 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_realloc(char *s1, char *s2)
{
	char	*s_realloc;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	s_realloc = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s_realloc)
		return (NULL);
	while (s1[++i])
		s_realloc[i] = s1[i];
	free(s1);
	while (s2[++j])
		s_realloc[i + j] = s2[j];
	s_realloc[i + j] = '\0';
	return (s_realloc);
}

char	*ft_arrange_bin(char *bin, char **sp_path, int i, t_cmd *cmd)
{
	manager(sp_path[i], 0);
	bin = ft_calloc(sizeof(char *),
			(ft_strlen(sp_path[i]) + ft_strlen((*cmd).cmd[0]) + 1));
	manager(bin, 0);
	bin = ft_strcat(bin, sp_path[i]);
	bin = ft_strcat(bin, "/");
	bin = ft_strcat(bin, (*cmd).cmd[0]);
	return (bin);
}
