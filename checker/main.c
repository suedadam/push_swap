/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/07 17:52:06 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>

struct s_operations operations[] = {
	// {"sa", &swap_a},
	// {"sb", &swap_b},
	// {"ss", &swap_ab}
};

int		is_sorted(t_stack *stack_a, int size)
{
	int i;

	i = 0;
	while (stack_a->link && stack_a->link->next)
	{
		if (stack_a->link->next->n < stack_a->link->n)
			return (0);
		stack_a->link = stack_a->link->next;
	}
	return (1);

	// while (i < (size - 2))
	// {
	// 	if (stack_a[i + 1] < stack_a[i])
	// 	{
	// 		printf("KO (%d) %d > %d\n", i, stack_a[i + 1], stack_a[i]);
	// 		return (0);
	// 	}
	// 	else
	// 		printf("OK (%d) %d > %d\n", i, stack_a[i + 1], stack_a[i]);
	// 	i++;
	// }
	// return (1);
}

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
	link->set = '1';
	return (link);
}

t_stack	*create_stack(void)
{
	// t_link *link;
	t_stack *stack;

	// link = create_link(0);
	stack = (t_stack *)ft_memalloc(sizeof(t_stack));
	if (!stack)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	// stack->stack = link;
	// stack->size = 1;
	return (stack);
}

int		sort_check(char **oplist, t_stack *stack_a, int size)
{
	t_stack *stack_b;
	int i;

	stack_b = create_stack();
	if (!stack_b)
		return (0);
	i = 0;
	while (operations[i].op)
	{
		if (!ft_strcmp(operations[i].op, *oplist))
		{
			operations[i].func(stack_a, stack_b);
			oplist++;
			i = 0;
		}
		i++;
	}
	return (is_sorted(stack_a, size));
}

int		populate(int argc, char *argv[], t_stack *stack)
{
	int		i;
	t_link	*links;
	t_link	*tmp;

	i = 1;
	while (i < argc)
	{
		if (!links)
		{
			links = create_link(ft_atoi(argv[i]));
			if (!links)
			{
				write(1, "Error\n", 6);
				return (-1);
			}
			stack->link = links;
		}
		else
		{
			tmp = create_link(ft_atoi(argv[i]));
			if (!tmp)
			{
				write(1, "Error\n", 6);
				return (-1);
			}
			if (links->next)
				printf("Error wtf? ->next = %p\n", links->next);
			links->next = tmp;
		}
		//change this to set at the end?
		stack->size++;
		links = links->next;;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	int		i;
	int		ops;
	char	**oplist;
	char	*line;

	if (argc <= 1)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	stack_a = create_stack();
	if (!stack_a)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	if (!populate(argc, argv, stack_a))
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	i = 0;
	// printf("in func:\n");
	// while (i < argc)
	// {
	// 	printf("to_sort[%d] = %d\n", i, to_sort[i]);
	// 	i++;
	// }
	i = 0;
	ops = 200;
	oplist = (char **)ft_memalloc(sizeof(char *) * ops);
	if (!oplist)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	while(get_next_line(0, &line) != 0)
	{
		if (i == (ops - 1))
		{
			oplist = (char **)ft_realloc_safe(oplist, ops, (ops + 200));
			if (!oplist)
			{
				write(1, "Error\n", 6);
				return (-1);
			}
			ops += 200;
		}
		oplist[i] = ft_strdup(line);
		printf("Line = %s (stored as: \"%s\")\n", line, oplist[i]);
		i++;
	}
	if (sort_check(oplist, stack_a, argc))
		printf("OK\n");
	else
		printf("KO\n");
	return (1);
}