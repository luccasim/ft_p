#include "serveur.h"

static int		parser_usage(char *name)
{
	char*	format;

	format = "{w:1}Usage: %s <Port> <IPversion?> <Limit?>\n";
	ft_fprintf(2, format, name);
	exit(FAIL);
}

static int		parser_default(t_server *server, char **av)
{
	server->name = ft_strdup(av[0]);
	server->domain = PF_INET;
	server->sock = -1;
	server->limit = 5;
	server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	server->sin.sin_port = 0;
	server->date = TIMESTAMP;
	return (SUCCESS);
}

static int		parser_optional(t_option *option, int ac, char **av)
{
	option->error = 0;
	option->ipv = 4;
	option->limit = 5;
	if (ac > 1)
	{
		option->port = ft_atoi(av[1]);
		if (option->port == 0)
			option->error = THROW(PORT);
	}
	if (ac > 2)
	{
		option->ipv = ft_atoi(av[2]);
		if (!(option->ipv == 4 || option->ipv == 6))
			option->error = THROW(IPV);
	}
	if (ac > 3)
	{
		option->limit = ft_atoi(av[3]);
		if (option->limit < 0 || option->limit > 10)
			option->error = THROW(LIMIT);
	}
	return (SUCCESS);
}

static int		parser_setting(t_server *server, t_option *option)
{
	if (option->error)
		return (FAIL);
	server->domain = (option->ipv == 4) ? PF_INET : PF_INET6;
	server->limit = option->limit;
	server->port = option->port;
	server->sin.sin_family = (option->ipv == 4) ? AF_INET : AF_INET6;
	server->sin.sin_port = htons(server->port);
	if ((server->protocol = getprotobyname("tcp")) == 0)
		return (THROW(PROTOCOL));
	return (SUCCESS);
}

int				parser(t_env *env, int ac, char **av)
{
	t_server	*server;
	t_option	option;

	if (ac < 2)
		parser_usage(av[0]);
	server = &env->server;
	parser_default(server, av);
	parser_optional(&option, ac, av);
	parser_setting(server, &option);
	STATE(env, "CREATED!");
	return (SUCCESS);
}