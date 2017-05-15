#include "serveur.h"
#include "ft_tool.h"
#include <string.h>

static t_server_cmd		g_server_cmd[] =
{
	// {"put", 0, request_put},
	{"pwd", 0, request_pwd},
	{"cd", 0, request_cd},
	{"ls", "/bin/ls", request},
	{"quit", 0, request_quit},
	{0, 0, 0}
};

static int		clients_usage(t_env *env, char *cmd)
{
	display(env, FAIL, CLIENT, cmd);
	ft_fprintf(env->client.sock, "{w:2}Root{e}: shutdown, infos\n");
	ft_fprintf(env->client.sock, "{w:2}Client{e}: get, put.\n");
	ft_fprintf(env->client.sock, "{w:2}Guest{e}: ls, cd, pwd, quit.\n");
	return (SUCCESS);
}

static int		clients_request_set(t_client *c, char *cmd)
{
	char*		res;
	t_request*	r;

	r = &c->request;
	r->request = 0;
	r->cmd = 0;
	r->nb = 0;
	ft_strdelsplit(r->args);
	res = cmd;
	while ((res = ft_strchr(res, '\t')))
		*res = ' ';
	ft_asprintf(&res, "%s %s", cmd, c->pwd);
	r->args = ft_strsplit(res, ' ');
	ft_strdel(&res);
	if (!r->args)
		return (FAIL);
	r->request = cmd;
	r->nb = ft_strstrlen(r->args);
	return (SUCCESS);
}

static int		clients_request(t_env *env, char *str)
{
	int			i;
	char*		key;

	i = 0;
	key = 0;
	str = ft_strtrim(str);
	if (clients_request_set(&env->client, str) == SUCCESS)
	{
		while ((key = g_server_cmd[i].key) != 0)
		{
			if (ft_strequ(env->client.request.args[0], key))
			{
				env->client.request.cmd = g_server_cmd[i].cmd;
				i = g_server_cmd[i].function(&env->client);
				display(env, i, CLIENT, str);
				ft_strdel(&str);
				return (i);
			}
			i++;
		}
	}
	if (!key)
		clients_usage(env, str);
	ft_strdel(&str);
	return (FAIL);
}

static int		clients_handle(t_env *env, t_client *c)
{
	int		ret;
	char	msg[32];

	ret = 1;
	display(env, SUCCESS, CLIENT, "CONNECTED!");
	ft_fprintf(c->sock, "Hello %s, you are connected !\n", c->name);
	c->pwd = ft_strdup("");
	c->old = ft_strdup("");
	while (ret > 0)
	{
		ft_fprintf(c->sock, "[%s]%s%s ", c->name, c->pwd, PROMPT);
		ret = recv(c->sock, msg, 31, 0);
		msg[ret - 1] = 0;
		clients_request(env, msg);
	}
	return (THROW(RECV));
}

int				clients(t_env *env)
{
	t_client	*client;

	client = &env->client;
	ft_asprintf(&client->name, "Guest %d", env->nbrclients);
	clients_handle(env, &env->client);
	return (SUCCESS);
}