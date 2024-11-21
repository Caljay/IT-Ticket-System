#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TO DO
FIX FGETS() CAPTURING NEW LINE CHARACTERS


*/

typedef struct ticket
{
	int id;
	char* name;
	char* email;
	char* date;
	int priority;
	char* issue_description;
	int is_closed;
	char* issue_solution;
	struct ticket* nextTicket;
} Ticket;

//prototype so that the ticket creation functions may access it
void rm_newline(char arr[]);
//checking for null pointers
void checkForNullPointer(void* ptr) {

	if (ptr == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

}
//all the  functions for ticket creation and addition

char* getName() {

	//alllocate the max lenth for the name to realloc it later
	char* name = malloc(sizeof(char) * 50);
	checkForNullPointer(name);

	printf("Please Enter your name: ");
	fgets(name, 50, stdin);
	rm_newline(name);
	name = (char*)realloc(name, sizeof(char) * strlen(name) + 1);
	checkForNullPointer(name);

	return name;


}
char* getEmail() {
	char* email = malloc(sizeof(char) * 50);
	checkForNullPointer(email);

	printf("Please Enter your email: ");
	fgets(email, 50, stdin);
	rm_newline(email);
	email = (char*)realloc(email, sizeof(char) * strlen(email) + 1);
	checkForNullPointer(email);

	return email;
}
char* getDate() {
	char* date = malloc(sizeof(char) * 15); //less characters needed due to the input format
	checkForNullPointer(date);
	printf("Please Enter the date MM/DD/YYYY: ");
	fgets(date, 15, stdin);
	rm_newline(date);
	date = (char*)realloc(date, sizeof(char) * strlen(date) + 1);
	checkForNullPointer(date);
	return date;

}
int getPriority() {
	int priority = -1;
	printf("What is the priority of this issue. 1 = LOW 5 = HIGH: ");
	priority = (int)getchar() - 48;
	getchar(); //capture newline
	if (priority > 5 || priority < 1) {
		priority = 1;
	}
	return priority;
}
char* getDescription() {

	char* description = malloc(sizeof(char) * 1000); //set the max that the user can intially do, then reallocate it later on
	checkForNullPointer(description);
	printf("Please describe the issue (1000 character max): ");
	fgets(description, 1000, stdin);
	rm_newline(description);
	description = (char*)realloc(description, sizeof(char) * strlen(description) + 1);
	checkForNullPointer(description);

	return description;




}
void createTicket(Ticket** tickets, int id) {

	Ticket* newTicket = NULL;
	Ticket* tempTicket = NULL;
	if (*tickets == NULL) { //if there are no current tickets

		*tickets = (Ticket*)malloc(sizeof(Ticket));
		checkForNullPointer(tickets);


		(*tickets)->id = id;
		(*tickets)->name = getName();
		(*tickets)->email = getEmail();
		(*tickets)->date = getDate();
		(*tickets)->priority = getPriority();
		(*tickets)->is_closed = 0;
		(*tickets)->issue_description = getDescription();
		(*tickets)->nextTicket = NULL;

		return;
	}

	else {
		tempTicket = *tickets;

		while ((tempTicket)->nextTicket != NULL) {
			tempTicket = tempTicket->nextTicket;
		}
	}
	

	newTicket = (Ticket*)malloc(sizeof(Ticket));
	checkForNullPointer(newTicket);

	newTicket->id = id;
	newTicket->name = getName();
	newTicket->email = getEmail();
	newTicket->date = getDate();
	newTicket->priority = getPriority();
	newTicket->is_closed = 0;
	newTicket->issue_description = getDescription();
	newTicket->nextTicket = NULL;

	tempTicket->nextTicket = newTicket;

	
}


//for ticket closing

char* getSolution() {

	//intilal size to be relloced later
	char* solution = malloc(sizeof(char) * 1000);
	checkForNullPointer(solution);

	printf("What was the solution for this issue: ");
	fgets(solution, 1000, stdin);
	rm_newline(solution);
	solution = (char*)realloc(solution, sizeof(char) * strlen(solution) + 1);
	checkForNullPointer(solution);

	return solution;



}

int getOpenTicketCount(Ticket** tickets) {

	if ((*tickets) == NULL) return 0;

	int ticketsOpen = 0;
	Ticket* tempTicket = *tickets;

	while (tempTicket->nextTicket != NULL) {

		if (tempTicket->is_closed == 0) {
			ticketsOpen++;
		}
		tempTicket = tempTicket->nextTicket;

	}
	if (tempTicket->is_closed == 0) {
		ticketsOpen++;
	}


	return ticketsOpen;




}

void closeTicket(Ticket** tickets) {

	if (*tickets == NULL) {
		printf("No open tickets"); 
		return;
	}

	int closeID = 0;
	int wasFound = 0; //check to see if the id was found
	Ticket* tempTicket = *tickets;
	printf("What is the ID of the ticket you wish to close? ");
	scanf("%d",&closeID);
	getchar();

	while (tempTicket->nextTicket != NULL && !wasFound) {

		if (tempTicket->id == closeID) {
			if (tempTicket->is_closed == 1) {
				printf("\nThis ticket is already closed!\n");
				return;
			}

			tempTicket->is_closed = 1;
			//put a solution
			tempTicket->issue_solution = getSolution();
			wasFound = 1;
		}
		tempTicket = tempTicket->nextTicket;
		



	}

	if (tempTicket->id == closeID) {

		if (tempTicket->is_closed == 1) {
			printf("This ticket is already closed!");
			return;
		}

		tempTicket->is_closed = 1;
		//put a solution
		tempTicket->issue_solution = getSolution();
		wasFound = 1;
	}

	if (!wasFound) {
		printf("No ticket with that id was found. Try printing all of these tickets to ensure you are using the proper id");

	}



}

//for it management
void getTicketsByPriority(Ticket** tickets) {

	//need to rank the tickets by priority...
	if (*tickets == NULL) {
		printf("There are no tickets");
		return;
	}

	int openTickets = getOpenTicketCount(tickets);
	if (openTickets == 0) {
		printf("There are currently no open tickets!");
		return;
	}
	int* ticketID_Priorties = malloc(sizeof(int) * openTickets); //the most tickets within a certain priortiy is equal to the tickets currently open
	checkForNullPointer(ticketID_Priorties);

	int ticketID_PrioritiyArrayIndex = 0;
	Ticket* tempTicket = *tickets;

	for (int priority = 1; priority <= 5; priority++) {
		tempTicket = *tickets; //must restart every single pass
		ticketID_PrioritiyArrayIndex = 0;

		while (tempTicket->nextTicket != NULL) {
		
			if (tempTicket->priority == priority && tempTicket->is_closed == 0) {

				ticketID_Priorties[ticketID_PrioritiyArrayIndex] = tempTicket->id;

				ticketID_PrioritiyArrayIndex++;

			}
			tempTicket = tempTicket->nextTicket;
		}
		if (tempTicket->priority == priority) {

			ticketID_Priorties[ticketID_PrioritiyArrayIndex] = tempTicket->id;
				ticketID_PrioritiyArrayIndex++;

			
		}

		if (ticketID_PrioritiyArrayIndex > 0) {

			printf("The following ticket IDs have a priority of %d: ", priority);

			for (int i = 0; i < ticketID_PrioritiyArrayIndex; i++) {

				printf("%d ", ticketID_Priorties[i]);
				ticketID_Priorties[i] = 0;

			}
			printf("\n\n");

	}



	}
	
	free(ticketID_Priorties);
	printf("\n\n");

}


//for niceities
void printAllTickets(Ticket** tickets) {
	
	if (*tickets == NULL) {
		printf("There are no tickets");  
		return;
	}


	Ticket* tempTicket = *tickets;
	printf("Printing all tickets\n");


		while (tempTicket->nextTicket != NULL) {
			if (tempTicket->is_closed) {
				printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s Solution: %s",
					tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description, tempTicket->issue_solution);
			}
			else {
				printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s",
					tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description);
			}
			printf("\n");


			tempTicket = tempTicket->nextTicket;
		}


		if (tempTicket->is_closed) {
			printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s Solution: %s",
				tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description, tempTicket->issue_solution);
		}
		else {
			printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s",
				tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description);
		}printf("\n\n\n");
		

	
}

 
void freeAllMemory(Ticket* tickets) {
	if (tickets == NULL) return;

	Ticket* tempTicket;
	while (tickets->nextTicket != NULL) {
		tempTicket = tickets;
		tickets = tickets->nextTicket;
		free(tempTicket);


	}
	free(tickets);

	//not sure if i need to free the memory allocated for the strings INSIDE of the structs


}

void rm_newline(char arr[]) {

	int index = 0;
	while (arr[index] != '\0') {

		if (arr[index] == '\n') {
			arr[index] = '\0';

		}

		index++;
	}


}


//the main part where the user may create/close tickets
void startTicketManagement() {

	//the id of the next ticket that may be created
	int nextID = 1; 
	Ticket* tickets = NULL; //set this to null   will end being the head of a linked list null pointer
	char userOption = '\0';

	while (1) {

		printf("\n\n");
		printf("Enter the number for option you would like\n(1) Create Ticket\n(2) Close Ticket\n(3) View All Tickets\n(4) Open Ticket Count\n(5) Tickets by Priority\n(6) Exit\nEnter a number: ");
		userOption = getchar();
		getchar(); //capture the newline character
		printf("\n\n");
		switch (userOption)
		{
		case '1':
			createTicket(&tickets, nextID); 
			nextID++;

			break;
		case '2':
			closeTicket(&tickets);
			break;
		case '3':
			printAllTickets(&tickets);
			break;
		case '4':
			printf("There are %d open tickets\n", getOpenTicketCount(&tickets));
			break;
		case '5':
			getTicketsByPriority(&tickets);
			break;
		case '6':
			printf("Exiting...\n");
			break;
		default:
			printf("Improper Input. Try Again!\n");
			break;
		}
	
		if (userOption == '6') {
			break;
		}


	}
	printf("Freeing all memory...\n");
	freeAllMemory(tickets); 	//free all the memmory

	printf("Thank you!");


}


int main(void){

	startTicketManagement();

	return 0;
}