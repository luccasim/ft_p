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

	env->error = SUCCESS;
	ft_strlcpy(env->login.name, av[0], SIZE);
	ft_strlcpy(env->login.spath, "", SIZE);
	env->login.mask = IDENTIFIED;
	env->client.port = 0;
	env->client.access = ACCESS_USER;
	env->login.access = ACCESS_USER;
	if ((path = getcwd(0, 0)) == 0)
		return (THROW(GETCWD));
	ft_strlcpy(env->client.name, av[0], SIZE);
	ft_strlcpy(env->login.cpath, path, SIZE);
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
