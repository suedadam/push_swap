/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulk_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 12:59:35 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 13:27:42 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	newrotate_x(t_link **stack, int i, char *id, short rev)
{
	while (i-- > 0)
	{
		print_ops(id);
		if (rev)
			rev_rot_a(stack, NULL);
		else
			rot_a(stack, NULL);
	}
}

void	ammor_rotate_x(t_link **stack_a, t_link **stack_b, int i, short rev)
{
	while (i-- > 0)
	{
		if (rev)
		{
			print_ops("rrr\n");
			rev_rot_ab(stack_a, stack_b);
		}
		else
		{
			print_ops("rr\n");
			rot_ab(stack_a, stack_b);
		}
	}
}

void	path_choose(t_link *stack)
{
	if (stack->rev_moves > 0 && stack->rev_moves < stack->moves)
		stack->r_dir = 1;
}
