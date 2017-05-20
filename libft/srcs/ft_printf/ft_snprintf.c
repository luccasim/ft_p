/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 17:55:27 by luccasim          #+#    #+#             */
/*   Updated: 2016/04/12 17:59:57 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_struct.h"

static size_t	ft_printlcpy(char *dst, const char *src, size_t n)
{
	char		*d;
	size_t		k;

	d = dst;
	k = 0;
	while (n > 1)
	{
		if (*src)
			*d++ = *src++;
		else
		{
			*d = 0;
			return (k);
		}
		n--;
		k++;
	}
	*d = 0;
	return (k);
}

int				ft_snprintf(char *buf, size_t size, char *str, ...)
{
	va_list		ap;
	char		*cpy;

	if (!buf)
		return (0);
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
	ft_printf_buffer(str, &cpy, BUF_GET);
	return (ft_printlcpy(buf, cpy, size));
}
