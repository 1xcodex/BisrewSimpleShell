#include "main.h"
/**
 * free_ptr - free pointer
 * @ptr: memory pointer to be freed
 */
void free_ptr(char *ptr)
{
	 if (ptr)
	 	 free(ptr);
}

/**
 * free_dblptr - free dbl memory
 * @argv: double pointer
 */
void free_dblptr(char **argv)
{
	int j = 0;
	 while (argv && argv[j])
	 {
	 	 if (argv[j])
	 	 	 free(argv[j]);
	 	 j++;
	 }
	 if (argv)
		free(argv);
}

/**
 * check_empty_space - a function check free space
 * @s: character play
 * Return: 0
 */
int check_empty_space(char *s)
{
	int j = 0;
	while (s[j])
	{
		if (s[j] != ' ')
			return (-1);
		j++;
	}
	return (0);
}

/**
 * init_line - function free memory from line
 * @line: line checker character
 * Return: -1 if nothing to clear else 0
 */
int init_line(char *line)
{
		if (line == NULL || (check_empty_space(line) == 0))
		{
			free_ptr(line);
			return (-1);
		}
		else if (line[0] == 0x04)
		{
			free_ptr(line);
			printf("\n");
			exit(0);
		}
		else if(line[0] == 0x03)
		{
			printf("^C\n");
			free_ptr(line);
			return (-1);
		}
		else
			return (0);
}
/**
 * __exit - auto exit stat
 * @argv: command line arg.
 * @status: */
void __exit(char **argv, char *status)
{
	free_dblptr(argv);
	if (status)
		exit(atoi(status));
	else
		exit(0);
}
int init_argv(char **argv, char *line, int env_set, int prev_index, int prev_stat)
{
	int i, j = 0;
	if (argv[0] && _strcmp(argv[0], "exit") == 0)
	{
		free_ptr(line);
		if (env_set == 1)
		{
			free_env(environ, prev_stat, prev_index);
		}
		if (argv[1])
			__exit(argv, argv[1]);
		else
			__exit(argv, NULL);
	}


		
	i = is_builtin(argv[0], argv[1]);
	if (i == 0)
	{
		free_ptr(line);
		free_dblptr(argv);
		return (-1);
	}
	if (i == 2)
		return (3);
	return (0);
}

char *get_abs_path(char **argv, char *path_cwd, char *path_in_path)
{
	if (argv[0][0] == '/')
		return (argv[0]);
	else if (path_cwd)
		return (path_cwd);
	else if(path_in_path)
		return (path_in_path);
	else
		return (NULL);
}
void free_all(char *line, char **argv, char *path_cwd, char *path_in_path)
{
	free_ptr(line);
	free_dblptr(argv);
	free_ptr(path_cwd);
	free_ptr(path_in_path);
}


