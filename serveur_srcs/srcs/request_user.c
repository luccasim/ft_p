#include "serveur.h"

static int		request_fileexist(t_client *c, char *path, char *file)
{
	DIR*			dir;
	struct dirent	*dp;

	if ((dir = opendir(path)) == 0)
		return (FAIL);
	while ((dp = readdir(dir)) != 0)
	{
		if (ft_strequ(dp->d_name, file))
		{
			closedir(dir);
			if (dp->d_type == DT_REG)
				return (SUCCESS);
			else
			{
				ft_fprintf(c->sock, "{y:1}'%s' is not a file!{e}\n", c, file);
				return (FAIL);
			}
		}
	}
	ft_fprintf(c->sock, "{y:1:%s}\n", "File not found!");
	closedir(dir);
	return (FAIL);
}

static int		request_filetransfert(t_client *c, char *src, char *dst)
{
	int		pid;
	char	d[SIZE];
	char	s[SIZE];

	pid = fork();
	if (pid == 0)
	{
			ft_sprintf(s, "%s/%s", src, c->request.args[1]);
			ft_sprintf(d, "%s/%s", dst, c->request.args[1]);
			execl("/bin/cp", "cp", s, d, 0);
			exit(SUCCESS);
	}
	return (SUCCESS);
}

int				request_put(t_client *c)
{
	if (request_access(c, c->request.cmd,USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		ft_fprintf(c->sock, "{y:1:%s}\n" ,"Error: put <file>");
		return (FAIL);
	}
	if ((request_fileexist(c, c->login.cpath, c->request.args[1])) == FAIL)
		return (FAIL);
	if ((request_filetransfert(c, c->login.cpath, c->login.spath)) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int				request_get(t_client *c)
{
	if (request_access(c, c->request.cmd,USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		ft_fprintf(c->sock, "{y:1:%s}\n" ,"Error: get <file>");
		return (FAIL);
	}
	if ((request_fileexist(c, ".", c->request.args[1])) == FAIL)
		return (FAIL);
	if ((request_filetransfert(c, c->login.spath, c->login.cpath)) == FAIL)
		return (FAIL);
	return (SUCCESS);
}