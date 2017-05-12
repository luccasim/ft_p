#include "client.h"

int		client_debug(t_client *client)
{
	PUTSTR("Client structure infos:");
	ft_printf("%-20s%s\n", "NAME:", client->name);
	ft_printf("%-20s%d\n", "SOCKET:", client->sock);
	ft_printf("%-20s%s\n", "DOMAIN:", GET_DOMAIN(client->domain));
	ft_printf("%-20s%s\n", "[PROTOCOL]NAME:", client->protocol->p_name);
	ft_printf("%-20s%d\n", "[PROTOCOL]PROTO:", client->protocol->p_proto);
	ft_printf("%-20s%hhd\n", "[CSIN]FAMILY:", client->csin.sin_family);
	ft_printf("%-20s%u\n", "[CSIN]PORT:", ntohs(client->csin.sin_port));
	ft_printf("%-20s%s\n", "[CSIN]ADDR:", inet_ntoa(client->csin.sin_addr));
	return (SUCCESS);
}