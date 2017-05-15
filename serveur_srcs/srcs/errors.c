#include "serveur.h"

static t_dic_error g_error[] = 
{
	{SOCKET, "socket() fail."},
	{BIND, "bind() fail."},
	{LISTEN, "listen() fail."},
	{ACCEPT, "accept() fail."},
	{PORT, "port range not valid."},
	{PROTOCOL, "protocol tcp not found."},
	{IPV, "<IPversion?> = {4,6} ; default = 4"},
	{LIMIT, "<limit?> = {1-10} ; default = 10"},
	{RECV, "recv() fail."},
	{NOERROR, 0}
};

int		errors(t_env *env)
{
	if (ERROR)
	{
		debug(env, DEBUG_SERVER);
		ft_printf("{r:1:%-15s}", "ERROR:");
	}
	env->error = CATCH(g_error);
	return (SUCCESS);
}