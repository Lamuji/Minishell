/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfkaier <rfkaier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:46:42 by edalmis           #+#    #+#             */
/*   Updated: 2022/03/31 00:23:30 by rfkaier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*add_content_to_var(char *dest, char *content_to_add, int i)
{
	char	*new_dest_content;

	new_dest_content = NULL;
	while (dest[i] != '=' && dest[i])
		i++;
	new_dest_content = act(dest, new_dest_content, content_to_add, i);
	manager(new_dest_content, 0);
	i = 0;
	while (dest[i] != '=' && dest[i])
	{
		new_dest_content[i] = dest[i];
		i++;
	}
	if (dest[i])
		new_dest_content[i] = dest[i];
	else
		new_dest_content[i] = '=';
	i++;
	new_dest_content = act2(new_dest_content, content_to_add, i);
	manager(new_dest_content, 0);
	return (new_dest_content);
}

static void	add_new(t_list **lst, char *new_content, char *var_dest)
{
	t_list	*temp;

	temp = *lst;
	while (temp != NULL)
	{
		if (ft_ch_int(temp->content, var_dest) != 0)
		{
			temp->content = add_content_to_var(temp->content, new_content, 0);
			break ;
		}
		temp = temp->next;
	}
	if (temp == NULL)
	{
		*lst = add_at(*lst, var_dest, 0, 0);
		manager(*lst, 0);
		add_new(lst, getcwd(NULL, 0), var_dest);
	}
}

static void	change_path(t_data *data, char *place)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	manager(cwd, 0);
	add_new(&data->env, cwd, place);
	manager(&data->env, 0);
	free(cwd);
}

static void	cd_norm(t_data *data)
{
	char	*home;

	home = ft_getenv("HOME", data, 0);
	if (home)
	{
		if (access(home, F_OK) == 0)
		{
			change_path(data, "OLDPWD");
			chdir(home);
			change_path(data, "PWD");
		}
	}
	else
	{
		printf("minishell: cd: HOME not set\n");
	}
}

void	exec_cd(t_data *data, char *path)
{
	if (access(path, F_OK) == 0)
	{
		change_path(data, "OLDPWD");
		chdir(path);
		change_path(data, "PWD");
	}
	else if (!path)
		cd_norm(data);
	else
		perror(path);
}
