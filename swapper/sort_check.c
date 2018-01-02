/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 12:55:24 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 13:28:19 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

int		rev_sort_check(t_link **stack_a)
{
	t_link	*save;

	save = *stack_a;
	if (!save)
		return (0);
	while (save && save->next)
	{
		if (save->next->n > save->n)
			return (0);
		save = save->next;
	}
	return (1);
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
		print_ops("rb\n");
		rot_b(NULL, stack);
	}
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
