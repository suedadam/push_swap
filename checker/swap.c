/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:02:32 by asyed             #+#    #+#             */
/*   Updated: 2017/12/22 14:19:11 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	swap_a(t_link **stack_a, t_link **stack_b)
{
	int	tmp;

	if (stack_a && *stack_a && (*stack_a)->next)
	{
		tmp = (*stack_a)->n;
		(*stack_a)->n = (*stack_a)->next->n;
		(*stack_a)->next->n = tmp;
	}
	(void)stack_b;
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
	(void)stack_a;
}

void	swap_ab(t_link **stack_a, t_link **stack_b)
{
	swap_a(stack_a, stack_b);
	swap_b(stack_a, stack_b);
}

void	push_a(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;

	if (*stack_b)
	{
		if ((*stack_b)->next)
			(*stack_b)->next->prev = (*stack_b)->prev;
		tmp = (*stack_b);
		(*stack_b) = (*stack_b)->next;
		if (*stack_a)
		{
			tmp->prev = (*stack_a)->prev;
			(*stack_a)->prev = tmp;
			tmp->next = (*stack_a);
		}
		else
		{
			tmp->prev = tmp;
			tmp->next = NULL;
		}
		(*stack_a) = tmp;
	}
}

void	push_b(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;

	if (*stack_a)
	{
		if ((*stack_a)->next)
			(*stack_a)->next->prev = (*stack_a)->prev;
		tmp = (*stack_a);
		(*stack_a) = (*stack_a)->next;
		if (*stack_b)
		{
			tmp->prev = (*stack_b)->prev;
			(*stack_b)->prev = tmp;
			tmp->next = (*stack_b);
		}
		else
		{
			tmp->prev = tmp;
			tmp->next = NULL;
		}
		(*stack_b) = tmp;
	}
}
