// adding header files to extend functionality of the shell
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


// defining the macros
#define MAX_INPUT 1024
#define MAX_ARGS 64
#define HISTORY_COUNT 50

// initializing the indexes to store the command history 
char command_history[HISTORY_COUNT][MAX_INPUT];
int history_index = 0;
int history_count = 0;

// giving an intro of the shell to the user
void print_intro() {
    printf("\nWelcome to the Safari Shell!\n");
    printf("This shell offers a variety of features for file management,\n");
    printf("running external programs, and accessing the Safari Ticketing System.\n");
    printf("Type 'all_comm' to view a list of available commands.\n\n");
}

// running the Safari Ticketing System
void executeSafariTicketingSystem() {
    system("gcc Validator.c EndSemesterProjectFOP_main.c -o ticketing_system"); // compiling source files
    system("./ticketing_system"); // running the executable
    system("rm ticketing_system"); // removing the executable
}

// showing the user the directory in which they are
void print_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *last_slash = strrchr(cwd, '/');
        if (last_slash != NULL) {
            last_slash++;
        }
        printf("[safariShell | %s]-> ", last_slash);
        fflush(stdout);
    }
}

// executing a command with or without background execution
void execute_command(char* args[], int background) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("Error: no such command");
        exit(1); // Child process exits on error
    } else {
        if (!background) {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }
        }
    }
}

// outputting all available commands
void help() {
    printf("\nAvailable commands:\n");
    printf("change_dir <directory>: Move around\n");
    printf("finish: Exit the shell\n");
    printf("safari: Run the Safari Ticketing System (change directory to 'Codes' before running this command)\n");
    printf("crt_dir <directory>: Make a new directory\n");
    printf("rem_dir <directory>: Delete a directory\n");
    printf("ls: List files and directories\n");
    printf("ls -l: List files and directories in long format\n");
    printf("comm_his: Show command history\n");
    printf("out <text>: Display some text\n");
    printf("clr_scr: Clean up the mess on the screen\n");
    printf("del <filename>: Delete a file\n");
    printf("crt <filename>: Create a file\n");
    printf("all_comm: Display this help message\n");
}

// main loop for the shell
int main() {
    print_intro();
    while (1) {
        char user_input[MAX_INPUT];
        printf("\n");
        print_prompt();
        if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            perror("fgets");
        }

        // Copy user input to 'input'
        char input[MAX_INPUT];
        strcpy(input, user_input);

        // Store the command in the history
        if (user_input[0] != '\0') {
            strncpy(command_history[history_index], user_input, MAX_INPUT);
            history_index = (history_index + 1) % HISTORY_COUNT;
            if (history_count < HISTORY_COUNT) {
                history_count++;
            }
        }

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Split the input into arguments
        char* args[MAX_ARGS];
        int arg_count = 0;
        char* token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Check for built-in commands
        if (arg_count > 0) {
            if (strcmp(args[0], "clr_scr") == 0) {
                system("clear");
            } else if (strcmp(args[0], "safari") == 0) {
                system("clear");
                executeSafariTicketingSystem();
            } else if (strcmp(args[0], "change_dir") == 0) {
                if (arg_count > 1) {
                    if (chdir(args[1]) != 0) {
                        perror("Error: invalid directory");
                    }
                }
            } else if (strcmp(args[0], "finish") == 0) {
                exit(0);
            } else if (strcmp(args[0], "crt_dir") == 0) {
                if (arg_count > 1) {
                    if (mkdir(args[1], 0777) != 0) {
                        perror("Error: cannot create directory");
                    }
                }
            } else if (strcmp(args[0], "rem_dir") == 0) {
                if (arg_count > 1) {
                    if (rmdir(args[1]) != 0) {
                        perror("Error: cannot remove directory");
                    }
                }
            } else if (strcmp(args[0], "comm_his") == 0) {
                for (int i = 0; i < history_count; i++) {
                    printf("%s", command_history[i]);
                }
            } else if (strcmp(args[0], "all_comm") == 0) {
                help();
            } else if (strcmp(args[0], "out") == 0) {
                printf("%s\n", args[1]);
            } else if (strcmp(args[0], "del") == 0) {
                char command[64] = "rm ";
                strcat(command, args[1]);
                system(command);
            } else if (strcmp(args[0], "crt") == 0) {
                char command[64] = "touch ";
                strcat(command, args[1]);
                system(command);
            } else { // running the default shell commands if the command does not match the built-in commands
                execute_command(args, 0);
            }
        }
    }
    return 0; // updating EXIT_STATUS to success
}

