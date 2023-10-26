/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:27:44 by jaimmart          #+#    #+#             */
/*   Updated: 2023/10/26 12:59:32 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	t_tex_free(t_tex **lst)
{
	t_tex	*aux;

	aux = *lst;
	while (*lst)
	{
		aux = *lst;
		*lst = (*lst)->next;
		free(aux->path);
		free(aux);
	}
	free(lst);
}

/* This function will return the size of the given t_tex *list.*/
int	t_tex_size(t_tex *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/* Creates a new node for t_tex.*/
t_tex	*create_node(char *texture_path, int type)
{
	t_tex	*new;

	new = malloc(sizeof(t_tex));
	if (!new)
		return (printf(ERRMEM, "create_node"), NULL);
	new->path = ft_strdup(texture_path);
	new->type = type;
	new->next = NULL;
	return (new);
}

/* Inserts a node at the end of a t_tex **lst.*/
void	insert_node(t_tex **lst, t_tex *node)
{
	t_tex	*curr;

	if (!*lst)
		*lst = node;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}
