/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:45:52 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 16:46:04 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		client_recv(t_client *c)
{
	char		buf[4095];
	int			ret;

	ret = 1;
	while (ret)
	{
		ret = read(c->sock, buf, 4096);
		if (ret <= 1)
			return (FAIL);
		buf[ret] = 0;
		write(0, buf, ret);
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int		client_send(t_client *c)
{
	char		*line;
	int			ret;

	line = 0;
	ret = get_next_line(0, &line);
	send(c->sock, line, ft_strlen(line) + 1, 0);
	ft_strdel(&line);
	client_recv(c);
	if (ret == FAIL)
		return (THROW(READ));
	return (SUCCESS);
}

static int		client_loop(t_client *c)
{
	while (client_recv(c) >= SUCCESS)
	{
		if (client_send(c) != SUCCESS)
			return (FAIL);
	}
	return (SUCCESS);
}

static int		client_authentification(t_env *env, t_client *c)
{
	client_recv(c);
	send(c->sock, &env->login, sizeof(t_login), 0);
	recv(c->sock, &env->login, sizeof(t_login), 0);
	client_recv(c);
	return (SUCCESS);
}

int				client(t_env *env)
{
	t_client	*c;
	t_server	*s;

	c = &env->client;
	s = &env->server;
	if ((c->sock = socket(PF_INET, SOCK_STREAM, c->proto->p_proto)) == FAIL)
		return (THROW(SOCK));
	if ((connect(c->sock, (const struct sockaddr *)&c->sin,
		sizeof(c->sin))) == FAIL)
		return (THROW(CONNECT));
	client_authentification(env, c);
	client_loop(c);
	return (SUCCESS);
}
