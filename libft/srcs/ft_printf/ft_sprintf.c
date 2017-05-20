/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 17:55:27 by luccasim          #+#    #+#             */
/*   Updated: 2016/04/12 17:59:57 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_struct.h"

static char		*buffer_cpy(char *src, char *dest)
{
	char		*d;

	d = dest;
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = 0;
	return (dest);
}

int				ft_sprintf(char *buf, char *str, ...)
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
	buffer_cpy(cpy, buf);
	return (ret);
}
