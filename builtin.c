#include "main.h"
int is_builtin(char *argv1, char *argv2)
{
		if (argv1 && _strcmp("cd", argv1) == 0)
		{
			if (argv2)
			{

				if(cd(argv2) == -1)
					return (2);
				else 
					return (0);
			}
			else
				cd(NULL);
			return (0);
		}
		else if  (argv1 && _strcmp("env", argv1) == 0)
		{
			env();
			return (0);
		}
		else
		{
			return (-1);
		}
}


int cd(char *path)
{
	int i, j = 5, len;
	char *valid_home, *prev_wd;

	if (path == NULL)
	{
		valid_home = _getenv("HOME");// HOME
		if (valid_home && _strlen(valid_home) >= 5)
		{
			prev_wd = environ[_getindex("PWD")];
			i = chdir(&(valid_home[5]));
			if (i == -1)
			{
				free(valid_home);
				return (-1);
			}
			//home = _getcwd();
		//	free(home);
		//	
			_setenv("OLDPWD", &(prev_wd[4]), 1);
			free(valid_home);
			return (0);
		}
		else
		{
			if (valid_home)
				free(valid_home);
			return (-1);
		}
	}
	else if (_strcmp(path, "-") == 0)
	{
		prev_wd = environ[_getindex("PWD")];
		if (chdir(&(environ[_getindex("OLDPWD")][7])) == -1)
			return (-1);

		_setenv("OLDPWD", &(prev_wd[4]), 1);
		return (0);
	}

	else
	{
		prev_wd = environ[_getindex("PWD")];
		i = chdir(path);
		if (i == -1)
		{
			return (-1);
		}
		//home = _getcwd();
		//free(home);
		_setenv("OLDPWD", &(prev_wd[4]), 1);
		return (0);
	}
}
void env()
{
	size_t i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

