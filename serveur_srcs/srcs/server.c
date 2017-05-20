/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:43 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:45 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int		server_handle_clients(t_env *env, t_server *server)
{
	char			*blockmsg;
	char			*unblockmsg;

	if (env->connexion >= server->limit)
	{
		blockmsg = "SERVER WILL BLOCK NEW CLIENTS.";
		unblockmsg = "SERVER WILL ACCEPT NEW CLIENTS!";
		display(env, WARNING, SERVER, blockmsg);
		wait4(-1, 0, 0, 0);
		display(env, WARNING, SERVER, unblockmsg);
	}
	return (SUCCESS);
}

static int		server_loop(t_env *env, t_server *server, t_client *c)
{
	int					pid;
	int					loop;

	loop = 1;
	while (loop)
	{
		if ((c->sock = accept(server->sock,
			(struct sockaddr *)&c->csin, &c->len)) <= 0)
			return (THROW(ACCEPT));
		++env->connexion;
		++env->nbrclients;
		if ((pid = fork()) == FAIL)
		{
			ft_strlcpy(c->name, inet_ntoa(c->csin.sin_addr), SIZE);
			display(env, FAIL, CLIENT, "NO RESOURCES FOR CONNECT...");
			continue ;
		}
		if (pid == 0)
			clients(env);
		else
			server_handle_clients(env, server);
	}
	return (SUCCESS);
}

int				server(t_env *env)
{
	t_server	*server;

	if (ERROR)
		return (FAIL);
	server = &env->server;
	if ((server->sock = socket(server->domain, SOCK_STREAM,
		server->protocol->p_proto)) == FAIL)
		return (THROW(SOCKET));
	if ((bind(server->sock, (const struct sockaddr *)&server->sin,
		sizeof(server->sin))) == FAIL)
		return (THROW(BIND));
	if (listen(server->sock, server->limit) == FAIL)
		return (THROW(LISTEN));
	STATE(env, "RUNNING!");
	server_loop(env, server, &env->client);
	close(env->server.sock);
	STATE(env, "CLOSED!");
	return (SUCCESS);
}
