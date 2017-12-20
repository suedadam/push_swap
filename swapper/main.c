/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/20 14:29:50 by suedadam         ###   ########.fr       */
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
		{
			printf("%d < %d\n", save->next->n, save->n);
			return (0);
		}
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
	int			num;
	int			ops;

	num = (*stack_a)->n;
	itt_s = (*stack_b);
	ops = 0;
	if (!itt_s || itt_s->prev == itt_s)
	{
		max = (num > max) ? num : max;
		return (1);
	}
	while (itt_s)
	{
		if ((itt_s->prev->n > num && num > itt_s->n)
			|| (itt_s->n == max && num < itt_s->prev->n)
			|| (itt_s->n == max && num > max))
		{
			max = (num > max) ? num : max;
			(*stack_a)->moves += ops;
			return (0);
		}
		ops++;
		itt_s = itt_s->next;
	}
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
		// printf("{clear_moves} %d->%d\n", save->n, save->moves);
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

void	rotate_x(t_link	**stack, int i)
{
	while (i-- > 0)
	{
		printf("ra\n");
		rot_a(stack, NULL);
	}
}

void	top_largest(t_link **stack)
{
	int		max;
	t_link	*tmp;

	max = 0;
	tmp = (*stack);
	while (tmp)
	{
		if (tmp->n > max)
			max = tmp->n;
		tmp = tmp->next;
	}
	while ((*stack)->n != max)
	{
		printf("rb\n");
		rot_b(NULL, stack);
	}
	if ((*stack)->n == max)
		printf("\e[1;32mOK\n\e[0m");
	else
		printf("\e[1;31mKO\n\e[0m");
}

void	lowest_res(t_link **stack_a, t_link **stack_b)
{
	int		i;
	t_link	*tmp;
	t_link	*copy;

	tmp = (*stack_a);
	copy = tmp;
	i = 0;
	while (tmp)
	{
		if (tmp->moves < copy->moves)
			copy = tmp;
		tmp->moves -= i++;
		tmp = tmp->next;
	}
	i = pl_in_stack(copy->n, (*stack_a));
	rotate_x(stack_a, i);
	copy->moves -= i;
	if (*stack_a == copy)
	{
		rotate_x(stack_b, copy->moves);
		printf("pb\n");
		push_b(stack_a, stack_b);
		top_largest(stack_b);
	}
	else
	{
		printf("Mis-calculation.\n");
	}
}

/*
** Never touch the order of (*stack_a);Thats what temp variables are for :) 
*/

void	push_min(t_link **stack_a, t_link **stack_b)
{
	t_link	*copy;
	t_link	*tmp;

	tmp = (*stack_a);
	clear_moves(&tmp);
	while (tmp)
	{
		if (move_calc(&tmp, stack_b))
		{
			//Rotate so that we're moving the correct variable on stack_a.
			while (*stack_a && (*stack_a) != tmp)
			{
				printf("ra\n");
				rot_a(stack_a, stack_b);
			}
			//Confirm position? We can do that on triggered debugging.
			push_b(stack_a, stack_b);
			if ((*stack_b)->next && (*stack_b)->next->n > (*stack_b)->n)
			{
				printf("rb\n");
				rot_b(stack_a, stack_b);
			}
			return ;
		}
		tmp = tmp->next;
	}
	lowest_res(stack_a, stack_b);
}

int		sortMoves(t_link **stack_a)
{
	t_link	*stack_b;	

	stack_b = NULL;
	while (*stack_a)
		push_min(stack_a, &stack_b);
	startover(&stack_b);
	while (stack_b)
	{
		printf("pa\n");
		push_a(stack_a, &stack_b);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
	t_link	*test;
	int		i;

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
	test = stack_a;
	while (test)
	{
		printf("(%d) %d (%d)\n", test->prev->n, test->n, (test->next) ? test->next->n : 0);
		test = test->next;
	}
	sortMoves(&stack_a);
	printf("\e[1;35m==Final==\e[0m\n");
	if (sort_check(&stack_a))
	{
		printf("\e[1;32mOK\e[0m\n");
	}
	else
		printf("\e[1;31mKO\e[0m\n");
	return (1);
}
