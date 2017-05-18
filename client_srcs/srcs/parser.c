/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:51:16 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 16:51:46 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		parser_usage(char *name)
{
	ft_fprintf(2, "Usage: %s <address IPv4> <port> <access?>\n", name);
	exit(FAIL);
}

static int		parser_optional(t_client *c, int ac, char **av)
{
	int			i;
	char		*res;
	int			nb;

	i = 3;
	if (ERROR)
		return (FAIL);
	while (i < ac)
	{
		if (ft_strnequ(av[i], "access=", 7))
		{
			res = ft_strchr(av[i], '=');
			nb = ft_atoi(++res);
			if (nb >= MASTER && nb <= GUEST)
				c->access = nb;
			else
				return (THROW(ACCESS));
		}
		i++;
	}
	return (SUCCESS);
}

static int		parser_value(t_client *c, char **av)
{
	ft_strcpy(c->name, av[0]);
	if (ft_strequ("localhost", av[1]))
		ft_strcpy(av[1], "127.0.0.1");
	if (inet_aton(av[1], &c->sin.sin_addr) == 1)
		ft_strcpy(c->addr, av[1]);
	else
		return (THROW(ADDR));
	if ((c->port = ft_atoi(av[2])) != 0)
		c->port = htons(c->port);
	else
		return (THROW(PORT));
	return (SUCCESS);
}

static int		parser_merge(t_env *env)
{
	if (ERROR)
		return (FAIL);
	ft_strcpy(env->login.name, env->client.name);
	env->login.access = env->client.access;
	env->client.proto = getprotobyname("tcp");
	env->client.sin.sin_family = AF_INET;
	env->client.sin.sin_port = env->client.port;
	env->client.sin.sin_addr.s_addr = inet_addr(env->client.addr);
	return (SUCCESS);
}

int				parser(t_env *env, int ac, char **av)
{
	if (ac < 3)
		parser_usage(av[0]);
	parser_value(&env->client, av);
	parser_optional(&env->client, ac, av);
	parser_merge(env);
	return (SUCCESS);
}
