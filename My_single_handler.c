#include "shell.h"



size_t my_strlen(const char *str);




/**
 * signal_handler - Handles the SIGINT signal (Ctrl+C)
 * @signal: The signal number (SIGINT)
 *
 * This function is called when the user presses Ctrl+C to interrupt the shell.
 * It prints a new line and the shell prompt and then flushes the standard output.
 * 
 * @note: The (void)signal is used to suppress unused parameter warnings.
 */




/*signal_handler*/
void signal_handler(int signal)
{
    char *prompt = "\n$ ";

    /* Suppress the "unused parameter" warning for signal */
    (void)signal;

    /* Print a new line and the shell prompt */
    write(1, prompt, my_strlen(prompt));

    /* Flush the standard output */
    fflush(stdout);
}
