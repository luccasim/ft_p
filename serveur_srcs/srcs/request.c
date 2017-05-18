/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:22 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:24 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static t_server_cmd		g_server_cmd[] =
{
	{"put", 0, request_put},
	{"lpwd", 0, request_lpwd},
	{"cmd", 0, request_cmd},
	{"get", 0, request_get},
	{"pwd", 0, request_pwd},
	{"cd", 0, request_cd},
	{"ls", "/bin/ls", request_system},
	{"quit", 0, request_quit},
	{0, 0, 0}
};

int				request_access(t_client *c, char *cmd, int access)
{
	if (c->login.access > access)
	{
		ft_fprintf(c->sock, "{y:1}Error: %s command denied.{e}\n", cmd);
		return (FAIL);
	}
	return (SUCCESS);
}

int				request_cmd(t_client *c)
{
	t_env		*env;
	char		*m;
	char		*u;
	char		*g;

	env = singleton();
	m = "{d:1}Master: %s{e}\n";
	u = "{d:1}User: %s{e}\n";
	if (c->login.access <= MASTER)
		m = "{w:1}Master: %s{e}\n";
	if (c->login.access <= USER)
		u = "{w:1}User: %s{e}\n";
	g = "{w:1}Guest: %s{e}\n";
	ft_fprintf(c->sock, m, "mkdir, rmdir, cp, shutdown.");
	ft_fprintf(c->sock, u, "get, put, lls, lcd, lpwd.");
	ft_fprintf(c->sock, g, "cmd, ls, cd, pwd, quit.");
	return (SUCCESS);
}

static int		request_set(t_client *c, char *cmd)
{
	char		*res;
	t_request	*r;

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

static int		request_state(int state, char *str)
{
	char		cmd[SIZE + 1];
	t_env		*env;
	t_client	*c;

	env = singleton();
	c = &env->client;
	ft_snprintf(cmd, SIZE, "Command: '%s'", str);
	display(env, state, CLIENT, cmd);
	if (state == FAIL)
		request_cmd(&env->client);
	ft_strdel(&str);
	return (SUCCESS);
}

int				request(t_client *c, char *str)
{
	int			i;
	char		*key;

	i = 0;
	key = 0;
	str = ft_strtrim(str);
	if (request_set(c, str) == SUCCESS)
	{
		while ((key = g_server_cmd[i].key) != 0)
		{
			if (ft_strequ(c->request.args[0], key))
			{
				c->request.cmd = g_server_cmd[i].cmd;
				i = g_server_cmd[i].function(c);
				request_state(i, str);
				return (i);
			}
			i++;
		}
	}
	ft_fprintf(c->sock, "{y:1}Error: command '%s' undefined!\n{e}", str);
	request_state(FAIL, str);
	return (FAIL);
}
