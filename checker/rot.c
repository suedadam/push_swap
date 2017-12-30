/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 14:11:18 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 14:18:59 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	rot_a(t_link **stack_a, t_link **stack_b)
{
	t_link *save;

	if (*stack_a && (*stack_a)->next)
	{
		save = (*stack_a)->next;
		(*stack_a)->prev->next = (*stack_a);
		(*stack_a)->next = NULL;
		(*stack_a) = save;
	}
	(void)stack_b;
}

void	rot_b(t_link **stack_a, t_link **stack_b)
{
	t_link *save;

	if (*stack_b && (*stack_b)->next)
	{
		save = (*stack_b)->next;
		(*stack_b)->prev->next = (*stack_b);
		(*stack_b)->next = NULL;
		(*stack_b) = save;
	}
	(void)stack_a;
}


void	rot_ab(t_link **stack_a, t_link **stack_b)
{
	rot_a(stack_a, stack_b);
	rot_b(stack_a, stack_b);
}
