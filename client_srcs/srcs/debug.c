#include "client.h"

static int	debug_client(t_client *c)
{
	ft_printf("{c:1:%s}\n", "Client struct:");
	ft_printf("{c}%-10s%s{e}\n", "NAME:", c->name);
	ft_printf("{c}%-10s%s{e}\n", "ADDR:", c->addr);
	ft_printf("{c}%-10s%d{e}\n", "ACCESS:", c->access);	
	ft_printf("{c}%-10s%d{e}\n", "SOCK:", c->sock);	
	ft_printf("{c}%-10s%hu{e}\n", "PORT:", ntohs(c->sin.sin_port));
	if (c->proto)
		ft_printf("{c}%-10s%s{e}\n", "PROTO:", c->proto->p_name);
	ft_printf("{c}%-10s%d{e}\n", "FAMILY:", c->sin.sin_family);
	ft_printf("{c}%-10s%s{e}\n", "ADDR:", inet_ntoa(c->sin.sin_addr));
	return (SUCCESS);
}

static int	debug_login(t_login *l)
{
	ft_printf("{c:1:%s}\n", "Login struct:");
	ft_printf("{c}%-10s%d{e}\n", "MASK:", l->mask);
	ft_printf("{c}%-10s%d{e}\n", "ACCESS:", l->access);
	ft_printf("{c}%-10s%s{e}\n", "NAME:", l->name);
	ft_printf("{c}%-10s%s{e}\n", "CPATH:", l->cpath);
	ft_printf("{c}%-10s%s{e}\n", "SPATH:", l->spath);
	return (SUCCESS);
}

int		debug(int act)
{
	t_env	*env;

	env = singleton();
	ft_printf("{b:1:%s}\n", "Debug infos:");
	if (act & LOGIN)
		debug_login(&env->login);
	if (act & CLIENT)
		debug_client(&env->client);
	return (SUCCESS);
}