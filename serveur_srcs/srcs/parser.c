/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:16 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:19 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static t_dict_option g_options[] =
{
	{"ip=", option_ip},
	{"name=", option_name},
	{"limit=", option_limit},
	{0, 0}
};

static int		parser_usage(char *name)
{
	char		*format;

	format = "{w:1}Usage: %s <Port> <ip=?> <limit=?> <name=?>\n";
	ft_fprintf(2, format, name);
	exit(FAIL);
}

static int		parser_seek(t_server *server, char *str)
{
	int			i;
	char		*res;

	i = 0;
	res = 0;
	while (g_options[i].key != 0)
	{
		if (ft_strnequ(g_options[i].key, str, ft_strlen(g_options[i].key)))
		{
			res = ft_strchr(str, '=');
			if ((g_options[i].function(server, ++res)) == SUCCESS)
				return (SUCCESS);
			else
				break ;
		}
		i++;
	}
	ft_fprintf(2, "{w:1}Optional '%s' unvalid!\n{e}", str);
	parser_usage(server->name);
	return (FAIL);
}

static int		parser_optionals(t_server *server, int ac, char **av)
{
	int			j;

	if (ERROR)
		return (FAIL);
	j = 2;
	while (j < ac)
	{
		parser_seek(server, av[j]);
		j++;
	}
	return (SUCCESS);
}

static int		parser_value(t_server *server, char **av)
{
	if ((server->protocol = getprotobyname("tcp")) == 0)
		return (THROW(PROTOCOL));
	if ((server->port = ft_atoi(av[1])) == 0)
		return (THROW(PORT));
	server->sin.sin_port = htons(server->port);
	server->domain = PF_INET;
	server->sin.sin_family = AF_INET;
	server->limit = 5;
	return (SUCCESS);
}

int				parser(t_env *env, int ac, char **av)
{
	t_server	*server;

	if (ac < 2)
		parser_usage(av[0]);
	server = &env->server;
	parser_value(server, av);
	parser_optionals(server, ac, av);
	STATE(env, "CREATED!");
	return (SUCCESS);
}
