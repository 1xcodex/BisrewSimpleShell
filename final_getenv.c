#include "main.h"
/**
* _unsetenv - unset environmenta var
* @name: env var to delete
* Return: 2 if success else -1
*/
int _unsetenv(const char *name)
{
	size_t i = 0, j = 0;
	int index;
	char *var;

	var = _getenv(name);
	if (var == NULL)
		return (-1);
	index = _getindex(name);
	while (environ[index][j])
	{
		environ[index][j] = '\0';
		j++;
	}
	free(var);
	return (2);
}
/**
 * _getenv - get enviroment variable
 * @name: name
 *
 * Return: Full name
 */
char *_getenv(const char *name)
{
	static char *val;
	unsigned int i = 0, notequal = 0, j = 0, k = 0, len = 0;

	if (name == NULL)
		return (NULL);
	while (environ[i])
	{
		notequal = 0;
		while (name[j] && (name[j] == environ[i][j]))
		{
			j++;
		}

		if (name[j] == '\0' && environ[i][j] == '=')
		{
			while (environ[i][k])
			{
				len++;
				k++;
			}
			val = malloc(sizeof(char) * (len + 1));
			if (val == NULL)
				return (NULL);
			k = 0;
			j = 0;
			while (environ[i][k])
			{
				val[j] = environ[i][k];
				j++;
				k++;
			}
			return (val);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
/**
 * _getindex - get index
 * @name: Name
 *
 * Return: index
 */
int  _getindex(const char *name)
{
	int i = 0;
	int notequal = 0, j = 0;

	if (name == NULL)
		return (-1);
	while (environ[i])
	{
		notequal = 0;
		while (name[j])
		{
			if (name[j] != environ[i][j])
			{
				notequal = 1;
				j = 0;
				break;
			}
			j++;
		}
		if (notequal == 0)
			return (i);
		i++;
	}
	return (-1);
}
/**
* free_null_env - free memory if fail during allocation
* @newenv: new environmental var pointer
* @i: failed index
* Return: -1 always
*/
int free_null_env(char **newenv, size_t i)
{

			i--;
			while (i >= 0)
			{
				free(newenv[i]);
				i--;
			}
			free(newenv);
			return (-1);
}

/**
* _addenv - add new environmental var
* @name: new name to be added
* @value: new value added
* Return: 1 if added 0 if No change or failed to add
*/
int  _addenv(const char *name, const char *value)
{
	size_t sizeenv, size, i = 0, j = 0, k = 0;
	char **newenv;

	while (environ[i])
		i++;
	sizeenv = i + 2;
	newenv = malloc(sizeof(char *) * (i  + 2));
	if (newenv == NULL)
		return (-1);
	for (i = 0; i < sizeenv - 1; i++)
	{
		if (environ[i])// environ[0]  SHELL=/bin/shell
			size = _strlen(environ[i]);
		else
			size = _strlen(name) + _strlen(value)  - 1;
		//printf("size = %lu\n", size);
		newenv[i] = malloc(sizeof(char) * (size));
		if (newenv[i] == NULL)
			return (free_null_env(newenv, i));
		_memset(newenv[i], size);
		if (environ[i])
			for (k = 0; k <= size - 1; k++)
				newenv[i][k] = environ[i][k];
		else
		{
			for (k = 0; k < _strlen(name) - 1; k++)
				newenv[i][k] = name[k];
			j = _strlen(name) - 1;
			newenv[i][j] = '=';
			j++;
			for (k = 0; k < _strlen(value) - 1; k++)
				newenv[i][k + j] = value[k];
		}
		j = 0;
	}
	newenv[sizeenv - 1] = NULL;
/*j = 0;

while (newenv[j])
{
	printf("%s\n", newenv[j]);
	j++;
}*/
	environ = newenv;
	return (1);
}
/**
* _setenv -set or add new environmental var
* @name: name of new env var
* @value: value to be asigned to new var
* @overwrite: what to do if value already exist /pass or overwrite
* Return: 0 if modify or no change -1 if failed 1 if added new var
*/
int  _setenv(const char *name, const char *value, int overwrite)
{
	size_t lenName, lenValue;
	int index, i = 0, j = 0;
	char *val;

	if (name == NULL)
		return (0);
	val = _getenv(name);
	if (val == NULL)
		return (_addenv(name, value));
	if (overwrite == 0)
		return (0);
	if (val)
	{ 
		index = _getindex(name);
		lenName = _strlen(name);
		lenValue = _strlen(value);
		environ[index] = malloc(sizeof(char) * (lenName + lenValue + 1));
		while (name[i])
		{
			environ[index][i] = name[i];
			i++;
		}
		environ[index][i] = '=';
		i++;
		while (value[j])
		{
			environ[index][i + j] = value[j];
			j++;
		}
		free(val);
		return (0);
	}
	return (-1);
}
/**
* free_env - free environment variable after setenv call
* @en: environ var
* @status: return value of setenv call
* @index: new index of env var set by setenv call
*/
void free_env(char **en, int status, int index)
{
	size_t set = 0;

	if (status == 0)
		free(en[index]);
	else if (status == 1)
	{
		while (en[set])
		{
			free(en[set]);
			set++;
		}
		free(en);
	}
}
