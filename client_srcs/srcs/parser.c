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

static t_dict_option g_options[] =
{
	{"name=", option_name},
	{"access=", option_access},
	{0, 0}
};

static int		parser_usage(char *name)
{
	ft_fprintf(2, "{w:1}Usage: %s <address IPv4> <port> <access?>{e}\n", name);
	exit(FAIL);
	return (FAIL);
}

static int		parser_seek(t_client *c, char *str)
{
	int			i;
	char		*res;

	i = 0;
	while (g_options[i].key != 0)
	{
		
		if (ft_strnequ(g_options[i].key, str, ft_strlen(g_options[i].key)))
		{
			res = ft_strchr(str, '=');
			if (g_options[i].function(c, ++res) == SUCCESS)
				return (SUCCESS);
			else
				break ;
		}
		i++;
	}
	ft_fprintf(2, "{w:1}Optional '%s' unvalid.{e}\n", str);
	parser_usage(c->name);
	return (FAIL);
}

static int		parser_optional(t_client *c, int ac, char **av)
{
	int			i;

	if (ERROR)
		return (FAIL);
	i = 3;
	while (i < ac)
	{
		parser_seek(c, av[i]);
		i++;
	}
	return (SUCCESS);
}

static int		parser_value(t_client *c, char **av)
{
	char		tmp[SIZE];

	ft_strlcpy(c->name, av[0], SIZE);
	if (ft_strequ("localhost", av[1]))
		ft_strlcpy(tmp, "127.0.0.1", SIZE);
	else
		ft_strlcpy(tmp, av[1], SIZE);
	if ((inet_aton(tmp, &c->sin.sin_addr)) == (int)INADDR_NONE)
		return (THROW(ADDR));
	if ((c->port = ft_atoi(av[2])) == 0)
		return (THROW(PORT));
	if ((c->proto = getprotobyname("tcp")) == 0)
		return (THROW(PROTOCOL));
	c->sin.sin_family = AF_INET;
	c->sin.sin_port = htons(c->port);
	return (SUCCESS);
}

int				parser(t_env *env, int ac, char **av)
{
	if (ac < 3)
		parser_usage(av[0]);
	parser_value(&env->client, av);
	parser_optional(&env->client, ac, av);
	return (SUCCESS);
}
