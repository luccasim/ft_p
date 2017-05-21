/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:43:00 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:43:02 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <netdb.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "error.h"
# include "ft_time.h"

# define STATE(env, msg)	display(env, ERROR, SERVER, msg)
# define IDENTIFIED			424242
# define SIZE				128
# define MSG_SIZE 			2048

/*
**	Enums
*/

typedef enum				e_enum_errors
{
	NOERROR = SUCCESS,
	SOCKET,
	BIND,
	LISTEN,
	ACCEPT,
	PROTOCOL,
	PORT,
	FORK,
	RECV,
	SEND,
	CMD,
	PWD
}							t_enum_errors;

typedef enum				e_enum_server_other
{
	SERVER,
	CLIENT,
	WARNING,
}							t_enum_server_other;

typedef enum				e_enum_debug
{
	DEBUG_CLIENT = 2,
	DEBUG_SERVER = 4,
	DEBUG_LOGIN = 8,
	DEBUG_ALL = 14,
}							t_enum_debug;

typedef enum				e_enum_access
{
	ACCESS_MASTER = 1,
	ACCESS_USER,
	ACCESS_GUEST
}							t_enum_access;

typedef enum				e_enum_fd
{
	FD_SUCCESS = 1,
	FD_ERROR = 2
}							t_enum_fd;

typedef enum				e_enum_msg
{
	MSG_RESPONSE,
	MSG_REQUEST,
	MSG_DIE
}							t_enum_msg;

/*
**	Structs
*/

typedef struct				s_login
{
	int						mask;
	int						access;
	char					name[SIZE];
	char					cpath[SIZE];
	char					spath[SIZE];
}							t_login;

typedef struct				s_message
{
	char					msg[MSG_SIZE];
	int						fd;
	t_enum_msg				type;
	int						receipt;
}							t_message;

typedef struct				s_request
{
	char					*request;
	char					*cmd;
	char					**args;
	int						nb;
}							t_request;

typedef struct				s_server
{
	int						port;
	int						sock;
	int						domain;
	int						date;
	int						limit;
	int						pid;
	char					name[SIZE];
	char					path[SIZE];
	struct protoent			*protocol;
	struct sockaddr_in		sin;
}							t_server;

typedef struct				s_client
{
	int						pid;
	int						port;
	int						sock;
	int						date;
	unsigned int			len;
	char					name[SIZE];
	char					pwd[SIZE];
	char					old[SIZE];
	char					prompt[SIZE];
	t_login					login;
	t_request				request;
	struct sockaddr_in		csin;
}							t_client;

typedef struct				s_env
{
	t_server				server;
	t_client				client;
	int						connexion;
	int						nbrclients;
	int						display;
	int						error;
}							t_env;

/*
** Dictionary
*/

typedef struct				s_dict_option
{
	char					*key;
	int						(*function)(t_server *, char *);
}							t_dict_option;

typedef struct				s_dict_cmd
{
	char					*key;
	char					*cmd;
	int						(*function)(t_client *);
}							t_dict_cmd;

/*
**	Fonctions
*/

t_env						*singleton(void);
int							debug(int what);
int							errors(t_env *env);
int							parser(t_env *env, int ac, char **av);
int							server(t_env *env);
int							clients(t_env *env);
int							display(t_env *env, int state, int who, char *msg);
int							message(int type, int fd, char *str);
int							transfert(char *str, char *dst, char *file);
int							request(t_client *client, char *cmd);
int							request_cmd(t_client *client);
int							request_get(t_client *client);
int							request_put(t_client *client);
int							request_cd(t_client *client);
int							request_pwd(t_client *client);
int							request_lpwd(t_client *client);
int							request_lls(t_client *client);
int							request_lcd(t_client *client);
int							request_quit(t_client *client);
int							request_system(t_client *client);
int							request_access(t_client *c, char *cmd, int access);
int							request_shutdown(t_client *c);
int							request_mkdir(t_client *c);
int							request_rmdir(t_client *c);
int							request_prompt(t_client *c);
int							request_display(t_client *c);
int							request_name(t_client *c);
int							option_ip(t_server *server, char *str);
int							option_limit(t_server *server, char *str);
int							option_name(t_server *server, char *str);
int							option_display(t_server *server, char *str);

#endif
