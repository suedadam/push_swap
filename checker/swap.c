/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:02:32 by asyed             #+#    #+#             */
/*   Updated: 2017/12/08 16:05:28 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>

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

void	swap_ab(t_link **stack_a, t_link **stack_b)
{
	swap_a(stack_a, stack_b);
	swap_b(stack_a, stack_b);
}

t_link	*test_create_link(t_link *prev, int num, t_link *next)
{
	t_link *link;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	link->n = num;
	if (!prev)
		link->prev = link;
	else
		link->prev = prev;
	link->next = next;
	return (link);
}

void	push_a(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;
	t_link	*lastb;

	if (*stack_b)
	{
		if (*stack_a)
			tmp = test_create_link((*stack_a)->prev, (*stack_b)->n, (*stack_a));
		else
			tmp = test_create_link(NULL, (*stack_b)->n, NULL);
		(*stack_a) = tmp;
		if ((*stack_a)->next)
			(*stack_a)->next->prev = (*stack_a);
		tmp = NULL;
		if ((*stack_b)->next)
			tmp = test_create_link((*stack_b)->prev, (*stack_b)->next->n, (*stack_b)->next->next);
		free(*stack_b);
		(*stack_b) = tmp;
	}
}

t_link	*fetch_last(t_link *stack)
{
	while (stack)
		stack = stack->next;
	return (stack->prev);
}
/*
** pb : push b - take the first element at the top of a and put 
** it at the top of b. Do nothing if a is empty.
*/
void	push_b(t_link **stack_a, t_link **stack_b)
{
	t_link	*tmp;
	t_link	*lastb;

	if (*stack_a)
	{
		if (*stack_b)
			tmp = test_create_link((*stack_b)->prev, (*stack_a)->n, (*stack_b));
		else
			tmp = test_create_link(NULL, (*stack_a)->n, NULL);
		(*stack_b) = tmp;
		if ((*stack_b)->next)
			(*stack_b)->next->prev = (*stack_b);
		tmp = NULL;
		if ((*stack_a)->next)
			tmp = test_create_link((*stack_a)->prev, (*stack_a)->next->n, (*stack_a)->next->next);
		free(*stack_a);
		(*stack_a) = tmp;
	}
}

// void	rot_a(t_link **stack_a, t_link **stack_b)
// {
// 	t_link *tmp;

// 	if (*stack_a && (*stack_a)->next)
// 	{
// 		tmp = (*stack_a);
// 		(*stack_a) = tmp->next;
// 		tmp->prev->next = tmp;
// 		tmp->next = NULL;
// 		(*stack_a)->prev = tmp;
// 	}
// }

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
}


void	rot_ab(t_link **stack_a, t_link **stack_b)
{
	rot_a(stack_a, stack_b);
	rot_b(stack_a, stack_b);
}

void	rev_rot_b(t_link **stack_a, t_link **stack_b)
{
	t_link	*save;

	if (*stack_b)
	{
		save = (*stack_b);
		while (save && save->next)
			save = save->next;
		save->prev->next = NULL;
		save->next = (*stack_b);
		(*stack_b) = save;
	}
}

void	rev_rot_a(t_link **stack_a, t_link **stack_b)
{
	t_link	*save;

	if (*stack_a)
	{
		save = (*stack_a);
		while (save && save->next)
			save = save->next;
		save->prev->next = NULL;
		save->next = (*stack_a);
		(*stack_a) = save;		
	}
}

void	rev_rot_ab(t_link **stack_a, t_link **stack_b)
{
	rev_rot_a(stack_a, stack_b);
	rev_rot_b(stack_a, stack_b);
}
