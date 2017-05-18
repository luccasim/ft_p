#include "serveur.h"

int				request_cd(t_client *client)
{
	char*	dest;
	DIR*	dir;

	if (ft_strequ("cd", client->request.request))
	{
		ft_strcpy(client->old, client->pwd);
		ft_strcpy(client->pwd, "");
		return (SUCCESS);
	}
	dest = client->request.args[1];
	if ((dir = opendir(dest)) == 0)
		return (FAIL);
	ft_strcpy(client->old, client->pwd);
	if (client->pwd[0] != 0)
		ft_sprintf(client->pwd, "%s/%s", client->pwd, dest);
	else
		ft_strcpy(client->pwd, dest);
	closedir(dir);
	return (SUCCESS);
}

int				request_pwd(t_client *client)
{
	t_env*		env;
	char*		format;

	env = singleton();
	format = (client->pwd[0] == 0) ? "%s%s\n" : "%s/%s\n";
	ft_fprintf(client->sock, format, env->server.path, client->pwd);
	return (SUCCESS);
}

int				request_quit(t_client *client)
{
	t_env	*env;

	env = singleton();
	display(env, SUCCESS, CLIENT, "DISCONNECTED!");
	ft_fprintf(client->sock, "{y:1}Disconnected!{e}\n");
	close(client->sock);
	exit(SUCCESS);
}

int				request_system(t_client *client)
{
	int			pid;
	int			status;
	t_request	*r;

	pid = fork();
	if (pid == 0)
	{
		r = &client->request;
		dup2(client->sock, 1);
		dup2(client->sock, 2);
		execv(r->cmd, r->args);
		close(client->sock);
		exit(SUCCESS);
	}
	else
		wait4(pid, &status, 0, 0);
	return (SUCCESS);
}