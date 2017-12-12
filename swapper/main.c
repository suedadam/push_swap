/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/11 18:18:41 by asyed            ###   ########.fr       */
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

int		perform_ops(char **oplist, t_link **stack_a)
{
	t_link	*stack_b;
	t_link	*save;
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
	printf("\n-------Greedymother fucker--=-----\n");
	save = stack_b;
	while (stack_b)
	{
		// printf("stack_b->prev = %p\n", stack_b->prev);
		printf("stack_b->n = (%d) %d (%d)\n", stack_b->prev->n, stack_b->n, (stack_b->next) ? stack_b->next->n : 0);
		stack_b = stack_b->next;
	}
	stack_b = save;
	printf("--------------------------\n");
	save = *stack_a;
	while (*stack_a)
	{
		// printf("stack_a->prev = %p\n", stack_a->prev);
		printf("stack_a->n = (%d) %d (%d)\n", (*stack_a)->prev->n, (*stack_a)->n, ((*stack_a)->next) ? (*stack_a)->next->n : 0);
		(*stack_a) = (*stack_a)->next;
	}
	*stack_a = save;
	printf("\n-------End of Dick--=-----\n");
}

int		sort_check(char **oplist, t_link **stack_a)
{
	t_link	*save;

	// perform_ops(oplist, stack_a);
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
	int min;
	t_link *save;

	save = *stack_a;
	min = save->n;
	while (save)
	{
		if (save->n <= min)
			min = save->n;
		save = save->next;
	}
	if ((*stack_a)->next && (*stack_a)->next->n == min)
	{
		printf("sa\n");
		swap_a(stack_a, stack_b);
	}
	while (*stack_a)
	{
		if ((*stack_a)->n == min)
		{
			printf("pb\n");
			push_b(stack_a, stack_b);
			break ;
		}
		printf("ra\n");
		rot_a(stack_a, stack_b);
	}
}

int	sortMoves(t_link **stack_a)
{
	t_link	*stack_b = NULL;

	while (*stack_a)
		push_min(stack_a, &stack_b);
	while (stack_b)
	{
		printf("pa\n");
		push_a(stack_a, &stack_b);
	}
}

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
	t_link *deleteme;
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