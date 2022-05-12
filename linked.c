#include "main.h"
/**
* free_head - free linked list with path
* @head: head pointer
* @p: associated path
* Return: NULL pointer
*/

filep *free_head(filep *head, char *p)
{
	filep *current = head;

	free(p);
	while (head)
	{
		current = head->next;
		free(head->path);
		free(head);
		head = current;
	}
	return (NULL);
}
/**
* free_list -free linked list
* @head: head pointer
*/
void free_list(filep *head)
{
	filep *current = head;

	while (head)
	{
		current = head->next;
		free(head->path);
		free(head);
		head = current;
	}
}
/**
 * set_next - set next node
 * @p: path
 * @i: current index in string p
 * @current: current Node
 * Return: 1 if failed 0 on success
 */
int set_next(char *p, size_t i, filep  *current)
{
	size_t len, k;
	filep *head = current;

	while (p[i])
	{
		if (p[i] == ':')
		{
			len = len_from_to(p, i + 1, ':');
			current->next = malloc(sizeof(filep));
			if (current->next == NULL)
				return (1);
			current->path  = malloc(sizeof(char) * (len + 1));
			if (current->path == NULL)
				return (1);
			_memset(current->path, len + 1);
			k = ++i;
			while (p[i] != ':' && p[i])
			{
				(current->path)[i - k] = p[i];
				i++;
			}
			if (p[i + 1] ==  '\0')
			{
				free(current->next);
				current->next = NULL;
			}
			else
				current = current->next;
		}
	}
	current = NULL;
	return (0);
}
/**
* gethead - get head of linked list
* Return: head pointer
*/
filep *gethead()
{
	char *p;
	filep *head, *current;
	size_t i = 0, j, k = 0, len = 0;

	p = _getenv("PATH");
	if (_strlen(p) <= 5 || p[5] != '/')
		return (NULL);
	len = len_from_to(p, 5, ':');
	head = malloc(sizeof(filep));
	if (head == NULL)
		return (free_head(head, p));
	head->path = malloc(sizeof(char) * (len + 1));
	if (head->path == NULL)
		return (free_head(head, p));
	_memset(head->path, len + 1);
	i =  5;
	while (p[i] != ':' && p[i])
	{
		(head->path)[i - 5] = p[i];
		i++;
	}
	current = malloc(sizeof(filep));
	if (current == NULL)
		return (free_head(head, p));
	head->next = current;
	if (set_next(p, i, current))
		return (free_head(head, p));
	free(p);
	return (head);
}

