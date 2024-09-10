/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pipe, fork, dup2, execvp, close
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // TODO: add functionality
    // Create pipe
    int fd[2]; // array to hold the two file descriptors (fd[0] read end) ( f[1] write end)
    char buf[30];
    if(pipe(fd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // Create child to run first command 
    // In child, redirect output to write end of pipe done
    // Close the read end of the pipe on the child side. done
    // In child, execute the command
    // this child takes in the unfiltered list such as cmd1 and takes it in and writes into the pipe
    pid_t child1 = fork();// if theres an error itll return -1
    if(child1 == -1){
        perror("fork");
        return 1;
    }
    if(child1 == 0){
        close(fd[0]); // closee readddd
        dup2(fd[1],STDOUT_FILENO); // output redirected to write end used STDOUT_FILENO becuase thats where a program typically writes the output
        // should close write end just in case 
        close(fd[1]); // its closed but all the outputs are already redirected so we good its trapped lol
    }
    
    // Create another child to run second command
    // In child, redirect input to the read end of the pipe
    // Close the write end of the pipe on the child side.
    // Execute the second command.
    // this child is the one actually making everything uniform/upper case this one takes in what child1 wrote and reads it and does its thang
    pid_t child2 = fork();// if theres an error itll return -1
    if(child2 == -1){
        perror("fork");
        return 1;
    }
    if(child2 == 0){
        close(fd[1]); // closee write
        dup2(fd[0],STDIN_FILENO); // output redirected to write end used STDOUT_FILENO becuase thats where a program typically writes the output
        // should close read end just in case 
        close(fd[0]); // its closed but all the inputs are already redirected so we good its trapped lol
    }
    // good practice to close when done so close parent now because the child processes alreayd have everything they need
    close(fd[0]); // bye bye read ;(
    close(fd[1]); // bye bye write :(
    // Reset the input and output file descriptors of the parent.
    

}
