/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <luccasim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/28 23:16:10 by luccasim          #+#    #+#             */
/*   Updated: 2015/03/17 14:38:31 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	char		*d;

	if (!dst || !src || n == 0)
		return (0);
	d = dst;
	while (n > 1)
	{
		if (*src)
			*d++ = *src++;
		else
		{
			*d = 0;
			return (ft_strlen(dst));
		}
		n--;
	}
	*d = 0;
	return (ft_strlen(dst));
}
