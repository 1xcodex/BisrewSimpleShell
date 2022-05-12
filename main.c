#include "main.h"

int main(int argc, char **ar)
{
	pid_t pid;
	int status;
	char *cmd;
	char **argv;
	int j = 0;

	char *path_cwd, *path_in_path, *abs_path;


	while (1)// infinte loop until exit nor CTRD+D 
	{
		printf("$ ");// prompt to type command
		cmd = _getline(); // store typed commands to cmd pointer
		if (cmd == NULL || check_empty_space(cmd) ==  0)
			continue;
		if (cmd[0] == 0x04)
		{
			printf("^D\n");
			exit(0);
		}
		if (cmd[0] == 0x03)
		{
			printf("^C\n");
			continue;
		}
		argv = (char **)_strtok(cmd, argv, ' ');
		
		if (argv && argv[0] && (_strcmp(argv[0], "cd") == 0))
		{
			 if (argv[1])
			 {
				 cd(argv[1]);
				 continue;
			 }
			 else
			 {
				 cd(NULL);
				 continue;
			 }
		}


		if (argv && argv[0] && (_strcmp(argv[0], "setenv") == 0))
		{
			if (argv[1] && argv[2])
			{
				_setenv(argv[1], argv[2], 1);
				continue;
			}
			else
			{
				printf("usage: setenv var value\n");
				continue;
			}
		}
		if (argv && argv[0] && (_strcmp(argv[0], "getenv") == 0))
		{
			if (argv[1])
			{
				if (_getindex(argv[0]) == -1)
					printf("%s: (nill)\n", argv[0]);
				else
					printf("%s\n", environ[_getindex(argv[1])]);
				continue;
			}
			else
			{
				printf("usage: getenv va\n");
				continue;
			}
		}
		if (argv && argv[0] && (_strcmp(argv[0], "unsetenv") == 0))
		{
			if (argv[1])
			{
				 _unsetenv(argv[1]);
				continue;
			}
			else
			{
				printf("usage: unsetenv va\n");
				continue;
			}
		}



		if (argv && argv[0] && (_strcmp(argv[0], "exit") == 0))
		{
			if (argv[1])
				exit(atoi(argv[1]));
			exit(0);
		}
		if (argv && argv[0] && (_strcmp(argv[0], "env") == 0))
		{
			env();
			continue;
		}

	
		while (argv[j])
		{
			printf("%s\n", argv[j]);
			j++;
		}
		//   ls -la      /bin/ls -la  cd  exit 98  a.out 
		if (argv == NULL)
			continue;

		if (argv && argv[0] && argv[0][0] == '/')
			abs_path = argv[0];
		else
		{
			path_cwd = check_in_cwd(argv[0]);
			path_in_path = check_in_path(argv[0]);
			if (path_cwd)
				abs_path = path_cwd;
			else
				abs_path = path_in_path;
		}
		if (abs_path == NULL)
		{
			printf("No file found\n");
			continue;
		}
		else
		{
			pid = fork();

			if  (pid == 0)
			{

				execve(abs_path, argv, environ);

			}
			else if (pid > 0)
			{
				wait (&status);
			}
			else
			{
				printf("Error forking\n");
			}
		}



		

	}	

	return (0);
}



