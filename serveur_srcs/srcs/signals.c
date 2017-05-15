#include "serveur.h"

static void		signals_handle(int pid)
{
	t_env		*env;

	env = singleton();
	if (pid == SIGCHLD)
		env->connexion--;
	if (pid == SIGQUIT)
		STATE(env, "CLOSED!");
}

int				signals(void)
{
	signal(SIGCHLD, signals_handle);
	signal(SIGQUIT, signals_handle);
	return (SUCCESS);
}