/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:06:41 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:06:44 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int		clients_init(t_client *c)
{
	t_env		*env;

	env = singleton();
	ft_strlcpy(c->pwd, "", SIZE);
	ft_strlcpy(c->old, "", SIZE);
	c->login.access = ACCESS_GUEST;
	c->login.mask = 0;
	ft_sprintf(c->login.name, "Guest %d", env->nbrclients);
	ft_strlcpy(c->login.cpath, "", SIZE);
	ft_strlcpy(c->login.spath, env->server.path, SIZE);
	return (SUCCESS);
}

static int		clients_authentification(t_client *c)
{
	char		msg[MSG_SIZE];
	t_login		login;
	t_env		*env;
	t_server	*server;

	env = singleton();
	server = &env->server;
	ft_snprintf(msg, MSG_SIZE, "Welcom to %s!\nPress Enter to continue..\n",
		server->name);
	message(MSG_RESPONSE, 0, msg);
	recv(c->sock, &login, sizeof(t_login), 0);
	if (login.mask == IDENTIFIED)
	{
		ft_strncpy(login.spath, env->server.path, SIZE - 1);
		ft_memcpy(&c->login, &login, sizeof(login));
		send(c->sock, &c->login, sizeof(t_login), 0);
	}
	ft_strlcpy(c->name, c->login.name, SIZE);
	ft_snprintf(msg, MSG_SIZE, "Hello %s!\n", c->name);
	message(MSG_RESPONSE, 0, msg);
	display(env, SUCCESS, CLIENT, "CONNECTED!");
	return (SUCCESS);
}

static int		clients_handle(t_client *c)
{
	int			ret;
	char		msg[SIZE + 1];
	char		prompt[MSG_SIZE];

	ret = 1;
	while (ret > 0)
	{
		ft_snprintf(prompt, MSG_SIZE, "[%s]%s%s ", c->name, c->pwd, PROMPT);
		message(MSG_REQUEST, 0, prompt);
		ret = recv(c->sock, msg, SIZE, 0);
		msg[ret - 1] = 0;
		request(c, msg);
	}
	return (THROW(RECV));
}

int				clients(t_env *env)
{
	t_client	*c;

	c = &env->client;
	clients_init(c);
	clients_authentification(c);
	clients_handle(c);
	return (SUCCESS);
}
