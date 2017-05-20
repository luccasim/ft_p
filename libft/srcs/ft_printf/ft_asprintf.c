/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 17:55:27 by luccasim          #+#    #+#             */
/*   Updated: 2016/04/12 17:59:57 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_struct.h"
#include <stdlib.h>

static char		*alloc_str(char *dst)
{
	char		*new;
	int			k;

	k = 0;
	if (!dst)
		return (0);
	while (dst[k++])
		;
	if ((new = (char*)malloc(k + 1)) == 0)
		return (0);
	k = 0;
	while (dst[k])
	{
		new[k] = dst[k];
		k++;
	}
	new[k] = 0;
	return (new);
}

int				ft_asprintf(char **buf, char *str, ...)
{
	va_list		ap;
	int			ret;
	char		*cpy;

	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
			str += ft_printf_lexer(str, ap);
		else if (*str == '{')
			str += ft_printf_color(str, ap);
		else
			ft_printf_buffer(str++, 0, BUF_CHAR);
	}
	va_end(ap);
	ret = ft_printf_buffer(str, &cpy, BUF_GET);
	*buf = alloc_str(cpy);
	return (ret);
}
