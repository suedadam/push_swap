/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/22 14:29:18 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>

t_link	*create_link(int num)
{
	t_link *link;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	link->n = num;
	return (link);
}

/*
** Will only work for 80,000 operations or less :)
*/

char	**fill_ops(char **oplist)
{
	int		ops;
	int		i;
	char	*line;

	ops = 80000;
	i = 0;
	oplist = (char **)ft_memalloc(ops * sizeof(char *));
	if (!oplist)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	while (get_next_line(0, &line) != 0)
	{
		oplist[i++] = ft_strdup(line);
		free(line);
	}
	return (oplist);
}

void	freestack(t_link **stack_a)
{
	t_link	*tmp;

	while (*stack_a)
	{
		tmp = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = tmp;
	}
}

void	oplist_free(char **oplist)
{
	while (oplist && *oplist)
	{
		free(*oplist);
		*oplist = NULL;
		oplist++;
	}
}
