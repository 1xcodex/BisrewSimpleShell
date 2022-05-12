#include "main.h"


ssize_t __getline(char *buf)
{

	ssize_t i;
	buf = malloc(sizeof(char) * 1024);
	_memset(buf, 1024);
	i = read(STDIN_FILENO, buf, 1024);
	if (i >= 0)
		return (i);


	return (-1);
}

	

int main()
{
	ssize_t i;
	char *buf;

	i = __getline(buf);

	printf("%s\n", buf);

	return (0);
}
