/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:56:01 by rfkaier           #+#    #+#             */
/*   Updated: 2022/03/25 18:39:11 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_list	*lstnew_env(char *str)
{
	t_list	*new_block;

	new_block = (t_list *)malloc(sizeof(t_list));
	manager(new_block, 0);
	if (!(new_block))
		return (NULL);
	new_block->content = ft_strdup(str);
	manager(new_block->content, 0);
	new_block->next = NULL;
	return (new_block);
}

void	creat_cell(t_list **cell, char *str)
{
	(*cell) = ft_calloc(sizeof(t_list), 1);
	manager(*cell, 0);
	if (!(*cell))
		return ;
	(*cell)->content = ft_strdup(str);
	manager((*cell)->content, 0);
}
