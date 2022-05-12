#include "main.h"
/**
* _getline - get any number of input to buffer
* @buf: storage buffer
*
* Description: user must free memory returned by this function
*
* Return: pointer to buffer
*/
char *_getline()
{
	char c;
	size_t size = 1024, i = 0;
	char  *init;
	static  char  *buf, *cp;

	buf  = malloc(sizeof(char) * size);
	if (buf == NULL)
		return (NULL);
	_memset(buf, size);
	init = buf;
	c = getchar();
	if (c ==  -1)
	{
		buf[0] = 0x04;
		return (buf);
	}
	while (!(c == EOF || c == '\n'))
	{
		if (i > size)
		{
			size = size * 2;
			cp = buf;
			buf = malloc(sizeof(char) * size);
			if (buf == NULL)
			{
				return (cp);
			}
			_memset(buf, size);
			_strcpy(cp, buf);
			free(cp);
		}
		buf[i] = c;
		c = getchar();
		i++;
	}
	if (init && i > 1024)
		free(init);
	return (buf);
}
