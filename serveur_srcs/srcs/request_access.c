#include "serveur.h"

int				request_display(t_client *c)
{
	t_env		*env;

	(void)c;
	env = singleton();
	env->display = (env->display) ? 0 : 1;
	return (SUCCESS);
}

int				request_name(t_client *c)
{
	char		res[SIZE];

	if (request_access(c, "name", ACCESS_MASTER))
		return (FAIL);
	ft_bzero(res, SIZE - 1);
	message(MSG_REQUEST, 0, "Would you change your name?(y/n)\n");
	recv(c->sock, &res, SIZE, 0);
	if (ft_strnequ(res, "y", 1))
	{
		message(MSG_REQUEST, 0, "Set your new name.\n");
		recv(c->sock, &res, SIZE, 0);
		ft_strlcpy(c->name, res, SIZE);
	}
	else
	{
		message(MSG_RESPONSE, FD_ERROR, "Change name operation cancelled\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int				request_mkdir(t_client *c)
{
	if (request_access(c, "mkdir", ACCESS_MASTER))
		return (FAIL);
	return (request_system(c));
}

int				request_rmdir(t_client *c)
{
	char		**args;
	char		msg[SIZE];

	if (request_access(c, "rmdir", ACCESS_MASTER))
		return (FAIL);
	args = c->request.args;
	while (*++args)
	{
		if (ft_strequ(*args, "includes") || ft_strequ(*args, "srcs"))
		{
			ft_snprintf(msg, SIZE, "For security, you can't remove %s", *args);
			message(MSG_RESPONSE, FD_ERROR, msg);
			return (FAIL);
		}
	}
	return (request_system(c));
}

int				request_shutdown(t_client *c)
{
	t_env		*env;

	if (request_access(c, "shutdown", ACCESS_MASTER))
		return (FAIL);
	env = singleton();
	message(MSG_DIE, 0, "You've killed the server...\n");
	close(env->server.sock);
	close(c->sock);
	execl("/bin/kill", "kill", ft_itoa(env->server.pid), 0);
	exit(SUCCESS);
	return (FAIL);
}