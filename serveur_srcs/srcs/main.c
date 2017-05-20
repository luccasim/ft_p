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


static void		signals_handle(int pid)
{
	t_env		*env;

	env = singleton();
	if (pid == SIGCHLD)
		env->connexion--;
	if (pid == SIGQUIT)
		STATE(env, "CLOSED!");
}

static int		env_init(t_env *env, char **av)
{
	t_server	*server;
	char		*server_path;

	server = &env->server;
	env->error = SUCCESS;
	env->nbrclients = 0;
	env->connexion = 0;
	server->domain = PF_INET;
	server->sock = -1;
	server->limit = 5;
	server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	server->sin.sin_port = 0;
	server->date = TIMESTAMP;
	if (!(server_path = getcwd(0,0)))
		return (THROW(PWD));
	ft_strlcpy(server->name, av[0], SIZE);
	ft_strlcpy(server->path, server_path, SIZE);
	ft_strdel(&server_path);
	signal(SIGCHLD, signals_handle);
	signal(SIGQUIT, signals_handle);
	return (SUCCESS);
}

t_env			*singleton(void)
{
	static t_env	sglt;

	return (&sglt);
}

int				main(int ac, char **av)
{
	t_env		*env;

	env = singleton();
	env_init(env, av);
	parser(env, ac, av);
	server(env);
	errors(env);
	return (env->error);
}
