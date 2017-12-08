/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:02:32 by asyed             #+#    #+#             */
/*   Updated: 2017/12/07 20:20:20 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

/*
** sa : swap a - swap the first 2 elements at the top of stack a. Do nothing if there
** is only one or no elements).
*/


void	swap_a(t_link **stack_a, t_link **stack_b)
{
	int	tmp;

	if (stack_a && *stack_a && (*stack_a)->next)
	{
		tmp = (*stack_a)->n;
		(*stack_a)->n = (*stack_a)->next->n;
		(*stack_a)->next->n = tmp;		
	}
}

void	swap_b(t_link **stack_a, t_link **stack_b)
{
	int	tmp;

	if (stack_b && *stack_b && (*stack_b)->next)
	{
		tmp = (*stack_b)->n;
		(*stack_b)->n = (*stack_b)->next->n;
		(*stack_b)->next->n = tmp;		
	}
}
