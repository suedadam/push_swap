/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_checker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:00:03 by asyed             #+#    #+#             */
/*   Updated: 2017/12/22 14:29:49 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_CHECKER_H
# define FT_PUSH_CHECKER_H
#include "libft.h"

typedef struct	s_link {
	struct s_link	*prev;
	int				n;
	int				p_steps; //Placement steps.
	int				moves;
	int				rev_moves;
	short			r_dir; //Reverse direction
	struct s_link	*next;
}				t_link;

typedef struct	s_stack {
	t_link	*link;
	int		size;
}				t_stack;

/*
** main.c
*/

void	push_min(t_link **stack_a, t_link **stack_b);
void	lowest_res(t_link **stack_a, t_link **stack_b);
int		move_calc(t_link **stack_a, t_link **stack_b);

/*
** utils.c
*/

void	sort_3(t_link **stack_a, int length);
int		sortMoves(t_link **stack_a);
void	clear_moves(t_link **stack_a);
void	print_ops(char *str);

/*
** swap.c
*/

void	swap_a(t_link **stack_a, t_link **stack_b);
void	swap_b(t_link **stack_a, t_link **stack_b);
void	swap_ab(t_link **stack_a, t_link **stack_b);
t_link	*test_create_link(t_link *prev, int num, t_link *next);
void	push_a(t_link **stack_a, t_link **stack_b);
t_link	*fetch_last(t_link *stack);
void	push_b(t_link **stack_a, t_link **stack_b);
void	rot_a(t_link **stack_a, t_link **stack_b);
void	rot_b(t_link **stack_a, t_link **stack_b);
void	rot_ab(t_link **stack_a, t_link **stack_b);
void	rev_rot_b(t_link **stack_a, t_link **stack_b);
void	rev_rot_a(t_link **stack_a, t_link **stack_b);
void	rev_rot_ab(t_link **stack_a, t_link **stack_b);

/*
** sort_checker.c
*/

int		rev_sort_check(t_link **stack_a);
void	top_largest(t_link **stack);
int		largest_val(t_link **stack_b);
int		sort_check(t_link **stack_a);

/*
** ll_utils.c
*/

t_link	*create_link(int num);
int		list_length(t_link *stack);
int		startover(t_link **stack);
int		pl_in_stack(int y, t_link *check);
t_link	*populate(int argc, char *argv[]);

/*
** bulk_ops.c
*/

void	newrotate_x(t_link	**stack, int i, char *id, short rev);
void	ammor_rotate_x(t_link **stack_a, t_link **stack_b, int i, short rev);
void	path_choose(t_link *stack);

struct	s_operations {
	char	*op;
	void	(*func)(t_link **stack_a, t_link **stack_b);
}		t_operations;

# ifdef DEBUG
	extern int g_ops;
# endif 
#endif
