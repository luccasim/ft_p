#include "client.h"

t_dic_error g_client_error[] =
{
	{PROTOCOL, "invalid protocol"},
	{PORT, "invalid port range"},
	{ADDR, "invalid address"},
	{SOCKET, "socket() failed"},
	{CONNECT, "connect() failed"},
	{NOERROR, 0}
};

static int		client_result(t_client *client)
{
	if (ERROR)
	{
		client_debug(client);
		RESPONSE(FAIL);
	}
	return (CATCH(g_client_error));
}

int				main(int ac, char **av)
{
	t_client	client;

	client_parser(ac, av, &client);
	client_init(&client);
	return (client_result(&client));
}