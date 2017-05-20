/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:51 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:53 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int		debug_server(t_server *server)
{
	char	*domain;

	domain = (server->domain == PF_INET6) ? "IPv6" : "IPv4";
	ft_printf("{c:1:%s{e}\n", "Server infos:");
	ft_printf("{c}%-15s%s{e}\n", "NAME:", server->name);
	ft_printf("{c}%-15s%d{e}\n", "SOCKET:", server->sock);
	ft_printf("{c}%-15s%hu{e}\n", "PORT:", ntohs(server->sin.sin_port));
	ft_printf("{c}%-15s%s{e}\n", "DOMAIN:", domain);
	ft_printf("{c}%-15s%hk{e}\n", "CREATED AT:", server->date);
	if (!server->protocol)
		ft_printf("{c}%-15s%s{e}\n", "PROTOCOL:", server->protocol->p_name);
	ft_printf("{c}%-15s%d{e}\n", "FAMILY:", server->sin.sin_family);
	ft_printf("{c}%-15s%s{e}\n", "ADDR:", inet_ntoa(server->sin.sin_addr));
	ft_printf("{c}%-15s%d{e}\n", "MAX CONNEXION:", server->limit);
	return (SUCCESS);
}

static int		debug_client(t_client *client)
{
	ft_printf("{c:1:%s{e}\n", "Client infos:");
	ft_printf("{c}%-15s%s{e}\n", "NAME:", client->name);
	ft_printf("{c}%-15s%s{e}\n", "PWD:", client->pwd);
	ft_printf("{c}%-15s%s{e}\n", "OLD:", client->old);
	ft_printf("{c}%-15s%d{e}\n", "PID:", client->pid);
	ft_printf("{c}%-15s%d{e}\n", "SOCKET:", client->sock);
	ft_printf("{c}%-15s%hhu{e}\n", "PORT:", ntohs(client->csin.sin_port));
	ft_printf("{c}%-15s%hk{e}\n", "CREATED AT:", client->date);
	ft_printf("{c}%-15s%d{e}\n", "FAMILY:", client->csin.sin_family);
	ft_printf("{c}%-15s%s{e}\n", "ADDR:", inet_ntoa(client->csin.sin_addr));
	return (SUCCESS);
}

static int		debug_login(t_login *l)
{
	ft_printf("{c:1:%s}\n", "Login infos:");
	ft_printf("{c}%-10s%d{e}\n", "MASK:", l->mask);
	ft_printf("{c}%-10s%d{e}\n", "ACCESS:", l->access);
	ft_printf("{c}%-10s%s{e}\n", "NAME:", l->name);
	ft_printf("{c}%-10s%s{e}\n", "CPATH:", l->cpath);
	ft_printf("{c}%-10s%s{e}\n", "SPATH:", l->spath);
	return (SUCCESS);
}

int				debug(int what)
{
	t_env	*env;

	env = singleton();
	ft_printf("{p:1:%s}\n", "Debug infos:");
	if (what & DEBUG_SERVER)
		debug_server(&env->server);
	if (what & DEBUG_CLIENT)
		debug_client(&env->client);
	if (what & DEBUG_LOGIN)
		debug_login(&env->client.login);
	return (SUCCESS);
}
