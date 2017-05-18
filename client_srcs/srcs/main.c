/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:54:53 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 16:55:04 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int		set_env(t_env *env, char **av)
{
	char		*path;

	path = getcwd(0, 0);
	env->error = SUCCESS;
	ft_strcpy(env->login.name, av[0]);
	ft_strcpy(env->login.cpath, path);
	ft_strcpy(env->login.spath, "(undefined).");
	env->login.mask = IDENTIFIED;
	ft_strcpy(env->client.name, av[0]);
	ft_strcpy(env->client.addr, "0.0.0.0");
	env->client.port = 0;
	env->client.access = USER;
	ft_strdel(&path);
	return (SUCCESS);
}

t_env			*singleton(void)
{
	static t_env	sglt;

	return (&sglt);
}

int				main(int ac, char **av)
{
	t_env	*env;

	env = singleton();
	set_env(env, av);
	parser(env, ac, av);
	client(env);
	errors(env);
	return (env->error);
}
