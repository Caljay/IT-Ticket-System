#include <stdio.h>
#include <stdlib.h>

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
}Ticket;

//all the  functions for ticket creation and addition

char* getName() {

	char* name = malloc(sizeof(char) * 50);
	printf("Please Enter your name: ");
	fgets(name, 50, stdin);
	return name;


}
char* getEmail() {
	char* email = malloc(sizeof(char) * 50);
	printf("Please Enter your email: ");
	fgets(email, 50, stdin);
	return email;
}
char* getDate() {
	char* date = malloc(sizeof(char) * 15); //less characters needed due to the input format
	printf("Please Enter the date MM/DD/YYYY: ");
	fgets(date, 15, stdin);
	return date;

}
int getPriority() {
	int priority = -1;
	printf("What is the priority of this issue. 1 = LOW 5 = HIGH: ");
	priority = (int)getchar() - 48;
	getchar(); //capture newline
	return priority;
}
char* getDescription() {

	char* description = malloc(sizeof(char) * 1000);
	printf("Please describe the issue (1000 character max): ");
	fgets(description, 1000, stdin);
	return description;




}
void createTicket(Ticket** tickets, int id) {

	Ticket* newTicket = NULL;
	Ticket* tempTicket = NULL;
	if (*tickets == NULL) { //if there are no current tickets

		*tickets = (Ticket*)malloc(sizeof(Ticket));

		(*tickets)->id = id;
		(*tickets)->name = getName();
		printf("%s ", (*tickets)->name);

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
	
	newTicket->id = id;
	newTicket->name = getName();
	printf("%s ", newTicket->name);

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

	char* solution = malloc(sizeof(char) * 1000);
	printf("What was the solution for this issue: ");
	fgets(solution, 1000, stdin);	//getchar(); //capture newline
	return solution;



}


int getOpenTicketCount(Ticket** tickets) {

	int ticketsOpen = 0;
	Ticket* tempTicket = *tickets;
	if (*tickets == NULL) return;

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
	int openTickets = getOpenTicketCount(tickets);
	int* ticketID_Priorties = malloc(sizeof(int) * openTickets); //the most tickets within a certain priortiy is equal to the tickets currently open
	int ticketID_PrioritiyArrayIndex = 0;
	Ticket* tempTicket = *tickets;

	for (int priority = 1; priority <= 5; priority++) {
		tempTicket = *tickets; //must restart every single pass
		ticketID_PrioritiyArrayIndex = 0;

		while (tempTicket->nextTicket != NULL) {
		
			if (tempTicket->priority == priority) {

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
	


	printf("\n\n");

}



//for niceities
void printAllTickets(Ticket** tickets) {
	
	Ticket* tempTicket = *tickets;
	printf("Printing all tickets\n");
	if (tempTicket == NULL) return;


		while (tempTicket->nextTicket != NULL) {

			printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s Solution: %s",
				tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description, tempTicket->issue_solution);
			printf("\n");


			tempTicket = tempTicket->nextTicket;
		}
		printf("ID: %d Name: %s Date: %s Priority: %d Closed: %d Description: %s Solution: %s",
			tempTicket->id, (tempTicket)->name, tempTicket->date, tempTicket->priority, tempTicket->is_closed, tempTicket->issue_description, tempTicket->issue_solution);
		printf("\n");
		printf("\n");
		printf("\n");

	




}

/*
just some temples of functions i am going to need
*/
 
void freeAllMemory(Ticket* tickets) {
	if (tickets == NULL) return;

	Ticket* tempTicket;
	while (tickets->nextTicket != NULL) {
		tempTicket = tickets;
		tickets = tickets->nextTicket;
		free(tempTicket);
//		1, 2, 3 NULL


	}
	free(tickets);

	//not sure if i need to free the memory allocated for the strings INSIDE of the structs




}

//the main part where the user may create/close tickets
void startTicketManagement() {

	//the id of the next ticket that may be created
	int nextID = 1; 
	Ticket* tickets; //set this to null   will end being the head of a linked list null pointer
	tickets = NULL;
	char userOption = '\0';

	while (1) {


		printf("Enter the number for option you would like\n(1) Create Ticket\n(2) Close Ticket\n(3)View All Tickets\n(4) Open Ticket Count\n(5) Tickets by Priority\n(6) Exit\nEnter a number: ");
		userOption = getchar();
		getchar(); //capture the newline character

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
			printf("There are %d open tickets", getOpenTicketCount(&tickets));
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
	freeAllMemory(tickets);
	printf("Thank you!");
	//free all the memmory









}



int main(void){

	startTicketManagement();






	return 0;







}