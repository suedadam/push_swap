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
	int		g_ops;
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

int		move_calc(t_link **stack_a, t_link **stack_b)
{
	static int	max = 0;
	t_link		*itt_s;
	int			num;
	int			ops;
	int			length;

	num = (*stack_a)->n;
	itt_s = (*stack_b);
	ops = 0;
	length = list_length(*stack_b);
	if (!itt_s || itt_s->prev == itt_s)
	{
		max = (num > max) ? num : max;
		return (1);
	}
	//New way to find max:
	while (itt_s)
	{
		max = (itt_s->n > max) ? itt_s->n : max;
		itt_s = itt_s->next;
	}
	itt_s = (*stack_b);
	//ENd of new way to find max
	while (itt_s)
	{
		if ((itt_s->prev->n > num && num > itt_s->n) //Between case.
			|| (itt_s->n == max && num < itt_s->prev->n) //Lowest case
			|| (itt_s->n == max && num > max)) //Highest case
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
	int		length;
	t_link	*tmp;
	t_link	*copy;

	tmp = (*stack_a);
	copy = tmp;
	length = list_length(*stack_a);
	while (tmp)
	{
		if (tmp->r_dir)
		{
			length = list_length(*stack_a);
			tmp->p_steps = (length - tmp->p_steps);
			if ((tmp->p_steps + tmp->rev_moves) < ((copy->r_dir) ? copy->rev_moves : copy->moves) + copy->p_steps)
				copy = tmp;
		}
		else
		{
			if ((tmp->p_steps + tmp->moves) < ((copy->r_dir) ? copy->rev_moves : copy->moves) + copy->p_steps)
				copy = tmp;
		}
		tmp = tmp->next;
	}
	if (copy->r_dir)
	{
		if (copy->rev_moves && copy->p_steps)
		{
			if (copy->rev_moves >= copy->p_steps)
			{
				ammor_rotate_x(stack_a, stack_b, copy->p_steps, 1);
				copy->rev_moves -= copy->p_steps;
				copy->p_steps = 0;
			}
			else if (copy->rev_moves < copy->p_steps)
			{
				ammor_rotate_x(stack_a, stack_b, copy->rev_moves, 1);
				copy->p_steps -= copy->rev_moves;
				copy->rev_moves = 0;
			}
		}
		newrotate_x(stack_a, copy->p_steps, "rra\n", 1);
		copy->p_steps = 0;
	}
	else
	{
		if (copy->moves && copy->p_steps)
		{
			if (copy->moves >= copy->p_steps)
			{
				ammor_rotate_x(stack_a, stack_b, copy->p_steps, 0);
				copy->moves -= copy->p_steps;
				copy->p_steps = 0;
			}
			else if (copy->moves < copy->p_steps)
			{
				ammor_rotate_x(stack_a, stack_b, copy->moves, 0);
				copy->p_steps -= copy->moves;
				copy->moves = 0;
			}	
		}
		newrotate_x(stack_a, copy->p_steps, "ra\n", 0);
	}
	if (*stack_a == copy)
	{
		if (copy->r_dir)
			newrotate_x(stack_b, copy->rev_moves, "rrb\n", 1);
		else
			newrotate_x(stack_b, copy->moves, "rb\n", 0);
		print_ops("pb\n");
		push_b(stack_a, stack_b);
	}
	else
		printf("Mis-calculation. (%d || %d) (%d instead of %d)\n", (*stack_a)->prev == copy, (((*stack_a)->next) ? (*stack_a)->next == copy : 0), (*stack_a)->n, copy->n);
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
			//Rotate so that we're moving the correct variable on stack_a.
			while (*stack_a && (*stack_a) != tmp)
			{
				print_ops("ra\n");
				rot_a(stack_a, stack_b);
			}
			//Confirm position? We can do that on triggered debugging.
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

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
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
	if (sort_check(&stack_a))
		return (0);
	i = list_length(stack_a);
	if (i <= 3)
		sort_3(&stack_a, i);
	else
		sortMoves(&stack_a);
	#ifdef DEBUG
		ft_putnbr(g_ops);
	#endif
	return (0);
}
