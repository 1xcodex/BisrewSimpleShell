#include "main.h"
int main(int argc, char **arv)
{
	int i, j = 0,k = 0, status, found, cmd_count = 0, prev_stat = -1, cur_stat = -1, prev_index = -1, cur_index = -1;
	char *line, *path_cwd, *path_in_path, *abs_path;
	int env_set = 0;//1: is changed 2: status of setenv 3: index
	char **argv;
	char **env_prev;
	char *env_var;
	pid_t pid;
	while (1)
	{
		cmd_count++;
		printf("$ ");
		line = _getline();
		if (init_line(line) == -1)
			continue;
		argv = (char **)_strtok(line, argv, ' ');
		if (argv && argv[0] && (_strcmp(argv[0], "setenv") == 0))
		{
			if (argv[1] && argv[2])
			{
				if (env_set == 1)
				{
					env_prev = environ;
					cur_stat =_setenv(argv[1], argv[2], 1);
					env_set = 1;
					cur_index = _getindex(argv[1]);
					free_env(env_prev, prev_stat, prev_index);
					prev_stat = cur_stat;
					prev_index = cur_index;
				}
				else
				{
					prev_stat = _setenv(argv[1], argv[2], 1);
					env_set = 1;
					prev_index = _getindex(argv[1]);
				}
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
			else
			{
				printf("usage: setenv var name\n");
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
		}
		if (argv && argv[0] && (_strcmp(argv[0], "getenv") == 0))
		{
			if (argv[1])
			{
				if (_getindex(argv[1]) == -1)
					printf("%s = (nill)\n", argv[1]);
				else
					printf("%s\n", environ[_getindex(argv[1])]);
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
			else
			{
				printf("Usage: getenv varname\n");
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
		}
		if (argv && argv[0] && (_strcmp(argv[0], "unsetenv") == 0))
		{
			if (argv[1])
			{
				printf("before : %s\n", environ[_getindex(argv[1])]);
				_unsetenv(argv[1]);
				if (_getindex(argv[1]) == -1)
					printf("After unset %s = (nill)\n", argv[1]);
				else
					printf("After : index%s\n",environ[_getindex(argv[1])]);
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
			else
			{
				printf("Usage: unsetenv varname\n");
				free_ptr(line);
				free_dblptr(argv);
				continue;
			}
		}



		if (init_argv(argv, line, env_set, prev_index, prev_stat) == -1) // means it is  built in done go next
		{
		//	free_ptr(line);
		//	free_dblptr(argv);
			continue;
		}
		if (init_argv(argv, line, env_set, prev_index, prev_stat) == 3)// built in cd but got error
		{
			free_ptr(line);
			printf("%s: %d: cd: can't cd to %s\n", arv[0], cmd_count, argv[1]);
			free_dblptr(argv);
			continue;
		}
		// setenv here
		path_cwd = check_in_cwd(argv[0]);
		path_in_path = check_in_path(argv[0]);
		if (get_abs_path(argv, path_cwd, path_in_path) == NULL)
		{
			printf("%s: %d: %s: not found\n", arv[0], cmd_count, argv[0]);
			free_all(line, argv, path_cwd, path_in_path);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			printf("PATH = %s\n", environ[_getindex("PATH")]);
			execve(get_abs_path(argv, path_cwd, path_in_path) , argv, NULL);
		}
		else if (pid > 0)
		{
			wait(&status);
			printf("my env here in parent %s\n", _getenv("HELLO"));
			free_all(line, argv, path_cwd, path_in_path);
		}
	}
	return (0);
}
