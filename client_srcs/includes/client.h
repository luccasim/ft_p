#ifndef CLIENT_H
# define CLIENT_H

# include "ft_printf.h"
# include "libft.h"
# include "error.h"

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define RESPONSE(a)		(a == SUCCESS) ? PUT_SUCCESS : PUT_ERROR
# define PUT_SUCCESS		ft_printf("{g:1:%-20s}", "SUCCESS:")
# define PUT_ERROR			ft_printf("{r:1:%-20s}", "ERROR:")

# define GET_DOMAIN(a)		(a == PF_INET6) ? "IPv6" : "IPv4"

typedef enum 			client_enum
{
	NOERROR = SUCCESS,
	PROTOCOL,
	PORT,
	ADDR,
	SOCKET,
	CONNECT
}						client_error;

typedef struct			s_client
{
	char*				name;
	int					sock;
	int					domain;
	struct protoent		*protocol;
	struct sockaddr_in	csin;
}						t_client;

int		client_parser(int ac, char **av, t_client *client);
int		client_debug(t_client* client);
int		client_init(t_client *client);

#endif