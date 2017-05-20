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
	char		msg[MSG_SIZE];

	if (c->login.access > access)
	{
		ft_snprintf(msg, MSG_SIZE, "%s command denied.", cmd);
		message(MSG_RESPONSE, FD_ERROR, msg);
		return (FAIL);
	}
	return (SUCCESS);
}

int				request_quit(t_client *client)
{
	t_env		*env;

	env = singleton();
	display(env, SUCCESS, CLIENT, "DISCONNECTED!");
	message(MSG_RESPONSE, 0, "{y:1}Disconnected!{e}\n");
	message(MSG_RESPONSE, FD_SUCCESS, 0);
	close(client->sock);
	exit(SUCCESS);
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
