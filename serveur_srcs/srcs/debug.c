#include "serveur.h"

static int	debug_server(t_server *server)
{
	char*	domain;

	domain = (server->domain == PF_INET6) ? "IPv6" : "IPv4";
	ft_printf("{y:1:%s}\n", "Server infos:");
	ft_printf("%-15s%s\n", "NAME:", server->name);
	ft_printf("%-15s%d\n", "SOCKET:", server->sock);
	ft_printf("%-15s%hhu\n", "PORT:", ntohs(server->sin.sin_port));
	ft_printf("%-15s%s\n", "DOMAIN:", domain);
	ft_printf("%-15s%hk\n", "CREATED AT:", server->date);
	if (!server->protocol)
		ft_printf("%-15s%s\n", "PROTOCOL:", server->protocol->p_name);
	ft_printf("%-15s%d\n", "FAMILY:", server->sin.sin_family);
	ft_printf("%-15s%s\n", "ADDR:", inet_ntoa(server->sin.sin_addr));
	ft_printf("%-15s%d\n", "MAX CONNEXION:", server->limit);
	return (SUCCESS);
}

static int	debug_client(t_client *client)
{
	ft_printf("{y:1:%s}\n", "Client infos:");
	ft_printf("%-15s%s\n", "NAME:", client->name);
	ft_printf("%-15s%s\n", "PID:", client->pid);
	ft_printf("%-15s%d\n", "SOCKET:", client->sock);
	ft_printf("%-15s%hhu\n", "PORT:", ntohs(client->csin.sin_port));
	ft_printf("%-15s%hk\n", "CREATED AT:", client->date);
	ft_printf("%-15s%d\n", "FAMILY:", client->csin.sin_family);
	ft_printf("%-15s%s\n", "ADDR:", inet_ntoa(client->csin.sin_addr));
	return (SUCCESS);
}

int		debug(t_env *env, int what)
{
	ft_printf("{r:1:%s}\n", "Debug infos:");
	if (what & DEBUG_SERVER)
		debug_server(&env->server);
	if (what & DEBUG_CLIENT)
		debug_client(&env->client);
	return (SUCCESS);
}