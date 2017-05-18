#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# include "ft_printf.h"
# include "libft.h"
# include "error.h"
# include "get_next_line.h"

# define SIZE				128
# define IDENTIFIED			424242

/*
** Enums
*/

typedef enum				e_enum_server_access
{
	MASTER = 1,
	USER,
	GUEST
}							t_enum_server_access;

typedef enum 				client_enum
{
	NOERROR = SUCCESS,
	PROTOCOL,
	ADDR,
	PORT,
	ACCESS,
	SOCK,
	CONNECT,
	READ
}							client_error;

typedef enum				s_client_debug
{
	ALL = 0,
	LOGIN = 2,
	CLIENT = 4,
}							t_client_debug;

typedef struct				s_login
{
	int						mask;
	int						access;
	char					name[SIZE];
	char					cpath[SIZE];
	char					spath[SIZE];
}							t_login;

typedef struct				s_client
{
	char					name[SIZE];
	char					addr[SIZE];
	int						port;
	int						access;
	int						sock;
	struct protoent			*proto;
	struct sockaddr_in		sin;
}	 						t_client;

typedef struct				s_server
{
	struct sockaddr_in		sin;
}							t_server;

typedef struct				s_env
{
	int						error;
	t_login					login;
	t_client				client;
	t_server				server;
}							t_env;

t_env*						singleton(void);
int							errors(t_env *env);
int							parser(t_env *env, int ac, char **av);
int							client(t_env *env);
int							debug(int act);

#endif