/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edalmis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:19:26 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/25 21:19:29 by edalmis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_courant;
	t_list	*p_courant2;

	p_courant2 = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		p_courant = ft_lstnew(lst->content);
		p_courant->content = (f)(lst->content);
		if (!p_courant)
			ft_lstdelone(p_courant, del);
		ft_lstadd_back(&p_courant2, p_courant);
		lst = lst->next;
	}
	return (p_courant2);
}
