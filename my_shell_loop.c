#include "shell.h"
#include <sys/wait.h>




/**
 * hsh - Main shell loop.
 *
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * This function is the main loop of the shell, responsible for
 * handling user input, executing commands, and built-in functions.
 * It continues to run until an error or exit command is encountered.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */




/*function hsh*/
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            /* Print the shell prompt. */
            _puts("$ ");
        _eputchar(BUF_FLUSH); /* Flush the output buffer. */
        r = get_input(info); /* Read user input. */
        if (r != -1)
        {
            set_info(info, av); /* Set shell information. */
            builtin_ret = find_builtin(info); /* Check for and execute built-in commands. */
            if (builtin_ret == -1)
                find_cmd(info); /* Try to find and execute external commands. */
        }
        else if (interactive(info))
            /* Print a newline for user-friendly appearance. */
            _putchar('\n');
        free_info(info, 0); /* Free allocated memory. */
    }
    write_history(info); /* Save command history to a file. */
    free_info(info, 1); /* Free remaining memory. */
    if (!interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}




/**
 * find_builtin - Find and execute a built-in command.
 *
 * @info: The parameter and return info struct.
 *
 * Return: -1 if built-in not found, 0 if built-in executed successfully,
 *         1 if built-in found but not successful, -2 if built-in signals exit().
 */



/*function find_builtin*/
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}




/**
 * find_cmd - Try to find and execute an external command.
 *
 * @info: The parameter and return info struct.
 *
 * This function attempts to locate and execute an external command by searching
 * for the command in the PATH environment variable.
 *
 * Return: void
 */



/*function find_cmd*/
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=")
            || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}





/**
 * fork_cmd - Fork and execute an external command.
 *
 * @info: The parameter and return info struct.
 *
 * This function forks a child process to run an external command and handles
 * the execution of the command.
 *
 * Return: void
 */




/*function fork_cmd*/
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: Implement error handling. */
        perror("Error:"); /* Print an error message. */
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126); /* Permission denied. */
            exit(1);
        }
        /* TODO: Implement error handling. */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}

