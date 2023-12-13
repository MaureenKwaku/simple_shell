#include "main.h"
/**
 * display_prompt - a function to display the prompt
 * BUFFER_SIZE - the size of the buffer for reading commands
 * Return: Always 0 (Success)
 */
#define BUFFER_SIZE 1024

void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * main - Entry point
 * Return: Always 0 (Success)
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t read_chars;
	pid_t child_pid;
	int status;

	while (1)
	{
		display_prompt();

		read_chars = read(STDIN_FILENO, buffer, BUFFER_SIZE);/*reads user inputs*/
		if (read_chars == 0)/*checks for the end of file*/
		{
			printf("\n");
			break;
		}
		if (buffer[read_chars - 1] == '\n')
		{
			buffer[read_chars - 1] = '\0';
		}
		/*forks a child process*/
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execlp(buffer, buffer, (char *)NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(&status);/*parent process: waits for the child*/
			}
		}
	}
	return (0);
}
