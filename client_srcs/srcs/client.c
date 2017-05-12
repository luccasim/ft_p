#include "client.h"

int		client_init(t_client *client)
{
	if (ERROR)
		return (FAIL);
	if ((client->sock = socket(client->domain, 
		SOCK_STREAM, client->protocol->p_proto)) == FAIL)
		return (THROW(SOCKET));
	RESPONSE(ERROR);
	ft_printf("%s CREATED!\n", client->name);
	if ((connect(client->sock, (struct sockaddr *)&client->csin,
		sizeof(client->csin))) == FAIL)
		return (THROW(CONNECT));
	return (SUCCESS);
}