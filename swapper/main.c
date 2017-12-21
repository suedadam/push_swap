/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:59:11 by asyed             #+#    #+#             */
/*   Updated: 2017/12/21 00:29:37 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_checker.h"
#include <stdlib.h>
#include <limits.h>

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

t_link	*create_link(int num)
{
	t_link *link;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	link->n = num;
	return (link);
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
		{
			printf("%d < %d\n", save->next->n, save->n);
			return (0);
		}
		save = save->next;
	}
	return (1);
}

t_link	*populate(int argc, char *argv[])
{
	t_link	*links;
	t_link	*save;
	int		n;
	int		i;

	links = create_link(0);
	save = links;
	i = 1;
	while (i < argc)
	{
		if (!(n = ft_atoi(argv[i])) && *(argv[i]) != '0')
			return (NULL);
		links->next = create_link(ft_atoi(argv[i]));
		links->next->prev = links;
		save->next->prev = links->next;
		links = links->next;
		i++;
	}
	return (save->next);
}

char	**fill_ops(char **oplist)
{
	int		ops;
	int		i;
	char	*line;

	ops = 200;
	i = 0;
	oplist = (char **)ft_memalloc(ops * sizeof(char *));
	if (!oplist)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	while (get_next_line(0, &line) != 0)
	{
		if (i == (ops - 1))
		{
			oplist = (char **)ft_realloc_safe(oplist, ops, ops + 200);
			if (!oplist)
			{
				write(1, "Error\n", 6);
				return (NULL);
			}
			ops += 200;
		}
		oplist[i++] = ft_strdup(line);
		free(line);
	}
	return (oplist);
}

int		rev_sort_check(t_link **stack_a)
{
	t_link	*save;

	save = *stack_a;
	if (!save)
		return (0);
	while (save && save->next)
	{
		if (save->next->n > save->n)
		{
			// printf("\e[1;36m{RC} %d > %d\e[0m\n", save->next->n, save->n);
			return (0);
		}
		save = save->next;
	}
	return (1);
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
		printf("rb\n");
		rot_b(NULL, stack);
	}
	// if ((*stack)->n == max)
	// 	printf("\e[1;32mOK\n\e[0m");
	// else
	// 	printf("\e[1;31mKO\n\e[0m");
}

int		list_length(t_link *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

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
	if (!itt_s || itt_s->prev == itt_s
		// (itt_s->next == itt_s->prev) //2 are placed.
	)
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
			// printf("\e[1;36m{%d} (%d || %d || %d)\e[0m\n", num, (itt_s->prev->n > num && num > itt_s->n), (itt_s->n == max && num < itt_s->prev->n), (itt_s->n == max && num > max));
			// max = (num > max) ? num : max;
			(*stack_a)->moves += ops;
			(*stack_a)->rev_moves += (length - ops);
			return (0);
		}
		ops++;
		itt_s = itt_s->next;
	}
	printf("=====The following are errors====\n");
	itt_s = (*stack_b);
	return (0);
}

void	clear_moves(t_link **stack_a)
{
	t_link *save;
	int	i;

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

int		startover(t_link **stack)
{
	while ((*stack)->prev->next)
		(*stack) = (*stack)->prev;
	return (1);
}

int		pl_in_stack(int y, t_link *check)
{
	int	i;

	i = 0;
	while (check)
	{
		if (check->n == y)
			return (i);
		i++;
		check = check->next;
	}
	return (i);
}

void	newrotate_x(t_link	**stack, int i, char *id, short rev)
{
	while (i-- > 0)
	{
		printf("%s\n", id);
		if (rev)
			rev_rot_a(stack, NULL);
		else
			rot_a(stack, NULL);
	}
}

void	print_stack(t_link *stack, char *prefix)
{
	while (stack)
	{
		if (prefix)
			printf("%s(%d) %d[%d;%d] (%d)\e[0m\n", prefix, stack->prev->n, stack->n, stack->p_steps, stack->moves, (stack->next) ? stack->next->n : 0);
		else
			printf("(%d) %d[%d;%d] (%d)\e[0m\n", stack->prev->n, stack->n, stack->p_steps, stack->moves,(stack->next) ? stack->next->n : 0);
		stack = stack->next;
	}
}

void	ammor_rotate_x(t_link **stack_a, t_link **stack_b, int i, short rev)
{
	while (i-- > 0)
	{
		if (rev)
		{
			printf("rrr\n");
			rev_rot_ab(stack_a, stack_b);
		}
		else
		{
			printf("rr\n");
			rot_ab(stack_a, stack_b);			
		}

	}
}

void	lowest_res(t_link **stack_a, t_link **stack_b)
{
	int		length;
	t_link	*tmp;
	t_link	*copy;

	tmp = (*stack_a);
	copy = tmp;
	length = 0;
	while (tmp)
	{
		if ((tmp->p_steps + ((tmp->r_dir) ? tmp->rev_moves : tmp->moves)) < (copy->p_steps + ((copy->r_dir) ? copy->rev_moves : copy->moves)))
			copy = tmp;
		tmp = tmp->next;
	}
	// length = list_length(*stack_a);
	// if (copy->r_dir)
	// {
	// 	//forgot to use length;
	// 	if (copy->moves && copy->p_steps && copy->p_steps >= (length > 2))
	// 	{
	// 		copy->p_steps = (length - copy->p_steps);
	// 		// if (copy->rev_moves >= copy->p_steps)
	// 		// {
	// 		// 	newrotate_x(stack_a, copy->rev_moves, "rra", 1);
	// 		// 	copy->rev_moves -= copy->p_steps;
	// 		// 	copy->p_steps = 0;
	// 		// }
	// 		// else
	// 		// {
	// 		// 	newrotate_x(stack_a, copy->rev_moves, "rra", 1);
	// 		// 	copy->p_steps -= copy->rev_moves;
	// 		// 	copy->rev_moves = 0;
	// 		// }
	// 		newrotate_x(stack_a, copy->p_steps, "rra", 1);
	// 	}
	// 	else
	// 		newrotate_x(stack_a, copy->p_steps, "ra", 0);
	// }
	// else
	// {
		if (!copy->r_dir && copy->moves && copy->p_steps)
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
		if (copy->r_dir)
			newrotate_x(stack_a, copy->p_steps, "rlola", 0);
		else
			newrotate_x(stack_a, copy->p_steps, "ra", 0);
	// }
	// printf("\e[1;33m{RX} %d->p_steps %d\n", copy->n, copy->p_steps);
	// print_stack(*stack_a, "\e[1;33m{RX}");
	if (*stack_a == copy)
	{
		// printf("%d->moves (%d)\n", copy->n, copy->moves);
		if (copy->r_dir)
		{
			// printf("\e[1;34mreverse detected %d (%d)\e[0m\n", copy->n, copy->rev_moves);
			// printf("Pre-rotate: (%d)\n", copy->n);
			// print_stack(*stack_b, "\e[1;35m{Pre-Push}");
			newrotate_x(stack_b, copy->rev_moves, "rrb", 1);
		}
		else
			newrotate_x(stack_b, copy->moves, "rb", 0);
			// rotate_x(stack_b, copy->moves, "rb");
		printf("pb\n");
		push_b(stack_a, stack_b);
	}
	else
	{
		//Find this error.
		printf("Mis-calculation. (%d || %d) (%d instead of %d)\n", (*stack_a)->prev == copy, (((*stack_a)->next) ? (*stack_a)->next == copy : 0), (*stack_a)->n, copy->n);
	}
}

void	path_choose(t_link *stack)
{
	if (stack->rev_moves > 0 && stack->rev_moves < stack->moves)
		stack->r_dir = 1;
}

/*
** Never touch the order of (*stack_a);Thats what temp variables are for :) 
*/

void	push_min(t_link **stack_a, t_link **stack_b)
{
	t_link	*copy;
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
				printf("ra\n");
				rot_a(stack_a, stack_b);
			}
			//Confirm position? We can do that on triggered debugging.
			printf("pb\n");
			push_b(stack_a, stack_b);
			top_largest(stack_b);
			return ;
		}
		path_choose(tmp);
		tmp = tmp->next;
	}
	lowest_res(stack_a, stack_b);
}

int		sortMoves(t_link **stack_a)
{
	t_link	*stack_b;	

	stack_b = NULL;
	while (*stack_a)
		push_min(stack_a, &stack_b);
	startover(&stack_b);
	top_largest(&stack_b);
	while (stack_b)
	{
		printf("pa\n");
		push_a(stack_a, &stack_b);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_link	*stack_a;
	t_link	*test;
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
	// test = stack_a;
	// while (test)
	// {
	// 	printf("(%d) %d (%d)\n", test->prev->n, test->n, (test->next) ? test->next->n : 0);
	// 	test = test->next;
	// }
	sortMoves(&stack_a);
	printf("\e[1;35m==Final==\e[0m\n");
	if (sort_check(&stack_a))
	{
		printf("\e[1;32mOK\e[0m\n");
	}
	else
		printf("\e[1;31mKO\e[0m\n");
	return (1);
}
