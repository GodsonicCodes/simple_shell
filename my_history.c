#include "shell.h"
#include <sys/stat.h>  /*Include the sys/stat.h header for fstat function.*/



/**
 * get_history_file - Retrieves the history file path.
 * @info: The parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */


/*function get_history_file*/
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME="); /* Get the HOME environment variable. */
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2)); /* Allocate memory for the history file path. */
	if (!buf)
		return (NULL);

	buf[0] = 0;
	_strcpy(buf, dir); /* Copy directory path. */
	_strcat(buf, "/"); /* Concatenate a '/' character. */
	_strcat(buf, HIST_FILE); /* Concatenate the history file name. */
	return (buf);
}






/**
 * write_history - Creates or appends to a history file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */




/*function write_history*/
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); /* Open the history file for writing. */
	free(filename);

	if (fd == -1)
		return (-1);

	/* Write history entries to the file. */
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd); /* Write string to the file. */
		_putfd('\n', fd); /* Write a newline character. */
	}
	_putfd(BUF_FLUSH, fd); /* Flush the character buffer. */
	close(fd);
	return (1);
}




/**
 * read_history - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: The histcount on success, 0 on failure.
 */




/*function read_history*/
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename); /* Open the history file for reading. */

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		fsize = st.st_size; /* Get the file size. */
	if (fsize < 2)
		return (0);

	buf = malloc(sizeof(char) * (fsize + 1)); /* Allocate memory for the file content. */
	if (!buf)
		return (0);

	rdlen = read(fd, buf, fsize); /* Read the file content. */
	buf[fsize] = 0;

	if (rdlen <= 0)
		return (free(buf), 0);

	close(fd);

	/* Parse the file content and build a history list. */
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;

	/* Ensure history size does not exceed the maximum allowed. */
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}






/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: The parameter struct.
 * @buf: The buffer containing the history entry.
 * @linecount: The history line count (histcount).
 *
 * Return: Always returns 0.
 */





/*function build_history_list*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	/* Add the history entry to the end of the list. */
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}




/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: The parameter struct.
 *
 * Return: The new histcount.
 */




/*function renumber_history*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	/* Update the history entry numbers. */
	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

