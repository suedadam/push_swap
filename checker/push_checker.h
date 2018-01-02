/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_checker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:00:03 by asyed             #+#    #+#             */
/*   Updated: 2017/12/08 15:37:48 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_CHECKER_H
# define FT_PUSH_CHECKER_H
# include "libft.h"
# include "structures.h"

t_link	*create_link(int num);
void	swap_a(t_link **stack_a, t_link **stack_b);
void	swap_b(t_link **stack_a, t_link **stack_b);
void	swap_ab(t_link **stack_a, t_link **stack_b);
void	push_a(t_link **stack_a, t_link **stack_b);
void	push_b(t_link **stack_a, t_link **stack_b);
void	rot_a(t_link **stack_a, t_link **stack_b);
void	rot_b(t_link **stack_a, t_link **stack_b);
void	rot_ab(t_link **stack_a, t_link **stack_b);
void	rev_rot_a(t_link **stack_a, t_link **stack_b);
void	rev_rot_b(t_link **stack_a, t_link **stack_b);
void	rev_rot_ab(t_link **stack_a, t_link **stack_b);

/*
** utils.c
*/

char	**fill_ops(char **oplist);
void	freestack(t_link **stack_a);
void	oplist_free(char **oplist);
t_link	*create_link(int num);

#endif
