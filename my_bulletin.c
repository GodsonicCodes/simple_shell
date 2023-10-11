#include "shell.h"




/**
 * _myexit - This will Exit the shell.
 *
 * @info: This is a Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: This Exits with a given exit status (0) if info.argv[0] != "exit".
 */


/*function _myexit*/
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* Check if there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]); /* Convert the exit argument to an integer. */
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: "); /* Print an error message for an illegal number. */
			_eputs(info->argv[1]); /* Print the illegal number. */
			_eputchar('\n'); /* Print a newline character. */
			return (1); /* Return 1 to indicate an error. */
		}
		info->err_num = _erratoi(info->argv[1]); /* Set the error number based on the exit argument. */
		return (-2); /* Return -2 to indicate a request to exit the shell. */
	}
	info->err_num = -1; /* Set the error number to -1 if no exit argument is provided. */
	return (-2); /* Return -2 to indicate a request to exit the shell. */
}



/**
 * _mycd - This Changes the current directory of the process.
 *
 * @info: This is Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0.
 */


/*function _mycd*/
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024); /* Get the current working directory. */
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n"); /* Print a message for a getcwd failure. */

	if (!info->argv[1]) /* Check if there is no argument for changing the directory. */
	{
		dir = _getenv(info, "HOME="); /* Get the home directory from environment variables. */
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/"); /* Change the directory to the home directory. */
		else
			chdir_ret = chdir(dir); /* Change the directory to the home directory. */
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD=")) /* Check if there is no previous working directory. */
		{
			_puts(s); /* Print the current working directory. */
			_putchar('\n'); /* Print a newline character. */
			return (1); /* Return 1 to indicate success. */
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n'); /* Print the previous working directory. */
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/"); /* Change the directory to the previous working directory. */
	}
	else
		chdir_ret = chdir(info->argv[1]); /* Change the directory to the specified path. */

	if (chdir_ret == -1) /* Check if chdir failed (returned -1). */
	{
		print_error(info, "can't cd to "); /* Print an error message for the failed directory change. */
		_eputs(info->argv[1]); /* Print the directory that couldn't be changed to. */
		_eputchar('\n'); /* Print a newline character. */
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD=")); /* Update the OLDPWD environment variable. */
		_setenv(info, "PWD", getcwd(buffer, 1024)); /* Update the PWD environment variable. */
	}
	return (0); /* Return 0 to indicate success. */
}




/**
 * _myhelp - This Provides help for the shell (not yet implemented).
 *
 * @info: This is a Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0.
 */


/*function _myhelp*/
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv; /* Store the argument array. */

	_puts("help call works. Function not yet implemented \n"); /* Print a message indicating the help call works but is not implemented. */
	if (0)
		_puts(*arg_array); /* Temporary att_unused workaround. */
	return (0); /* Return 0 to indicate success. */
}
