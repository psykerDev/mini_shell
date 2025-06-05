#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>

void display_prompt();
char *read_input();
char **parse_input(char *input);
int handle_cd(char **args);
int handle_exit(char **args);
int handle_pwd(char **args);
int handle_external(char **args);

int main()
{
    while (1)
    {
        display_prompt();
        char *input = read_input();

        if (input == NULL)
        {
            printf("\nExiting shell (EOF received).\n");
            break;
        }

        char **pArgs = parse_input(input);
        execute_command(pArgs);
        free(pArgs);
    }
    return 0;
}

void display_prompt()
{
    printf("havoc.sh> ");
}

char *read_input()
{
    static char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;

    return buffer;
}

char **parse_input(char *input)
{
    char **args = malloc(sizeof(char *) * 32);

    int i = 0;

    char *token = strtok(input, " \n");

    while (token != NULL && i < 32)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    return args;
}

int execute_command(char **args)
{
    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "cd") == 0)
        return handle_cd(args);

    if (strcmp(args[0], "exit") == 0)
        return handle_exit(args);

    if (strcmp(args[0], "pwd") == 0)
        return handle_pwd(args);

    if (strcmp(args[0], "clear") == 0)
        return handle_clear(args);

    return handle_external(args);
}

int handle_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd: expected argument\n");
        return 1;
    }

    if (chdir(args[1]) != 0)
    {
        perror("cd failed path not found");
        return 1;
    }
    return 0;
}
int handle_exit(char **args)
{
    exit(0);
}
int handle_pwd(char **args)
{
    char buffer[2000];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        printf("Path: %s\n", buffer);
    }
    else
    {
        perror("getcwd() failed");
    }

    return 0;
}
int handle_clear(char **args)
{

    system(args[0]);
    return 0;
}

int handle_external(char **args)
{
    if (args == NULL || args[0] == NULL)
        return 1;

    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(args[0], args);

        perror("execvp failed");
        exit(1);
    }
    else if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
