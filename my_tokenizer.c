#include "shell.h"




/**
 * **strtow - Splits a string into words, considering delimiters. Repeated delimiters are ignored.
 * @str: The input string to be split.
 * @d: The delimiter string used for splitting.
 * Return: A pointer to an array of strings or NULL on failure.
 */



/*function strtow*/
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	/* Check if the input string is empty or NULL */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* If delimiter string is not provided, use a space ' ' as the default delimiter */
	if (!d)
		d = " ";

	/* Count the number of words in the input string */
	for (i = 0; str[i] != '\0'; i++) {
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
	}

	/* If no words found, return NULL */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for an array of strings to store the words */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Parse the input string and extract individual words */
	for (i = 0, j = 0; j < numwords; j++) {
		/* Skip leading delimiters */
		while (is_delim(str[i], d))
			i++;
		k = 0;
		/* Copy characters of the word into a new string */
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		/* Allocate memory for the word and copy its characters */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j]) {
			/* Clean up allocated memory if there's an allocation failure */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}




/**
 * **strtow2 - Splits a string into words based on a specified delimiter character.
 * @str: The input string to be split.
 * @d: The delimiter character used for splitting.
 * Return: A pointer to an array of strings or NULL on failure.
 */




/*function  strtow2*/
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	/* Check if the input string is empty or NULL */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Count the number of words in the input string based on the delimiter */
	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	}

	/* If no words found, return NULL */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for an array of strings to store the words */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Parse the input string and extract individual words based on the delimiter */
	for (i = 0, j = 0; j < numwords; j++) {
		/* Skip leading delimiter characters */
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		/* Copy characters of the word into a new string */
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		/* Allocate memory for the word and copy its characters */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j]) {
			/* Clean up allocated memory if there's an allocation failure */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
