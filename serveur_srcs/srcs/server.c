#include "serveur.h"

static int		server_close(t_env *env)
{
	display(env, ERROR, SERVER, "CLOSED!");
	close(env->server.sock);
	return (SUCCESS);
}

static int		server_connexions(t_env *env, t_server *server)
{
	char			*blockmsg;
	char			*unblockmsg;

	if (env->connexion >= server->limit)
	{
		blockmsg = "CLIENTS LIMIT REACHED, SERVER WILL BLOCK NEW CLIENTS...";
		unblockmsg = "RESOURCES RELEASES, SERVER WILL ACCEPT NEW CLIENTS!";
		display(env, WARNING, SERVER, blockmsg);
		wait4(-1, 0, WNOHANG, 0);
		display(env, WARNING, SERVER, unblockmsg);
	}
	return (SUCCESS);
}

static int		server_client(t_env *env, t_server *server, t_client *client)
{
	int					pid;

	env->quit = FAIL;
	while (env->quit)
	{
		if ((client->sock = accept(server->sock, 
			(struct sockaddr *)&client->csin, &client->len)) == FAIL)
			return (THROW(ACCEPT));
		env->connexion++;
		env->nbrclients++;
		if ((pid = fork()) == FAIL)
		{
			client->name = inet_ntoa(client->csin.sin_addr);
			display(env, FAIL, CLIENT, "NO RESOURCES FOR CONNECT...");
			continue ;
		}
		if (pid == 0)
			clients(env);
		else
			server_connexions(env, server);
	}
	return (SUCCESS);
}

int				server(t_env *env)
{
	t_server	*server;

	if (ERROR)
		return (FAIL);
	server = &env->server;
	if ((server->sock = socket(server->domain, SOCK_STREAM,
		server->protocol->p_proto)) == FAIL)
		return (THROW(SOCKET));
	if ((bind(server->sock, (const struct sockaddr *)&server->sin, 
		sizeof(server->sin))) == FAIL)
		return (THROW(BIND));
	if (listen(server->sock, server->limit) == FAIL)
		return (THROW(LISTEN));
	STATE(env, "RUNNING!");
	server_client(env, server, &env->client);
	server_close(env);
	return (SUCCESS);
}