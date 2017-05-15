#include "serveur.h"

static int		request_cd_args(t_client *client, char *dest)
{
	char*	pwd;

	if (*(client->pwd) == 0)
		return (FAIL);
	pwd = ft_strrchr(client->pwd, '/');
	if (ft_strequ(dest, ".."))
		dest = (pwd == 0) ? ft_strdup("") : ft_strdup(--dest);
	else if (ft_strequ(dest, "-"))
		dest = ft_strdup(client->old);
	else if (ft_strequ(dest, "~"))
		dest = ft_strdup("");
	else
		return (FAIL);
	ft_strdel(&client->old);
	client->old = client->pwd;
	client->pwd = dest;
	return (SUCCESS);
}

int				request_cd(t_client *client)
{
	char*	dest;

	if (ft_strequ("cd", client->request.request))
	{
		ft_strdel(&client->old);
		client->old = client->pwd;
		client->pwd = ft_strdup("");
		return (SUCCESS);
	}
	dest = client->request.args[1];
	if (request_cd_args(client, dest) == SUCCESS)
		return (SUCCESS);
	if (opendir(dest) == 0)
		return (FAIL);
	ft_strdel(&client->old);
	client->old = client->pwd;
	if (*(client->pwd) != 0)
		asprintf(&dest, "%s/%s", client->pwd, dest);
	else
		dest = ft_strdup(dest);
	client->pwd = dest;
	return (SUCCESS);
}

int				request_pwd(t_client *client)
{
	char*		path;
	t_env*		env;
	int			size;
	char*		format;

	env = singleton();
	format = (*client->pwd == 0) ? "%s%s\n" : "%s/%s\n";
	size = asprintf(&path, format, env->server.path, client->pwd);
	send(client->sock, path, size, 0);
	return (SUCCESS);
}

int				request_quit(t_client *client)
{
	t_env	*env;

	env = singleton();
	display(env, SUCCESS, CLIENT, "DISCONNECTED!");
	ft_fprintf(client->sock, "Disconnected!\n");
	close(client->sock);
	exit(SUCCESS);
}

int				request(t_client *client)
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