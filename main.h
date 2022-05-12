#ifndef MAIN_H

#define MAIN_H

extern  char **environ;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
/**
 * struct filepath - filepath structure
 *
 * @path: path to file
 * @next: pointer to next file
 *
*/
typedef struct filepath
{
	char *path;
	struct filepath *next;
} filep;
/*
*utility 2
*/
void free_ptr(char *ptr);
void free_dblptr(char **argv);
int check_empty_space(char *s);
void __exit(char **, char *);
int init_line(char *line);

int init_argv(char **argv, char *line, int env_stat, int , int);
char *get_abs_path(char **argv, char *path_cwd, char *path_in_path);
void free_all(char *line, char **argv, char *path_cwd, char *path_in_path);
int is_builtin(char *argv1, char *argv2);
int cd(char *);
void env();
char *_getcwd();
filep *free_head(filep *head, char *p);
void free_list(filep *head);
int set_next(char *p, size_t i, filep  *current);
filep *gethead();
char *check_in_cwd(char *filename);
char *check_in_path(char *filename);
char *get_full_path(char *filename, char *homedir);
char *get_path_in_cwd(char *filename);
int _unsetenv(const char *name);
char *_getenv(const char *name);
int  _getindex(const char *name);
char *_getline();
size_t _strlen(const char *s);
char *_strtok(char *s, char **p, char sep);
int _strcmp(char *src, char *dest);
int _strcpy(char *src, char *dest);
size_t len_words(char **s);
int free_null_env(char **newenv, size_t i);
int  _addenv(const char *name, const char *value);
int  _setenv(const char *name, const char *value, int overwrite);
void free_env(char **en, int status, int index);
int _memset(char *mem, size_t size);
size_t len_from_to(char *p, int start, char stop);
#endif
