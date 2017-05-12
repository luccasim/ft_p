#include "client.h"

static void		client_usage(char *name)
{
	ft_fprintf(2, "Usage: %s <address IPv4> <port>\n", name);
	exit(FAIL);
}

static char*	client_name(char *name)
{
	char*	str;

	str = ft_strchr(name, '/');
	str = (str) ? ++str : name;
	return (ft_strdup(str));
}

static int		client_setting(t_client *client, char **av)
{
	client->name = client_name(av[0]);
	client->domain = PF_INET;
	if ((client->protocol = getprotobyname("tcp")) == NULL)
		return (THROW(PROTOCOL));
	client->csin.sin_family = AF_INET;
	if ((client->csin.sin_port = htons(ft_atoi(av[2]))) == 0)
		return (THROW(PORT));
	if ((client->csin.sin_addr.s_addr = inet_addr(av[1])) == INADDR_NONE)
		return (THROW(ADDR));
	return (SUCCESS);
}

int				client_parser(int ac, char **av, t_client *client)
{
	if (ac < 3)
		client_usage(av[0]);
	client_setting(client, av);
	return (SUCCESS);
}