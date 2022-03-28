/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:23:28 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/25 21:23:31 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p_courant;
	t_list	*tmp;

	if (lst)
	{
		p_courant = *lst;
		while (p_courant)
		{
			tmp = p_courant -> next;
			ft_lstdelone(p_courant, del);
			p_courant = tmp;
		}
		*lst = NULL;
	}
}
