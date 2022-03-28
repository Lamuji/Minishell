/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:07:25 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/16 17:00:37 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	count_equals(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

void	pwd(void)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror(tmp);
	}
	else
	{
		ft_putstr_fd(tmp, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	free(tmp);
}
