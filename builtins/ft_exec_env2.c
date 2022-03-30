/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:24:28 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/30 16:03:01 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	print_list2(t_list *lst)
{
	char	*strtrim;

	while (lst)
	{
		if (!verify_char(lst->content))
		{
			lst = lst->next;
		}
		else
		{
			strtrim = ft_strtrim2(lst->content, "\"");
			ft_putstr_fd(strtrim, 1);
			manager(strtrim, 0);
			write(1, "\n", 2);
			lst = lst->next;
		}
	}
}
