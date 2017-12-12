/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:20:10 by asyed             #+#    #+#             */
/*   Updated: 2017/11/15 13:31:21 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t num)
{
	char	*d;
	size_t	i;

	d = (char *)ptr;
	i = 0;
	while (i < num)
	{
		*(d++) = val;
		i++;
	}
	return (ptr);
}
