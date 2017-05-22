/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:07:01 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/22 15:07:07 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int				option_name(t_server *server, char *str)
{
	ft_strlcpy(server->name, str, SIZE);
	return (SUCCESS);
}

int				option_limit(t_server *server, char *str)
{
	int			nb;

	nb = ft_atoi(str);
	if (nb > 0 && nb < 10)
		server->limit = nb;
	else
		return (PERROR("<limit=?> {1-10}; Default : limit=5"));
	return (SUCCESS);
}

int				option_ip(t_server *server, char *str)
{
	int			nb;

	nb = ft_atoi(str);
	if (nb == 4)
		return (SUCCESS);
	if (nb == 6)
	{
		server->domain = PF_INET6;
		server->sin.sin_family = AF_INET6;
	}
	else
		return (PERROR("<ip=?> {4,6}; Default : ip=4"));
	return (SUCCESS);
}
