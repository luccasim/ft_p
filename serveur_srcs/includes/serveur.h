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

// A virer
#include <stdio.h>

# include "libft.h"
# include "ft_printf.h"
# include "error.h"
# include "ft_time.h"

# define STATE(env, msg)	display(env, ERROR, SERVER, msg)
# define PROMPT				"~>"

/*
**	Enums
*/

typedef enum				e_enum_server_error
{
	NOERROR = SUCCESS,
	SOCKET,
	BIND,
	LISTEN,
	ACCEPT,
	PROTOCOL,
	PORT,
	IPV,
	LIMIT,
	FORK,
	RECV,
	SEND,
	CMD
}							t_enum_server_error;

typedef enum				e_enum_server_other
{
	SERVER,
	CLIENT,
	WARNING,
}							t_enum_server_other;

typedef enum				e_enum_server_debug
{
	DEBUG_ALL = 6,
	DEBUG_CLIENT = 2,
	DEBUG_SERVER = 4
}							t_enum_server_debug;

typedef enum				e_enum_server_access
{
	ROOT = 0,
	USER,
	GUEST
}							t_enum_server_access;

/*
**	Structs
*/

typedef struct				s_request
{
	char*					request;
	char*					cmd;
	char**					args;
	int						nb;
}							t_request;

typedef struct				s_option
{
	int						port;
	int						ipv;
	int						limit;
	int						error;
	char*					name;
}							t_option;

typedef struct				s_server
{
	int						port;
	int						sock;
	int						domain;
	int						date;
	int						limit;
	char*					name;
	char*					path;
	struct protoent			*protocol;
	struct sockaddr_in		sin;
}							t_server;

typedef struct				s_client
{
	int						pid;
	int						port;
	int						sock;
	int						date;
	int						access;
	unsigned int			len;
	char*					name;
	char*					pwd;
	char*					old;
	char*					path;
	t_request				request;
	struct sockaddr_in		csin;
}							t_client;

typedef struct				s_env
{
	t_server				server;
	t_client				client;
	int						connexion;
	int						quit;
	int						nbrclients;
	int						error;
}							t_env;

typedef struct				s_server_cmd
{
	char*					key;
	char*					cmd;
	int						(*function)(t_client *);
}							t_server_cmd;

/*
**	Fonctions
*/

t_env*						singleton(void);
int							request_put(t_client *client);
int							request_cd(t_client *client);
int							request_pwd(t_client *client);
int							request_quit(t_client *client);
int							request(t_client *client);
int							debug(t_env *env, int what);
int							signals(void);
int							errors(t_env *env);
int							parser(t_env *env, int ac, char **av);
int							server(t_env *env);
int							clients(t_env *env);
int							display(t_env *env, int state, int who, char *msg);

#endif