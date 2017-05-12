#include "serveur.h"
#include <stdio.h>

static int	clients_exit(t_env *env)
{
	display(env, SUCCESS, CLIENT, "DISCONNECT!");
	return (SUCCESS);
}

int			clients(t_env *env)
{
	t_client	*client;
	t_server	*server;

	client = &env->client;
	server = &env->server;
	asprintf(&client->name, "client %d: [%s]", 
		client->pid, inet_ntoa(client->csin.sin_addr));
	display(env, SUCCESS, CLIENT, "CONNECTED!");
	send(client->sock, "Bonjour\n", 8, 0);
	clients_exit(env);
	exit(SUCCESS);
}