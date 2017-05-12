#include "serveur.h"

t_dic_error g_error[] = 
{
	{SOCKET, "socket() fail."},
	{BIND, "bind() fail."},
	{LISTEN, "listen() fail."},
	{ACCEPT, "accept() fail."},
	{PORT, "port range not valid."},
	{PROTOCOL, "protocol tcp not found."},
	{IPV, "<IPversion?> = {4,6} ; default = 4"},
	{LIMIT, "<limit?> = {1-10} ; default = 10"},
	{NOERROR, 0}
};

static t_env	*singleton(void)
{
	static t_env	sglt;

	return (&sglt);
}

static void		signals_child(int pid)
{
	t_env		*env;

	if (pid == SIGCHLD)
	{
		env = singleton();
		env->connexion--;
	}
}

static int		signals(void)
{
	signal(SIGCHLD, signals_child);
	return (SUCCESS);
}

static int		errors(t_env *env)
{
	if (ERROR)
	{
		debug(env, DEBUG_SERVER);
		ft_printf("{r:1:%-15s}", "ERROR:");
	}
	env->ret = CATCH(g_error);
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	t_env		*env;

	env = singleton();
	parser(env, ac, av);
	signals();
	server(env);
	errors(env);
	return (env->ret);
}