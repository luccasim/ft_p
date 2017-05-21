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

static t_dict_cmd		g_cmds[] =
{
	{"put", 0, request_put},
	{"lpwd", 0, request_lpwd},
	{"lls", "/bin/ls", request_lls},
	{"lcd", 0, request_lcd},
	{"cmd", 0, request_cmd},
	{"get", 0, request_get},
	{"pwd", 0, request_pwd},
	{"cd", 0, request_cd},
	{"ls", "/bin/ls", request_system},
	{"quit", 0, request_quit},
	{"shutdown", "/bin/kill", request_shutdown},
	{"display", 0, request_display},
	{"mkdir", "/bin/mkdir", request_mkdir},
	{"rmdir", "/bin/rmdir", request_rmdir},
	{"name", 0, request_name},
	{"prompt", 0, request_prompt},
	{0, 0, 0}
};

int				request_cmd(t_client *c)
{
	char		*m;
	char		*u;
	char		*g;
	char		msg[MSG_SIZE];
	char		tmp[SIZE];

	m = "{d:1}Master: %s{e}\n";
	u = "{d:1}User: %s{e}\n";
	if (c->login.access <= ACCESS_MASTER)
		m = "{w:1}Master: %s{e}\n";
	if (c->login.access <= ACCESS_USER)
		u = "{w:1}User: %s{e}\n";
	g = "{w:1}Guest: %s{e}\n";
	msg[0] = 0;
	ft_snprintf(tmp, SIZE, m, "display, mkdir, rmdir, name, shutdown.");
	ft_strcat(msg, tmp);
	ft_snprintf(tmp, SIZE, u, "get, put, lls, lcd, lpwd, prompt.");
	ft_strcat(msg, tmp);
	ft_snprintf(tmp, SIZE, g, "cmd, ls, cd, pwd, quit.");
	ft_strcat(msg, tmp);
	message(MSG_RESPONSE, 0, msg);
	return (SUCCESS);
}

int				request_access(t_client *c, char *cmd, int access)
{
	char		msg[MSG_SIZE];

	if (c->login.access > access)
	{
		ft_snprintf(msg, MSG_SIZE, "%s command denied.", cmd);
		message(MSG_RESPONSE, FD_ERROR, msg);
		return (FAIL);
	}
	return (SUCCESS);
}

static int		request_set(t_client *c, char *cmd)
{
	char		*res;
	t_request	*r;

	if (!cmd)
		exit(FAIL);
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
	char		cmd[SIZE];
	t_env		*env;
	t_client	*c;

	env = singleton();
	c = &env->client;
	ft_snprintf(cmd, SIZE, "COMMAND: '%s'", str);
	display(env, state, CLIENT, cmd);
	if (state == SUCCESS)
		message(MSG_RESPONSE, FD_SUCCESS, 0);
	if (state == 1)
	{
		ft_snprintf(cmd, SIZE, "Command: '%s' undefined!", str);
		message(MSG_RESPONSE, FD_ERROR, cmd);
	}
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
		while ((key = g_cmds[i].key) != 0)
		{
			if (ft_strequ(c->request.args[0], key))
			{
				c->request.cmd = g_cmds[i].cmd;
				i = g_cmds[i].function(c);
				request_state(i, str);
				return (i);
			}
			i++;
		}
	}
	request_state(1, str);
	return (FAIL);
}
