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

#ifndef FT_STRUCTURES_H
# define FT_STRUCTURES_H

typedef struct	s_link {
	struct s_link	*prev;
	int				n;
	int				p_steps;
	int				moves;
	int				rev_moves;
	short			r_dir;
	struct s_link	*next;
}				t_link;

typedef struct	s_stack {
	t_link	*link;
	int		size;
}				t_stack;

struct			s_operations {
	char	*op;
	void	(*func)(t_link **stack_a, t_link **stack_b);
}				t_operations;

#endif
