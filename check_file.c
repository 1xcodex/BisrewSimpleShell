#include "main.h"

	
char *check_in_path(char *filename)
{
	char *p, *cp;
	struct stat sb;
	int status;
	filep *head, *current;
	head = gethead();
	current = head;
	while (current)
	{
		if (current->path)
			p = get_full_path(filename, current->path);
		else 
		{
			current = current->next;
			continue;
		}
		if (p == NULL)
		{
			free_list(head);
			return (NULL);
		}
		status = access(p, F_OK);
		if (status == 0)
		{
			free_list(head);

			return (p);
		}
		if (current->next)
			current = current->next;
		else
			current = NULL;

		free(p);

	}
	free_list(head);
	return (NULL);
}
char  *check_in_cwd(char *filename)
{
	char *path;
	path = get_path_in_cwd(filename);
	if (access(path, F_OK | X_OK) == 0)
	{
		return (path);
	}
	else
	{
		free(path);
		return (NULL);
	}
}
char *get_full_path(char *filename, char *homedir)
{
	char *path;
	size_t i = 0, j = 0, len;

	len = _strlen(filename) + _strlen(homedir);
	path = malloc(sizeof(char) * len);
	if (path == NULL)
		return (NULL);
	_memset(path, len);
	while (homedir[i])
	{
		path[i] = homedir[i];
		i++;
	}
	path[i] = '/';
	i++;
	while (filename[j])
	{
		path[i] = filename[j];
		i++;
		j++;
	}
	return (path);
}
/*
	
int main(int __attribute__((unused)) argc, char **argv)
{
	char *path;
	path = check_in_cwd(argv[1]);
	if (path)
	{
		printf("%s: %s\n", argv[1], path);
		free(path);
		exit(99);
	}
	path = check_in_path(argv[1]);
	if (path)
	{
		printf("%s: %s\n", argv[1], path);
		free(path);
		exit(98);
	}
	printf("%s: No Such file or directory\n", argv[1]);


	char *path;
	path = get_full_path("ls", "/bin/usr");
	printf("%s\n", path);
	free(path);*/
	/*filep  *h;
	_setenv("PATH", "", 1);
	h = gethead(h);
	while (h)
	{
		printf("%s\n", h->path);
		h = h->next;
	}
	return (0);
}*/
