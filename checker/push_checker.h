/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_checker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:00:03 by asyed             #+#    #+#             */
/*   Updated: 2017/12/07 20:18:47 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_CHECKER_H
# define FT_PUSH_CHECKER_H
#include "libft.h"

typedef struct	s_link {
	struct s_link	*prev;
	int				n;
	struct s_link	*next;
}				t_link;

typedef struct	s_stack {
	t_link	*link;
	int		size;
}				t_stack;

void	swap_a(t_link **stack_a, t_link **stack_b);
void	swap_b(t_link **stack_a, t_link **stack_b);

struct	s_operations {
	char	*op;
	void	(*func)(t_link **stack_a, t_link **stack_b);
}		t_operations;

#endif
