#include "shell.h"




/**
 * is_cmd - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: The path to the file.
 *
 * Returns: 1 if it's an executable command, 0 otherwise.
 */


/*function is_cmd*/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	/* If 'path' is NULL or 'stat' fails, return 0. */
	if (!path || stat(path, &st))
		return (0);

	/* Check if 'st' represents a regular file. */
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}




/**
 * dup_chars - Duplicates characters from 'pathstr'.
 * @pathstr: The PATH string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Returns: A pointer to the new buffer.
 */



/*function dup_chars*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	/* Copy characters from 'pathstr' to 'buf' while skipping colons. */
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}





/**
 * find_path - Finds 'cmd' in the 'PATH' string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Returns: The full path of 'cmd' if found, or NULL if not found.
 */



/*function find_path*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	/* If 'pathstr' is NULL, return NULL. */
	if (!pathstr)
		return (NULL);

	/* Check if 'cmd' starts with './' and is a valid command. */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	/* Iterate through 'pathstr' to find the full path of 'cmd'. */
	while (1)
	{
		/* If we reach the end of 'pathstr' or find a colon, create 'path'. */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);

			/* If 'path' is empty, just set it to 'cmd'. Otherwise, append 'cmd' to 'path'. */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			/* Check if 'path' is a valid command path. */
			if (is_cmd(info, path))
				return (path);

			/* If we reach the end of 'pathstr', exit the loop. */
			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}

	/* 'cmd' was not found in the 'PATH' string, so return NULL. */
	return (NULL);
}

