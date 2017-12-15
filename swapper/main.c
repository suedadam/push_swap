/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/14 22:20:14 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>

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

int		sort_check(t_link **stack_a)
{
	t_link	*save;

	save = *stack_a;
	if (!save)
		return (0);
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

char	**fill_ops(char **oplist)
{
	int		ops;
	int		i;
	char	*line;

	ops = 200;
	i = 0;
	oplist = (char **)ft_memalloc(ops * sizeof(char *));
	if (!oplist)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	while (get_next_line(0, &line) != 0)
	{
		if (i == (ops - 1))
		{
			oplist = (char **)ft_realloc_safe(oplist, ops, ops + 200);
			if (!oplist)
			{
				write(1, "Error\n", 6);
				return (NULL);
			}
			ops += 200;
		}
		oplist[i++] = ft_strdup(line);
		free(line);
	}
	return (oplist);
}

void	push_min(t_link **stack_a, t_link **stack_b)
{
	t_link	*save;
	int		num;
	int		c;

	save = *stack_a;
	while (*stack_a)
	{
	}
}

int		rev_sort_check(t_link **stack_a)
{
	t_link	*save;

	save = *stack_a;
	if (!save)
		return (0);
	while (save && save->next)
	{
		if (save->next->n < save->n)
			return (0);
		save = save->next;
	}
	return (1);
}

int		move_calc(t_link **stack_a, t_link **stack_b)
{
	static int	max = 0;
	int	ops;
	int num;

	ops = 0;
	num = (*stack_a)->n;
	if (max > num)
		num = max;
	// 0 elements, 1 element or 2 elements
	if (!*stack_b || (*stack_b)->prev == (*stack_b) || (*stack_b)->prev == (*stack_b)->next)
	{
		if (*stack_b)
			printf("%p || %p == %p || %p == %p\n", *stack_b, (*stack_b)->prev, (*stack_b), (*stack_b)->prev, (*stack_b)->next);
		else
			printf("stack_b == NULL\n");
		(*stack_a)->moves = ops;
		return (0);
	}
	while (*stack_b)
	{
		if (num < (*stack_b)->prev->n && num > (*stack_b)->n)
		{
			(*stack_a)->moves = ops;
			return (1);
		}
		else
		{
			printf("%d < %d && %d > %d\n", num, (*stack_b)->prev->n, num, (*stack_b)->n);
		}
		ops++;
		(*stack_b) = (*stack_b)->next;
	}
	if (!ops)
	{
		printf("Error? %d calculated ops for (*stack_a)->n (->moves) %d\n", (*stack_a)->moves, (*stack_a)->n);
	}
	return (0);
}

int	sortMoves(t_link **stack_a)
{
	t_link	*stack_b = NULL;
	t_link	*save;
	int		ret;

	save = (*stack_a);
	while (*stack_a && !sort_check(stack_a))
	{
		if ((ret = move_calc(stack_a, &stack_b)))
		{
			printf("we calculated it biatch (%d) took %d moves\n", (*stack_a)->n, (*stack_a)->moves);
			(*stack_a) = (*stack_a)->next;
		}
		else if (!ret && !(*stack_a)->moves)
		{
			printf("Pushing %d to stack b\n", (*stack_a)->n);
			push_b(stack_a, &stack_b);
		}
		else
		{
			printf("wtf? %d\n", (*stack_a)->n);
		}
	}
	(*stack_a) = save;
	// rev_sort(stack_b);
	// while (stack_b)
	// {
	// 	printf("pa\n");
	// 	push_a(stack_a, &stack_b);
	// }
	return (0);
}

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
	t_link	*deleteme;
	int		i; //Del me.

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
	sortMoves(&stack_a);
	// deleteme = stack_a;
	// while (stack_a)
	// {
	// 	printf("stack_a->n = (%d) %d\n", stack_a->prev->n, stack_a->n);
	// 	stack_a = stack_a->next;
	// }
	// stack_a = deleteme;
	// if (sort_check(oplist, &stack_a))
	// 	printf("OK\n");
	// else
	// 	printf("KO\n");
	// i = 0;
	// while (oplist[i])
	// {
	// 	printf("oplist[%d] = %s\n", i, oplist[i]);
	// 	i++;
	// }
	// while (stack_a)
	// {
	// 	printf("stack_a->n = (%d) %d (%d)\n", stack_a->prev->n, stack_a->n, (stack_a->next) ? stack_a->next->n : 0);
	// 	stack_a = stack_a->next;
	// }
	stack_a = deleteme;
	//Check if its empty.
	return (1);
}


// int	main(int argc, char *argv[])
// {
// 	t_link	*stack_a;
// 	int		i;
// 	int		ops;
// 	char	**oplist;
// 	char	*line;

// 	if (argc <= 1)
// 	{
// 		write(1, "Error\n", 6);
// 		return (-1);
// 	}
// 	stack_a = create_stack();
// 	if (!stack_a)
// 	{
// 		write(1, "Error\n", 6);
// 		return (-1);
// 	}
// 	if (!populate(argc, argv, stack_a))
// 	{
// 		write(1, "Error\n", 6);
// 		return (-1);
// 	}
// 	i = 0;
// 	ops = 200;
// 	oplist = (char **)ft_memalloc(sizeof(char *) * ops);
// 	if (!oplist)
// 	{
// 		write(1, "Error\n", 6);
// 		return (-1);
// 	}
// 	while(get_next_line(0, &line) != 0)
// 	{
// 		if (i == (ops - 1))
// 		{
// 			oplist = (char **)ft_realloc_safe(oplist, ops, (ops + 200));
// 			if (!oplist)
// 			{
// 				write(1, "Error\n", 6);
// 				return (-1);
// 			}
// 			ops += 200;
// 		}
// 		oplist[i] = ft_strdup(line);
// 		printf("Line = %s (stored as: \"%s\")\n", line, oplist[i]);
// 		i++;
// 	}
// 	if (sort_check(oplist, stack_a, argc))
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	return (1);
// }