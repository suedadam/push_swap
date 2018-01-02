/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revrot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 14:11:46 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 14:18:45 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	rev_rot_b(t_link **stack_a, t_link **stack_b)
{
	t_link *save;

	if (*stack_b)
	{
		save = (*stack_b)->prev;
		save->next = (*stack_b);
		save->prev->next = NULL;
		(*stack_b) = save;
	}
	(void)stack_a;
}

void	rev_rot_a(t_link **stack_a, t_link **stack_b)
{
	t_link *save;

	if (*stack_a)
	{
		save = (*stack_a)->prev;
		save->next = (*stack_a);
		save->prev->next = NULL;
		(*stack_a) = save;
	}
	(void)stack_b;
}

void	rev_rot_ab(t_link **stack_a, t_link **stack_b)
{
	rev_rot_a(stack_a, stack_b);
	rev_rot_b(stack_a, stack_b);
}
