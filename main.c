#include "shell.h"
#include <fcntl.h> /* Including the necessary header for open function */
#include <errno.h> /* Including the necessary header for errno */




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




/* function main */
int main(int ac, char **av)
{
    info_t info; /* Declare a single info_t structure */

    /* Initialize the fields of the info_t structure */
    info.argc = ac;
    info.line_count = 0;
    info.err_num = 0;
    info.status = 0;
    info.readfd = 2; /* Set an initial value for readfd */

    int fd = info.readfd; /* Copy the readfd to fd */

    /* Inline assembly code to modify 'fd' */
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY); /* Attempt to open a file */
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
    }

    info.readfd = fd; /* Update the readfd with the modified 'fd' */

    /* Populate environment list, read history, and start the shell */
    populate_env_list(&info); /* Pass a pointer to the info_t structure */
    read_history(&info); /* Pass a pointer to the info_t structure */
    hsh(&info, av); /* Pass a pointer to the info_t structure */

    return (EXIT_SUCCESS);
}
