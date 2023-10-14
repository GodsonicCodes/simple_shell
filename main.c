#include "shell.h"






/* 
 * main - Entry point of the shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * This function serves as the entry point for the shell program.
 * It initializes necessary data structures, reads input, and
 * executes the shell's core functionality.
 *
 * @ac: The number of command-line arguments.
 * @av: An array of command-line argument strings.
 *
 * Return: 0 on success, 1 on error
 */




/*function main*/
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };
    int fd = 2;

    /* Inline assembly code to modify 'fd' */
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        /* Attempt to open a file */
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            /* Handle file open errors */
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        info->readfd = fd;
    }

    /* Populate environment list, read history, and start the shell */
    populate_env_list(info);
    read_history(info);
    hsh(info, av);

    return (EXIT_SUCCESS);
}

