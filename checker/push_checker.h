/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_checker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:00:03 by asyed             #+#    #+#             */
/*   Updated: 2017/12/07 17:48:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_CHECKER_H
# define FT_PUSH_CHECKER_H
#include "libft.h"

typedef struct	s_link {
	int				n;
	char			set;
	struct s_link	*next;
}				t_link;

typedef struct	s_stack {
	t_link	*link;
	int		size;
}				t_stack;

struct	s_operations {
	char	*op;
	void	*(*func)(t_stack *stack_a, t_stack *stack_b);
}		t_operations;

#endif
