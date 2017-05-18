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
	ft_strcpy(c->pwd, "");
	ft_strcpy(c->old, "");
	c->login.access = GUEST;
	c->login.mask = 0;
	ft_sprintf(c->login.name, "Guest %d", env->nbrclients);
	ft_strcpy(c->login.cpath, "");
	ft_strcpy(c->login.spath, env->server.path);
	return (SUCCESS);
}

static int		clients_authentification(t_env *env, t_client *c)
{
	char		*msg;
	t_login		login;

	msg = "{y:1}Welcom to %s, Press Enter to continue{e}\n";
	ft_fprintf(c->sock, msg, env->server.name);
	recv(c->sock, &login, sizeof(t_login), 0);
	if (login.mask == IDENTIFIED)
	{
		ft_strcpy(login.spath, env->server.path);
		ft_memcpy(&c->login, &login, sizeof(login));
		send(c->sock, &c->login, sizeof(t_login), 0);
	}
	ft_strcpy(c->name, c->login.name);
	ft_fprintf(c->sock, "{y:1}Hello %s!{e}\n", c->name);
	display(env, SUCCESS, CLIENT, "CONNECTED!");
	return (SUCCESS);
}

static int		clients_handle(t_client *c)
{
	int			ret;
	char		msg[SIZE + 1];

	ret = 1;
	while (ret > 0)
	{
		ft_fprintf(c->sock, "[%s]%s%s ", c->name, c->pwd, PROMPT);
		ret = recv(c->sock, msg, SIZE, 0);
		msg[ret - 1] = 0;
		request(c, msg);
	}
	return (THROW(RECV));
}

int				clients(t_env *env)
{
	t_client	*client;

	client = &env->client;
	clients_init(client);
	clients_authentification(env, client);
	clients_handle(client);
	return (SUCCESS);
}
