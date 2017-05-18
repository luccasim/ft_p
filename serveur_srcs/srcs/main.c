/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:09 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:11 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

t_env			*singleton(void)
{
	static t_env	sglt;

	return (&sglt);
}

static int		set_env(t_env *env, char **av)
{
	t_server	*server;

	server = &env->server;
	env->error = SUCCESS;
	env->nbrclients = 0;
	env->connexion = 0;
	env->quit = FAIL;
	server->name = av[0];
	server->domain = PF_INET;
	server->sock = -1;
	server->limit = 5;
	server->path = getcwd(0, 0);
	server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	server->sin.sin_port = 0;
	server->date = TIMESTAMP;
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	t_env		*env;

	env = singleton();
	set_env(env, av);
	parser(env, ac, av);
	signals();
	server(env);
	errors(env);
	return (env->error);
}
