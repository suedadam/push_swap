/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:00:18 by suedadam          #+#    #+#             */
/*   Updated: 2017/12/22 14:30:43 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"

void	clear_moves(t_link **stack_a)
{
	t_link	*save;
	int		i;

	save = *stack_a;
	i = 0;
	while (save)
	{
		save->p_steps = i++;
		save->moves = 0;
		save->rev_moves = 0;
		save->r_dir = 0;
		save = save->next;
	}
}

int		sortmoves(t_link **stack_a)
{
	t_link	*stack_b;

	stack_b = NULL;
	while (*stack_a)
		push_min(stack_a, &stack_b);
	startover(&stack_b);
	top_largest(&stack_b);
	while (stack_b)
	{
		print_ops("pa\n");
		push_a(stack_a, &stack_b);
	}
	return (0);
}

void	sort_3(t_link **stack_a, int length)
{
	int	max;

	if (length == 1)
		return ;
	if (length == 3)
	{
		max = pl_in_stack(largest_val(stack_a), *stack_a);
		if (!max)
		{
			print_ops("ra\n");
			rot_a(stack_a, NULL);
		}
		if (max == 1)
		{
			print_ops("rra\n");
			rev_rot_a(stack_a, NULL);
		}
	}
	if ((*stack_a)->n > (*stack_a)->next->n)
	{
		print_ops("sa\n");
		swap_a(stack_a, NULL);
	}
}

void	print_ops(char *str)
{
	write(1, str, ft_strlen(str));
#ifdef DEBUG

	g_ops++;
#endif

}

int		max_fetch(t_link *itt_s)
{
	int	max;

	max = 0;
	while (itt_s)
	{
		max = (itt_s->n > max) ? itt_s->n : max;
		itt_s = itt_s->next;
	}
	return (max);
}
