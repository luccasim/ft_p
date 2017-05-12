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

# include "libft.h"
# include "ft_printf.h"
# include "error.h"
# include "ft_time.h"

# define STATE(env, msg)	display(env, ERROR, SERVER, msg)

// Enum error

typedef enum				e_server_enum
{
	NOERROR = SUCCESS,
	SERVER,
	CLIENT,
	SOCKET,
	BIND,
	LISTEN,
	ACCEPT,
	PROTOCOL,
	PORT,
	IPV,
	LIMIT,
	FORK,
	WARNING
}							t_server_enum;

typedef enum				e_server_debug
{
	DEBUG_ALL = 6,
	DEBUG_CLIENT = 2,
	DEBUG_SERVER = 4
}							t_server_debug;

// Struct

typedef struct				s_server
{
	int						port;
	int						sock;
	int						domain;
	int						date;
	int						limit;
	char*					name;
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
	char*					name;
	struct sockaddr_in		csin;
}							t_client;

typedef struct				s_option
{
	int						port;
	int						ipv;
	int						limit;
	int						error;
	char*					name;
}							t_option;

typedef struct				s_env
{
	t_server				server;
	t_client				client;
	int						connexion;
	int						quit;
	int						nbrclients;
	int						ret;
}							t_env;

// Fonctions

int							debug(t_env *env, int what);
int							parser(t_env *env, int ac, char **av);
int							server(t_env *env);
int							clients(t_env *env);
int							display(t_env *env, int state, int who, char *msg);

#endif