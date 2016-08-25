#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

// EXECUTE FUNCTION (cmd params)
void execute(char **argv) {
	pid_t pid;
	int status;
	if ((pid = fork()) < 0) {
		cout << "ERROR: fork failed" << endl;
		exit(1);
	}
	else if (pid==0) {
		if (execvp(*argv, argv) < 0) {
			cout << "ERROR: execute failed" << endl;
			exit(1);
		}
	}
	else {
		while (wait(&status) != pid)
			;
	}
}

// PIPE FUNCTION (cmd1 params | cmd2 params)
int pipeFnc(int argc, char** argv) {
	int pipefd[2];
	int pid;
	//char *cmd1_args[] = {};
	//char *cmd2_args[] = {};
	if( pipe(pipefd) != 0) {
		pipe(pipefd);
	}
	pid = fork();
	if (pid == 0) {
		// CHILD PROCESS
		dup2(pipefd[0],0);
		close(pipefd[1]);
		//execvp(cmd1, cmd1_args);
	} else {
		// PARENT PROCESS
		dup2(pipefd[1],1);
		close(pipefd[0]);
		//execvp(cmd2, cmd2_args);
	}

}

// REDIRECT OUT FUNCTION (cmd params > outfile)
int outFnc(int argc, char** argv) {
	int outFile;
	//char* cmd_args[] = {}
	//outFile = open(outfile, O_WRONLY);
	//dup2(outFile,1);
	//close(outFile);
	//execvp(cmd,cmd_args);
}

// REDIRECT IN FUNCTION (cmd params < infile)
int inFnc(int argc, char** argv) {
	int inFile;
	//char* cmd_args[] = {}
	//inFile = open(infile, O_RDONLY);
	//dup2(inFile,0);
	//close(inFile);
	//execvp(cmd,cmd_args);
}

int main(int argc, char**argv){
	
	string lineS;
	while(getline(cin, lineS)) {
		const char* line = lineS.c_str();
		int size = lineS.length();
		if (size > 80) {
			// Line exceeded max length, check for next line
			cout << "ERROR: Number of characters in line has exceeded 80." << endl;
			continue;
		}	
		else {
			// Parse Line character by character for tokens

			// Prepare for individual tokens and full cmd with args
			int error = 0;
			string token;
			char cmd_args[80][80] = {0};
			int location = 0;
			
			// CREATE LIST OF POSSIBLE TOKENS, TO BE EXECUTED LATER	
			for(int i = 0; i < size; i++){
				char c = line[i];
				// cout << "Character " << i << " is: " << c << endl;
				if (!isalpha(c) && !isdigit(c) && c != '-' && c != '.' && c != '_' && c != ' '){
					if(c == '<' || c == '>' || c == '|'){
						// Must be space before and after
						if (line[i-1] != ' ' ||  line[i+1] != ' '){
							// Call error for wrong formatting
							cout << "ERROR: Formatted operator wrong!" << endl;
						}
						else {
							// Catch any extra spaces and save to cmd_args
							++i;
							while(line[i+1] == ' '){
								++i;
							}
							token += c;
							// cout << "Token: " << token << endl;
							char* word = const_cast<char*>(token.c_str());
							strcpy(cmd_args[location], word);
							location+=1;
							token = "";
							continue;
						}
					}
					// If character found is not valid, fail and go to next line 
					cout << "ERROR: Character [" << c << "] is invalid" << endl;
					error = 1;
					break;
				}
				if (i == size-1) {
					// Found end of line, process
					// cout << "End of line" << endl;
					token += c;
					// cout << "Token: " << token << endl;
					char* word = const_cast<char*>(token.c_str());
					strcpy(cmd_args[location], word);
					location+=1;
					location+=1;
				}
				if (c == ' '){
					// Extra spaces don't do anything
					while(line[i+1] == ' '){
						++i;
					}
					// Found space, add token to cmd/args
					if (token == " " || token != "") {
						// cout << "Space" << endl;
						// cout << "Token: " << token << endl;
						char* word = const_cast<char*>(token.c_str());
						strcpy(cmd_args[location], word);
						location+=1;
						token = "";
					}
				} else {
					// Add extra character to token
					// cout << "Adding character to token" << endl;
					token += c;
				}
			}
			if (error) {
				// Prevent anything else from happening
				continue;
			}

			//ONCE ALL TOKENS OBTAINED, PUT INTO TOKEN GROUPS WITH OPERATORS
			
			int lastOp = 0;
			int done = 0;
			int command = 0;
			char **exec_cmd_args;
			int position = 0;

			for(int j = 0; j < location; j++){
				//cout << "cmd_args[" << j << "] is: " << cmd_args[j] << endl;
				if (strcmp(cmd_args[j],"exit") == 0){
					// End Program if one of the cmds is exit
					cout << "exit called, end program" << endl;
					return 0;
				}
				if (strcmp(cmd_args[0],"<") == 0 || strcmp(cmd_args[0],">") == 0 || strcmp(cmd_args[0],"|") == 0){
					if (j == 0){
						// Check if list of words/operators begins with an operator
						cout << "ERROR: Cannot begin with operators" << endl;
						break;
					}
				} else {
					// CHECK FOR |, <, >
					// Completed first command:
					char* validWord = cmd_args[j];
					char* check = cmd_args[j+1];
					if ((validWord,"exit") == 0){
						// End Program if one of the cmds is exit
						cout << "exit called, end program" << endl;
						return 0;
					}
					if (strcmp(check,"<") == 0 || strcmp(check,">") == 0 || strcmp(check,"|") == 0){
						j++;
	
						//execute(exec_cmd_args);					
						// Get all valid words before this point
						for(int k = lastOp; k < j; k++){
							cout << "Command/Parameter " << k << ": " << cmd_args[k] << endl;
						}
						lastOp = j+1;
						
						// PIPE
						if(strcmp(check,"|") == 0){
							// START WITH PIPE
							cout << "Starting FIRST pipe (1)" << endl;	
							char* check = cmd_args[j];
							int status  = 1;
							int num = 1;
							while(status){
								// Get all commands/parameters until next Pipe |
								j++;
								check = cmd_args[j];
	
								if (strcmp(check,"|") == 0){
									// New pipe incoming
									num++;
									cout << "Starting new pipe: " << num <<endl;
									j++;
									check = cmd_args[j];
								}
								if (strcmp(cmd_args[j+1],"") == 0){
									// Done piping, exit
									cout << "FINAL pipe item in " << num << ": " << cmd_args[j] << endl;
									status = 0;
									break;
								} else if (strcmp(check,"") != 0){
									// (another) pipe item
									cout << "Pipe item in " << num << ": " << check << endl;
								}
							}
						}
						// INPUT FILE REDIRECTION (FIRST OPERATOR IS <)
						if(strcmp(check,"<") == 0){
							//Check for errors
							
							char* check = cmd_args[j+1];
							if (strcmp(check,"<") == 0 || strcmp(check,">") == 0 || strcmp(check,"|") == 0){
								cout << "ERROR: Invalid use of operators!(A)" << endl;
								break;
							}

							// File comes immediately after
							char* inFile = cmd_args[j+1];
							cout << "infile is: " << inFile << endl;
							j++;				
							
							check = cmd_args[j+1];
							if (strcmp(check,"<") == 0 || (strcmp(check,"|") != 0 && strcmp(check,">") != 0 && strcmp(check,"") != 0)){
								if (strcmp(check,"<") == 0){
									cout << "ERROR: Invalid use of operators. Too many redirection in operators!" << endl;

								}
								if (strcmp(check,"") != 0){
									cout << "ERROR: Redirection in has only 1 infile." << endl;
								}
								break;
							} else {
								
								// PIPE after <
								// MAKE SURE TO BE ABLE TO HAVE MULTIPLE COMMANDS/PARAMETERS
								if (strcmp(check,"|") == 0) {
									++j;


									cout << "Starting FIRST pipe (1)" << endl;	
									char* check = cmd_args[j];
									int status  = 1;
									int num = 1;
									while(status){
										// Get all commands/parameters until next Pipe |
										j++;
										check = cmd_args[j];
	
										if (strcmp(check,"|") == 0){
											// New pipe incoming
											num++;
											cout << "Starting new pipe: " << num <<endl;
											j++;
											check = cmd_args[j];
										}
										if (strcmp(check,">") == 0){
											// Redirect out incoming
											cout << "redirected out (multi pipes)" << endl;
											char* outFile = cmd_args[j+1];
											cout << "outfile is: " << outFile << endl;
											status = 0;
											break;
										}
										if (strcmp(cmd_args[j+1],"") == 0){
											// Done piping, exit
											cout << "FINAL pipe item in " << num << ": " << cmd_args[j] << endl;
											status = 0;
											break;
										} else if (strcmp(check,"") != 0){
											// (another) pipe item
											cout << "Pipe item in " << num << ": " << check << endl;
										}
									}
									cout << "EXITED!" << endl;
								}
									
								// Output after <
								
								if (strcmp(check,">") == 0) {
									++j;
									cout << "redirected out (single)" << endl;
									char* outFile = cmd_args[j+1];
									cout << "outfile is: " << outFile << endl;
									//break;
								}

								// SINGLE INPUT
								
								if (strcmp(check,"") == 0) {
									cout << "single input" << endl;
									//break;		
								}	
							}
						}
						// OUTPUT FILE REDIRECTION
						if(strcmp(check,">") == 0){
							// SINGLE OUTPUT OPERATOR	
							// File comes immediately after
							char* outFile = cmd_args[j+1];
							cout << "outfile is: " << outFile << endl;
							cout << "redirected out (no input)" << endl;
							j++;
							if( strcmp(cmd_args[j+1],"") != 0){
								cout << "ERROR: Shouldn't have anything after an outfile!" << endl;
								break;
							}
						}
						cout << "DONE" << endl;
					} else {
						// for first commands and parameters
						if (strcmp(cmd_args[j],"") != 0){
							if (!command) {
								//SEGFAULT POINT
								//strcpy(exec_cmd_args[position], cmd_args[0]);
								command = 1;
								position+=1;
							}
							cout << "Command/Parameter: " << cmd_args[j] << endl;
							//strcpy(exec_cmd_args[position], cmd_args[j]);
							position+=1;
						} else {
							cout << "END OF LIST" << endl;
						}
					} // end of FOR LOOP
				}
			}
			cout << "Complete" << endl;
			//cout << line << endl;	
			cout << endl;
		}
	}
}
