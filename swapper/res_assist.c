/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_assist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 14:11:46 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 14:18:45 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	reverse_process(t_link **stack_a, t_link **stack_b, t_link *copy)
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

void	normal_process(t_link **stack_a, t_link **stack_b, t_link *copy)
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

t_link	*step_counter(t_link **stack_a)
{
	t_link	*copy;
	t_link	*tmp;
	int		length;

	tmp = (*stack_a);
	copy = tmp;
	length = list_length(*stack_a);
	while (tmp)
	{
		if (tmp->r_dir)
		{
			length = list_length(*stack_a);
			tmp->p_steps = (length - tmp->p_steps);
			if ((tmp->p_steps + tmp->rev_moves) <
				((copy->r_dir) ? copy->rev_moves : copy->moves) + copy->p_steps)
				copy = tmp;
		}
		else if ((tmp->p_steps + tmp->moves) <
			((copy->r_dir) ? copy->rev_moves : copy->moves) + copy->p_steps)
			copy = tmp;
		tmp = tmp->next;
	}
	return (copy);
}
