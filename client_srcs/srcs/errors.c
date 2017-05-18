#include "client.h"

t_dic_error g_client_error[] =
{
	{PROTOCOL, "invalid protocol"},
	{PORT, "invalid port range"},
	{ADDR, "invalid address"},
	{ACCESS, "<access?> access={1-3}"},
	{SOCK, "socket() failed."},
	{CONNECT, "connect() failed."},
	{NOERROR, 0}
};

int		errors(t_env *env)
{
	if (ERROR)
		ft_fprintf(2, "{r:1:%-10s}", "ERROR:");
	env->error = CATCH(g_client_error);
	close(env->client.sock);
	return (env->error);
}