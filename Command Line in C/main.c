#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list_node;
struct tree_node;
typedef struct list_node list_node;
typedef struct tree_node tree_node;

/* Required Methods */
struct tree_node *mk_tree_node(char *name);
struct tree_node *run_cd(struct tree_node *cwd, struct tree_node *root, char *arg);
struct list_node *mk_list_node(struct tree_node *v, struct list_node *next);

void run_mkdir(struct tree_node *cwd, char *arg);
void run_ls(struct tree_node *cwd);
void show_prompt(struct tree_node *cwd);
void remove_child(struct tree_node *dir, struct tree_node *child);
void run_rmdir(struct tree_node *cwd, char *arg);

/* My Methods */
tree_node *get_tree_node(list_node *child, char *arg);

int directoryExists(list_node *subdir, char *arg);
int hasChildren(tree_node *cwd);
int hasSpace(char *input);
char *getArgument(char *delim);

/* My Variables */
tree_node *root;

struct list_node { //Linked list of children
	 tree_node *represents;
	 list_node *next_child;
};

struct tree_node { //Each dir
	char dirName[128];
	tree_node *parent;
	list_node *child;
};


int main(void) {
	char userInput[134]; 
	char delim[2] = " ";
	char *command, *argument;
	int commandNumber, hasArg,running = 1;

	tree_node *tempTreeNode = malloc(sizeof(tree_node)); //Used with "cd" command
	
	/* cwd & root directories are set */
	tree_node *root = mk_tree_node("root");
	tree_node *cwd = root;
	
	while(running) {

		/*User Enters input */
		show_prompt(cwd);
		printf(" >"); 
		fgets(userInput, 134, stdin);
		argument = NULL;
		
		/* Gets the command and the arguemnt (if any) */
		if(hasSpace(userInput)) {
			command = strtok(userInput, delim);
			hasArg = 1;
		} else {
			command = malloc(sizeof(char *) * sizeof(userInput));
			strcpy(command, userInput);
			hasArg = 0;
		} 

		
		/* Removes the newline char from command */
		char *pos;
		if ((pos = strchr(command, '\n')) != NULL)
	    	*pos = '\0';

		
		
		/* Performing Command */
		if(!strcmp(command, "exit")) { 
			puts("Goodbye\n");
			return 0;
		} else if(!strcmp(command, "ls")) {
			run_ls(cwd);
		} else if(!strcmp(command, "cd"))  {
			
			if(hasArg) {
				argument = getArgument(delim);
			}

			if((tempTreeNode = run_cd(cwd, root, argument)) != NULL) {
				cwd = tempTreeNode;
			}

		} else if(!strcmp(command, "mkdir")) {

			
			if(hasArg) {
				argument = getArgument(delim);
				run_mkdir(cwd,argument);
			} else {
				puts("Error: Argument was not entered");
			}


		} else if(!strcmp(command, "rmdir")) {
			

			if(hasArg) {
				argument = getArgument(delim);
				run_rmdir(cwd, argument);
			} else {
				puts("Error: Argument was not entered");
			}


		} else {
			puts("Not a command");
		}
	}
}

struct tree_node *mk_tree_node(char *name) {
	tree_node *tempTreeNode = malloc(sizeof(tree_node));
	
	tempTreeNode->parent = malloc(sizeof(tree_node));
	tempTreeNode->parent = NULL;

	tempTreeNode->child = malloc(sizeof(list_node));
	tempTreeNode->child = NULL;

	strcpy(tempTreeNode->dirName, name);

	return tempTreeNode; //Right return type, but memory disappears after
}

struct list_node *mk_list_node(struct tree_node *v, struct list_node *next) {
	list_node *tempListNode = malloc(sizeof(list_node));

	tempListNode->represents = malloc(sizeof(tree_node));
	tempListNode->represents = v;

	tempListNode->next_child = malloc(sizeof(list_node));
	tempListNode->next_child = next;

	return tempListNode;
}

void run_mkdir(struct tree_node *cwd, char *arg) {
	
	if(arg == NULL) {	
		
		puts("Error: Name of directory to be create was not entered");

	} else if(directoryExists(cwd->child, arg)) {

		puts("Directory exists!");	
	
	} else {
	
		if(cwd->child == NULL) {  //Create the first child
			cwd->child = mk_list_node(mk_tree_node(arg), NULL);
		} else {
			cwd->child = mk_list_node(mk_tree_node(arg), cwd->child); 
			/*Creates child who's next (variable) is what is currently 
				being pointed at by the tree node and reset the tree tree_node
				  child (variable) pointer */
		}

		cwd->child->represents->parent = cwd;
	
	}
}

int directoryExists(list_node *subdir, char *arg) {
	
	printf("Childless: %d\n",subdir == NULL);
	if(subdir == NULL) //If no children
		return 0;

	if(!strcmp(subdir->represents->dirName, arg))
		return 1;
	if(subdir->next_child == NULL)
		return 0;
	else
		return directoryExists(subdir->next_child, arg);	
}

void run_ls(struct tree_node *cwd) {
	int print = 1;
	list_node *current = cwd->child;

	/* If the dir has no sub-directories */
	if(current == NULL)
		print = 0;
	else
		puts("Entries:");

	while(print) {
		printf("  %s/\n",current->represents->dirName);
		if(current->next_child != NULL) 
			current = current->next_child;
		else
			print = 0;
	}
}

struct tree_node *run_cd(struct tree_node *cwd, struct tree_node *root, char *arg) {

	/* Input: cd */
	if(arg == NULL) 
		return root;

	/* Input: cd .. */
	if(!strcmp(arg, ".."))
		return cwd->parent;

	/* If cwd has no subdirectories */
	if(cwd->child == NULL) {
		puts("Current working directory has no subdirectories.");
		return NULL;
	}

	/* If the directory exists */
	if(directoryExists(cwd->child, arg)) {
		return get_tree_node(cwd->child, arg);
	}
	printf("Directory '%s' does not exist.\n", arg);
	return NULL;
}

tree_node *get_tree_node(list_node *child, char *arg) {

	if(!strcmp(child->represents->dirName, arg)) //If dir found
		return child->represents;
	return get_tree_node(child->next_child, arg);
}

void show_prompt(struct tree_node *cwd) {
	if(cwd->parent != NULL)
		show_prompt(cwd->parent);
	printf("%s/", cwd->dirName);
}

void remove_child(struct tree_node *dir, struct tree_node *child) {
	
	/*First child*/
	if(!(strcmp(dir->child->represents->dirName, child->dirName))) {
		
		list_node *temp = dir->child;
		dir->child = temp->next_child;
		free(temp);

	} else {

		list_node *current = dir->child;
		while(current->next_child->represents != child) { //Gets to the node before the one to be deleted
			current = current->next_child;
		}
		list_node *temp = current->next_child;
		current->next_child = temp->next_child;
		free(temp);

	}
}

int hasChildren(tree_node *cwd) {
	
	return (cwd->child != NULL);	
}

void run_rmdir(struct tree_node *cwd, char *arg) {
	
	if(arg == NULL) {
		puts("Directory to be moved was not specified");
	} else {
		int loop = 1;

		list_node *current = cwd->child;
		while(loop) {

			if(!strcmp(current->represents->dirName, arg)) {  //If it's the first child
				

				if(!hasChildren(current->represents)){
						remove_child(cwd,current->represents);
					} else {
						puts("Cannot delete directory as their are subdirectories within");
					}
				loop = 0;


			} else if (current->next_child == NULL) { //If it's not 1st and/or there is no next
				

				puts("Entered directory is not a subdirectory of the current working directory");
				loop = 0;


			} else if(!strcmp(current->next_child->represents->dirName, arg)) { //If it's the +1 child dir
				

				if(!hasChildren(current->next_child->represents)) {
					remove_child(cwd, current->next_child->represents);
				} else {
					puts("Cannot delete directory as their are subdirectories within");
				}
				loop = 0;

			}
			current = current->next_child; //Move onto next node
		}
	}
}

int hasSpace(char *input) {

	while(*input != '\0') {
		if(*input == ' ') {
			return 1;
		} else {
			input++;
		}
	}
	return 0;
}

char *getArgument(char *delim) {
		char *temp_arg = strtok(NULL, delim);
		char *argument;

		/* Removes the newline that is added with fgets() */
		/* The arguement, if not entered appears as a single whitespace after strtok has been used */

		if((temp_arg == NULL) | (strlen(temp_arg) == 1)) {
			return NULL;
		} else if (temp_arg[strlen(temp_arg)-1] == '\n') {
			argument = malloc(sizeof(char *) * 128);
			memcpy(argument, temp_arg, strlen(temp_arg)-1);
		} else { 
			argument = malloc(sizeof(char *) * 128);
			strcpy(argument, temp_arg);
		}

		return argument;
}