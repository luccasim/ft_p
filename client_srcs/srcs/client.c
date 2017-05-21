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

static int		client_send(t_client *c)
{
	char		*line;
	int			ret;

	line = 0;
	ret = get_next_line(0, &line);
	send(c->sock, line, ft_strlen(line) + 1, 0);
	if (ft_strnequ(line, "quit", 4))
		c->sock = 0;
	ft_strdel(&line);
	return (SUCCESS);
}

static int		client_recv(t_client *c)
{
	t_message	msg;

	recv(c->sock, &msg, sizeof(msg), 0);
	msg.receipt = 0;
	ft_fprintf(msg.fd, msg.msg);
	if (msg.type == MSG_REQUEST)
		client_send(c);
	if (msg.type == MSG_DIE)
	{
		close(c->sock);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

static int		client_loop(t_client *c)
{
	while (c->sock)
		client_recv(c);
	return (SUCCESS);
}

static int		client_authentification(t_env *env, t_client *c)
{
	ft_fprintf(1, "authentification!\n");
	client_recv(c);
	send(c->sock, &env->login, sizeof(t_login), 0);
	recv(c->sock, &env->login, sizeof(t_login), 0);
	client_recv(c);
	return (SUCCESS);
}

int				client(t_env *env)
{
	t_client	*c;

	c = &env->client;
	if ((c->sock = socket(PF_INET, SOCK_STREAM, c->proto->p_proto)) == FAIL)
		return (THROW(SOCK));
	if ((connect(c->sock, (const struct sockaddr *)&c->sin,
		sizeof(c->sin))) == FAIL)
		return (THROW(CONNECT));
	client_authentification(env, c);
	client_loop(c);
	return (SUCCESS);
}
