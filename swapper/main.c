/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/20 13:20:52 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>
#include <limits.h>

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

int		largest_val(t_link **stack_b)
{
	t_link	*tmp;
	int		largest;

	largest = 0;
	tmp = (*stack_b);

	while (tmp)
	{
		if (tmp->n > largest)
			largest = tmp->n;
		tmp = tmp->next;
	}
	return (largest);
}

int		move_calc(t_link **stack_a, t_link **stack_b)
{
	static int	max = 0;
	t_link		*itt_s;
	int			ops;
	int			num;

	num = (*stack_a)->n;
	if (num > max)
		max = num;
	itt_s = (*stack_b);
	if (!itt_s || itt_s->prev == itt_s)
	{
		// printf("{@1}\n");
		return (1);
	}
	while (itt_s)
	{
		if (itt_s->prev->n > num && num > itt_s->n)
		{
			// printf("\e[1;32m{OK} %d > (%d) > %d\e[0m\n", itt_s->prev->n, num, itt_s->n);
			(*stack_a)->moves += ops;
			return (0);
		}
		else if (itt_s->n == max && num < itt_s->prev->n)
		{
			// printf("\e[1;36mLowest Number \e[0m\n");
			(*stack_a)->moves += ops;
			return (0);
		}
		// else
		// 	printf("\e[1;31m{KO} %d > (%d) > %d\e[0m\n", itt_s->prev->n, num, itt_s->n);
		ops++;
		itt_s = itt_s->next;
	}
	// printf("\e[1;31mNO VALID PLACEMENT\e[0m\n");
	return (0);
}

void	clear_moves(t_link **stack_a)
{
	t_link *save;
	int	i;

	save = *stack_a;
	i = 0;

	while (save)
	{
		save->moves = i++;
		printf("{clear_moves} %d->%d\n", save->n, save->moves);
		save = save->next;
	}
}

int		startover(t_link **stack)
{
	while ((*stack)->prev->next)
		(*stack) = (*stack)->prev;
	return (1);
}

int		pl_in_stack(int y, t_link *check)
{
	int	i;

	i = 0;
	while (check)
	{
		if (check->n == y)
			return (i);
		i++;
		check = check->next;
	}
	return (i);
}	

void	push_min(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;
	t_link	*copy;
	int		i;

	tmp = (*stack_a);
	clear_moves(&tmp);
	while (tmp)
	{
		// printf("num: %d called move_calc(%d)\n", tmp->n, tmp->moves);
		if (move_calc(&tmp, stack_b))
		{
			while (*stack_a && (*stack_a) != tmp)
			{
				printf("ra\n");
				rot_a(stack_a, stack_b);
			}
			if ((*stack_a) == tmp)
				printf("\e[1;32m Matched position\e[0m\n");
			else
				printf("\e[1;31mError - Mismatched position\e[0m\n");
			push_b(stack_a, stack_b);
			if ((*stack_b)->next && (*stack_b)->next->n < (*stack_b)->n)
			{
				printf("rb\n");
				rot_b(stack_a, stack_b);
			}
			// printf("====LOL=====\n");
			return ;
		}
		// printf("{%d} After move_calc() ->%d\n", tmp->n, tmp->moves);
		tmp = tmp->next;
	}
	tmp = (*stack_a);
	copy = tmp;
	i = 0;
	while (tmp)
	{
		if (tmp->moves < copy->moves)
		{
			copy = tmp;
			// printf("Re-set copy -> %d (%d)\n", copy->n, copy->moves);
		}
		tmp->moves -= i++;
		tmp = tmp->next;
	}
	i = pl_in_stack(copy->n, *stack_a);
	while (i-- > 0)
	{
		printf("ra\n");
		rot_a(stack_a, stack_b);
	}
	if (*stack_a == copy)
	{
		while (copy->moves-- > 0)
		{
			printf("rb\n");
			rot_b(stack_a, stack_b);
		}
		printf("pb\n");
		push_b(stack_a, stack_b);
		//#Hackzy way
		// printf("=== Rotate for largest at the top ===\n");
		tmp = (*stack_b);
		int max;
		max = 0;
		while (tmp)
		{
			if (tmp->n > max)
				max = tmp->n;
			tmp = tmp->next;
		}
		while ((*stack_b)->n != max)
		{
			printf("rb\n");
			rot_b(stack_a, stack_b);
		}
		tmp = (*stack_b);
	}
	else
	{
		printf("\e[1;31mERRORRRRRR stack_a = %d\n\e[0m", (*stack_a)->n);
	}
}

int		sortMoves(t_link **stack_a)
{
	t_link	*stack_b = NULL;
	t_link	*save;
	int		ret;

	while ((*stack_a) && startover(stack_a))
	{
		// save = stack_b;
		// printf("=================================\n");
		// while (save)
		// {
		// 	printf("SB: (%d) %d (%d)\n", save->prev->n, save->n, (save->next) ? save->next->n : 0);
		// 	save = save->next;
		// }
		// printf("=================================\n");
		push_min(stack_a, &stack_b);
	}
	startover(&stack_b);
	// printf("pushing all to stack_a\n");
	while (stack_b)
	{
		printf("pa\n");
		push_a(stack_a, &stack_b);
	}
	// printf("{sortMoves} starting Over. (%d)\n", stack_b->n);
	// save = stack_b;
	// printf("=================================\n");
	// while (save)
	// {
	// 	printf("SB: (%d) %d (%d)\n", save->prev->n, save->n, (save->next) ? save->next->n : 0);
	// 	save = save->next;
	// }
	// 	printf("=================================\n");
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
	printf("====== Done Sorting Printing Stack====\n");
	deleteme = stack_a;
	while (deleteme)
	{
		printf("SA: (%d) %d (%d)\n", deleteme->prev->n, deleteme->n, (deleteme->next) ? deleteme->next->n : 0);
		deleteme = deleteme->next;
	}
	printf("====== Done printing stack ======\n");
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