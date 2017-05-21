#include "serveur.h"

static int			transfert_file(int fd_dst, int fd_src, int size)
{
	char			*buf;

	buf = mmap(0, size, PROT_WRITE, MAP_PRIVATE, fd_src, 0);
	if (buf)
	{
		write(fd_dst, buf, size);
		munmap(buf, size);
		return (SUCCESS);
	}
	return (FAIL);
}

int					transfert(char *src, char *dst, char *file)
{
	char			s[SIZE];
	int				fd_s;
	int				fd_d;
	struct stat		st;
	int				ret;

	ret = SUCCESS;
	fd_d = 0;
	ft_snprintf(s, SIZE, "%s/%s", src, file);
	if ((fd_s = open(s, O_RDWR)) != FAIL)
	{
		if ((ret = fstat(fd_s, &st)) == 0)
		{
			ft_snprintf(s, SIZE, "%s/%s", dst, file);
			if ((fd_d = open(s, O_CREAT | O_RDWR, st.st_mode)) != FAIL)
				ret = transfert_file(fd_d, fd_s, st.st_size);
			close(fd_d);
		}
	}
	close(fd_s);
	if (fd_s == FAIL || fd_d == FAIL || ret == FAIL)
		message(MSG_RESPONSE, FD_ERROR, "transfert failed().\n");
	return (ret);
}
