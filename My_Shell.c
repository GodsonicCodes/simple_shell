#include "shell.h"




/* Function for string comparison */
int my_strcmp(const char *string1, const char *string2);

/* Signal handler function for Ctrl+C */
void signal_handler(int signal);

/* Function to calculate the length of a string */
size_t my_strlen(const char *str);

/* Function to duplicate a string */
char *my_strdup(const char *str);

/* Function to concatenate two strings */
char *my_strcat(char *final_str, char *str_to);

/* Function to copy one string to another */
char *my_strcpy(char *dest, char *src);

/* Function to read a line from the user */
ssize_t my_getline(char **line, size_t *len, FILE *stream);






/**
 * main - Custom shell implementation
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description: This program performs the following tasks:
 * 1. Displays a prompt to the user for entering a command.
 * 2. Reads the user's command in the main() function.
 * 3. Tokenizes the command into individual components.
 * 4. If the first token (program name) contains '/', it is considered a path.
 * 5. If the first token does not contain '/', it's treated as a raw program name.
 *
 * 6. If the command is a path, it executes the program using execve(path, arguments, NULL).
 * 7. If the command is not a path, it searches for the program in directories specified by the $PATH environment variable.
 * 8. It looks for a program with a matching name using strcmp. If a match is found, it executes execve(strcat(directory, line), arguments, NULL).
 *
 * The smaller strings represent the arguments parameter of the execve function.
 * It forks a new process to create a child.
 * The child process uses the execve function to execute the command.
 * The parent process waits for another command to be input by the user.
 *
 * Return: Always returns 0.
 */






/* Main function - Building a custom shell */
int main(int ac, char **av)
{
    /* Set the shell prompt */
    char *prompt = "$ ";

    /* Store the number of characters read */
    ssize_t characters_read = 0;

    /* Store the number of prompt bytes written */
    ssize_t prompt_bytes_written = 0;

    /* Initialize user input line */
    char *line = NULL;

    /* Initialize the length of the input line */
    size_t len = 0;

    /* Index variable */
    size_t i = 0;

    /* Index for freeing directories */
    size_t free_dir_i = 0;

    /* Define delimiters for tokenization */
    const char *delimiters = NULL;

    /* Store tokens of the command */
    char *command_token = NULL;

    /* Store the command and arguments */
    char **command = NULL;

    /* Maximum command size */
    size_t max_command = 0;

    /* Store child process ID */
    int child_pid = 0;

    /* Store process status */
    int status = 0;

    /* Store the PATH environment variable */
    char *path_env_var = NULL;

    /* Index to check for '/' in the program name */
    int slash_i = 0;

    /* Store the path of the program */
    char *path = NULL;

    /* Maximum number of directories */
    size_t max_directories = 0;

    /* Store directories in PATH */
    char **directories = NULL;

    /* Tokenize directories */
    char *directories_token = NULL;

    /* Index for directories */
    size_t directories_i = 0;

    /* Directory stream for searching */
    DIR *directory_stream = NULL;

    /* Index for searching directories */
    size_t searching_i = 0;

    /* Store directory entries */
    struct dirent *entry = NULL;

    /* Store concatenated path */
    char *concat_path = NULL;

    /* Flag for finding the program */
    int found = 0;

    /* Error message */
    char *err_msg = NULL;

    /* Store size */
    size_t size = 0;

    (void)ac;

    /* Set up signal handling for Ctrl+C (SIGINT) */
    signal(SIGINT, signal_handler);

    while (1)
    {
        line = NULL;
        delimiters = " \n\t\r\a";
        path = NULL;

        /* Prompt the user for input and display the shell prompt */
        if (isatty(STDIN_FILENO))
        {
            prompt_bytes_written = write(1, prompt, my_strlen(prompt));
            if (prompt_bytes_written == -1)
            {
                perror("write"); /* Handle write error */
                exit(1);
            }
        }
        /* With this we are flushing stdout*/
        fflush(stdout);

        /* Read the user's input */
        characters_read = my_getline(&line, &len, stdin);

        /* Check for end-of-file (EOF) or error in reading input */
        if (characters_read == EOF)
        {
            break;
        }
        else if (characters_read == -1)
        {
            break;
        }

        /* Check if the command is "exit" to exit the shell */
        if (my_strcmp(line, "exit") == 0)
        {
            free(line);
            exit(0);
        }

        /* Check if the command is "env" to display environment variables */
        if (my_strcmp(line, "env") == 0)
        {
            int i = 0;

            /* Loop through environment variables and print each one */
            for (; environ[i]; i++)
            {
                write(1, environ[i], my_strlen(environ[i]));
                write(1, "\n", 1);
            }

            free(line);
            continue;
        }

        /* Tokenize the command using the specified delimiters */
        command_token = strtok(line, delimiters);

        /* If no tokens are found, continue to the next input */
        if (command_token == NULL)
        {
            free(line);
            continue;
        }

        /* Allocate space for the command array */
        max_command = 10;
        command = malloc(sizeof(char *) * max_command);
        i = 0;

        /* Iterate through tokens and store them in the command array */
        while (command_token != NULL)
        {
            /* Check if reallocation is needed when reaching the maximum */
            if (i >= max_command)
            {
                max_command *= 2;
                command = realloc(command, sizeof(char *) * max_command);

                if (command == NULL)
                {
                    perror("./hsh"); /* Handle realloc error */
                }
            }

            /* Duplicate the token and store it in the command array */
            command[i] = my_strdup(command_token);

            if (command[i] == NULL)
                continue;

            command_token = strtok(NULL, delimiters);
            i++;
        }

        /* Set the last element of the command array to NULL */
        command[i] = NULL;

        /* Check if the program name is a path or just a file name */
        slash_i = 0;
        while (line[slash_i] != '\0')
        {
            if (line[slash_i] == '/')
            {
                path = line;
                break;
            }
            slash_i++;
        }

        /* If the program name is not a path, search for it in directories */
        if (path == NULL)
        {
            char *PATH = getenv("PATH");

            if (PATH == NULL)
                continue;

            path_env_var = my_strdup(PATH);

            if (path_env_var == NULL)
                continue;

            directories_token = strtok(path_env_var, ":");
            if (directories_token == NULL)
            {
                perror("av[0]"); /* Handle error when no directories found */
            }

            /* Allocate space for directories array */
            max_directories = 100;
            directories = malloc(sizeof(char *) * max_directories);
            directories_i = 0;

            /* Iterate through tokens and store them in the directories array */
            while (directories_token != NULL)
            {
                /* Check if reallocation is needed when reaching the maximum */
                if (directories_i >= max_directories)
                {
                    max_directories *= 2;
                    directories = realloc(directories, sizeof(char *) * max_directories);

                    if (directories == NULL)
                    {
                        perror("realloc"); /* Handle realloc error */
                    }
                }

                /* Duplicate the token and store it in the directories array */
                directories[directories_i] = my_strdup(directories_token);

                if (PATH == NULL)
                    continue;

                directories_token = strtok(NULL, delimiters);
                directories_i++;
            }

            /* Set the last element of the directories array to NULL */
            directories[directories_i] = NULL;

            /* Open directories to search for the command */
            searching_i = 0;

            while (directories[searching_i] != NULL)
            {
                directory_stream = opendir(directories[searching_i]);

                /* Handle the case where the directory could not be opened */
                if (directory_stream == NULL)
                {
                    searching_i++;
                    continue;
                }

                found = 0;
                entry = readdir(directory_stream);

                /* Loop through entries in the directory to find the command */
                while (entry != NULL)
                {
                    if (my_strcmp(command[0], entry->d_name) == 0)
                    {
                        found = 1;
                        break;
                    }

                    entry = readdir(directory_stream);
                }

                closedir(directory_stream);

                /* If the command is found, exit the loop */
                if (found == 1)
                    break;

                searching_i++;

                /* If no directories are left to search, handle the error */
                if (searching_i == directories_i)
                {
                    perror(command[0]);
                }
            }
        }
        /* This is the END of if (Path == NULL)*/
        /** 5. Forks a new process to execute the command */
        child_pid = fork(); /* Create a new child process */
        if (child_pid == -1)
        {
        perror("fork"); /* Check for fork failure */
        }
        else if (child_pid == 0)
        {
        /* This is the child process */
        if (path == NULL) /* If the program is not a path */
        {
        size = my_strlen(directories[searching_i]) + my_strlen(line) + 2;
        concat_path = malloc(size); /* Allocate memory for the concatenated path */
        if (concat_path == NULL)
        {
            perror("malloc"); /* Check for malloc failure */
        }

        /* Create the path to be executed */
        my_strcpy(concat_path, directories[searching_i]); /* Copy the directory */
        my_strcat(concat_path, "/"); /* Append a '/' character */
        my_strcat(concat_path, command[0] /* line */); /* Append the program name */

        /* Execute the program with the given arguments */
        command[0] = concat_path;
        execve(command[0], command, environ);

        /* Handle execve failure if it occurs */
        perror("execve");
        free(concat_path); /* Free the concatenated path memory */
        free(command);     /* Free the command array memory */
    }
    else
    {
        (void)av;       /* Suppress unused parameter warning */
        (void)err_msg;  /* Suppress unused parameter warning */
        execve(command[0], command, environ);

        /* Handle execve failure if it occurs */
        perror("execve");
    }
}

/* Continue in the parent process (this program) */
wait(&status); /* Wait for the child process to complete */

    /* Free memory allocated for directories array (if applicable) */
    if (path == NULL)
    {
        for (free_dir_i = 0; directories[free_dir_i] != NULL; free_dir_i++)
        {
            free(directories[free_dir_i]); /* Free each directory entry */
        }
    }

    /* Free memory allocated for command array */
    for (i = 0; command[i] != NULL; i++)
    {
        free(command[i]); /* Free each command argument */
    }

    free(directories);     /* Free the directories array */
    free(path_env_var);    /* Free the path environment variable string */
    free(concat_path);     /* Free the concatenated path string */
    free(command);         /* Free the command array */
    free(line);            /* Free the user input line */

    } /* End of the main loop; clean up and print a new line if STDIN is a terminal */
    free(line);
    if (isatty(STDIN_FILENO) == 1)
        write(1, "\n", 1); /* Print a newline character if STDIN is a terminal */
    
    return (0); /* Return 0 to indicate successful program execution */
}




