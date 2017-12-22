/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/22 14:24:28 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>

short	g_error = 0;
size_t	g_tops;

struct s_operations operations[] = {
	{"sa", &swap_a},
	{"sb", &swap_b},
	{"ss", &swap_ab},
	{"pa", &push_a},
	{"pb", &push_b},
	{"ra", &rot_a},
	{"rb", &rot_b},
	{"rr", &rot_ab},
	{"rra", &rev_rot_a},
	{"rrb", &rev_rot_b},
	{"rrr", &rev_rot_ab}
};

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

int		perform_ops(char **oplist, t_link **stack_a)
{
	t_link	*stack_b;
	int		i;

	i = 0;
	stack_b = NULL;
	while (operations[i].op && *oplist)
	{
		if (!ft_strcmp(operations[i].op, *oplist))
		{
			operations[i].func(stack_a, &stack_b);
			oplist++;
			i = 0;
		}
		else
			i++;
	}
	if (i > 10)
	{
		g_error = 1;
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}

int		sort_check(char **oplist, t_link **stack_a)
{
	t_link	*save;

	if (!perform_ops(oplist, stack_a))
		return (0);
	save = *stack_a;
	while (save && save->next)
	{
		if (save->next->n < save->n)
			return (0);
		save = save->next;
	}
	return (1);
}

t_link	*populate(int argc, char *argv[])
{
	t_link	*links;
	t_link	*save;
	int		n;
	int		i;

	links = create_link(0);
	save = links;
	i = 1;
	while (i < argc)
	{
		if (!(n = ft_atoi(argv[i])) && *(argv[i]) != '0')
			return (NULL);
		links->next = create_link(ft_atoi(argv[i]));
		links->next->prev = links;
		save->next->prev = links->next;
		links = links->next;
		i++;
	}
	return (save->next);
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
	g_tops = i;
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

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
	char	**oplist;

	g_tops = 0;
	if (argc <= 1)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	stack_a = populate(argc, argv);
	if (!stack_a)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	oplist = NULL;
	oplist = fill_ops(oplist);
	if (!g_error && sort_check(oplist, &stack_a))
		printf("OK\n");
	else if (!g_error)
		printf("KO\n");
	while (oplist && *oplist)
	{
		free(*oplist);
		*oplist = NULL;
		oplist++;
	}
	freestack(&stack_a);
	return (g_tops);
}
