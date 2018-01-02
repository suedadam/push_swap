/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/22 14:31:25 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>
#include <limits.h>

#ifdef DEBUG

int	g_ops;
#endif

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

int		eval_case(t_link *itt_s, int max, t_link *stack_a)
{
	if ((itt_s->prev->n > stack_a->n && stack_a->n > itt_s->n)
		|| (itt_s->n == max && stack_a->n < itt_s->prev->n)
		|| (itt_s->n == max && stack_a->n > max))
	{
		return (1);
	}
	else
		return (0);
}

int		move_calc(t_link **stack_a, t_link **stack_b)
{
	static int	max = 0;
	t_link		*itt_s;
	int			ops;
	int			length;

	itt_s = (*stack_b);
	length = list_length(*stack_b);
	if (!(ops = 0) && (!itt_s || itt_s->prev == itt_s))
	{
		max = ((*stack_a)->n > max) ? (*stack_a)->n : max;
		return (1);
	}
	max = max_fetch(itt_s);
	while (itt_s)
	{
		if (eval_case(itt_s, max, *stack_a))
		{
			(*stack_a)->moves += ops;
			(*stack_a)->rev_moves += (length - ops);
			return (0);
		}
		ops++;
		itt_s = itt_s->next;
	}
	return (0);
}

void	lowest_res(t_link **stack_a, t_link **stack_b)
{
	t_link	*copy;

	copy = step_counter(stack_a);
	(copy->r_dir) ? reverse_process(stack_a, stack_b, copy) :
	normal_process(stack_a, stack_b, copy);
	if (*stack_a == copy)
	{
		newrotate_x(stack_b, (copy->r_dir) ? copy->rev_moves : copy->moves,
			(copy->r_dir) ? "rrb\n" : "rb\n", copy->r_dir);
		print_ops("pb\n");
		push_b(stack_a, stack_b);
	}
}

/*
** Never touch the order of (*stack_a);Thats what temp variables are for :)
*/

void	push_min(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;

	tmp = (*stack_a);
	clear_moves(&tmp);
	while (tmp)
	{
		if (move_calc(&tmp, stack_b))
		{
			while (*stack_a && (*stack_a) != tmp)
			{
				print_ops("ra\n");
				rot_a(stack_a, stack_b);
			}
			print_ops("pb\n");
			push_b(stack_a, stack_b);
			top_largest(stack_b);
			return ;
		}
		path_choose(tmp);
		tmp = tmp->next;
	}
	lowest_res(stack_a, stack_b);
}

int		main(int argc, char *argv[])
{
	t_link	*stack_a;
	int		i;

	if (argc <= 1)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	if (!(stack_a = populate(argc, argv)))
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	if (sort_check(&stack_a))
		return (0);
	if ((i = list_length(stack_a)) <= 3)
		sort_3(&stack_a, i);
	else
		sortmoves(&stack_a);
	return (0);
}
