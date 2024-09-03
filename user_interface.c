/*****************************************************************
//
//  NAME:        Shaelyn Loo
//
//  HOMEWORK:    project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 26, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file holds the user itnerface for the bank records
//   database. It also holds the getaddress function that is
//   used when adding new records to the database and the
//   getAccountNum function that is used when checking for valid
//   account numbers
//
****************************************************************/

#include <stdio.h>
#include <string.h>

#include "database.h"

void getaddress(char[], int);
void getAccountNum(int*);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This function acts as the user interface and menu 
//                 option for the bank record database assignment
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int debugmode = 0;

int main(int argc, char* argv[])
{
    struct record * start = NULL;

    int i;
    int run = 1;
    int length;
    int repeat = 0;

    int newAccNo;
    int findAccNo;
    int delAccNo;
    char address[50];
    char newName[30];
    char userInput[100];
    char hold[100];

    char acceptedDebug[] = "debug";
    char acceptedAdd[] = "add";
    char acceptedPrintall[] = "printall";
    char acceptedFind[] = "find";
    char acceptedDelete[] = "delete";
    char acceptedQuit[] = "quit";
    char filename[] = "records.txt";

    if (argc > 2)
    {
        printf("bash:");
        for (i = 1; i < argc; i++)
        {
            printf(" %s", argv[i]);
        }
        printf(": command not found\n");
        run = 0;
    }
    else if (argc == 2)
    {
        if (strcmp(acceptedDebug, argv[1]) == 0)
        {
            debugmode = 1;
        }
        else if (strcmp(acceptedDebug, argv[1]) != 0)
        {
            printf("bash: %s: command not found\n", argv[1]);
            run = 0;
        }
    }

    readfile(&start, filename);

    while (run == 1)
    {
        if (repeat == 0)
        {
            printf("\nWelcome to the user interface of this banking systems record tracker!\n");
            repeat = 1;
        }
        printf("\n");
        printf("Please enter one of the following options for what you would like to do:\n");
        printf("\n");
        printf("add: if you would like to add a record\n");
        printf("printall: if you would like to print all reccords currently in the database\n");
        printf("find: if you would like to find a certain record\n");
        printf("delete: if you would like to delete a record\n");
        printf("quit: if you would like to quit the program\n");

        scanf("%s", userInput);
        fgets(hold, 100, stdin);

        if (strncmp(acceptedAdd, userInput, strlen(userInput)) == 0)
        {
            printf("please enter your account number: \n");

            getAccountNum(&newAccNo);

            fgets(hold, 100, stdin);

            printf("please enter your name: \n");
            fgets(newName, 30, stdin);
            length = strlen(newName);

            if (length > 0 && newName[length - 1] == '\n')
            {
                newName[length - 1] = '\0';
            }

            printf("please enter your address: (you must hit the ']' key followed by the enter key when you are done typing your address)\n");
            getaddress(address, 50);

            if (addRecord(&start, newAccNo, newName, address) == -1)
            {
                printf("record could not be added because an account with that number already exists\n");
            }
            else
            {
                printf("record was successfully added\n");
            }
        }
        else if (strncmp(acceptedPrintall, userInput, strlen(userInput)) == 0)
        {
            printAllRecords(start);
        }
        else if (strncmp(acceptedFind, userInput, strlen(userInput)) == 0)
        {
            printf("enter the record you want to find by entering the account number: \n");

            getAccountNum(&findAccNo);

            fgets(hold, 100, stdin);

            if (findRecord(start, findAccNo) == -1)
            {
                printf("record could not be found\n");
            }
        }
        else if (strncmp(acceptedDelete, userInput, strlen(userInput)) == 0)
        {
            printf("enter the account number you would like to delete\n");

            getAccountNum(&delAccNo);

            fgets(hold, 100, stdin);

            if (deleteRecord(&start, delAccNo) == -1)
            {
                printf("record could not be deleted\n");
            }
            else
            {
                printf("record was successfully deleted\n");
            }
        }
        else if (strncmp(acceptedQuit, userInput, strlen(userInput)) == 0)
        {
            writefile(start, filename);
            cleanup(&start);
            run = 0;
        }
        else
        {
            printf("Please enter a valid input\n");
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   This function takes user input for their address 
//                 and allows the user to enter a multi line address
//
//  Parameters:    address (char[]) : starting address of the array 'address'
//                                    that gets passed so the array can update and 
//                                    hold the necessary characters
//                 length (int) : the length of the array passed
//
//  Return values:  no return values
//
****************************************************************/

void getaddress(char address[], int length)
{
    int i;
    char character;
    int index = 0;
    char hold[100];

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: getaddress\n");
        printf("PARAMETER NAME: address\n");
        printf("VALUE OF address: ");
        for (i = 0; i < sizeof(address); i++)
        {
            printf("%c", address[i]);
        }
        printf("\nPARAMETER NAME: length\n");
        printf("VALUE OF length: %d\n", length);
        printf("===================================================\n");
        printf("\n");
    }

    for (index = 0; index < length; index++)
    {
        character = fgetc(stdin);
        address[index] = character;

        if (character == ']')
        {
            address[index] = '\0';
            index = 50;
        }
    }
    fgets(hold, 100, stdin);
}

/*****************************************************************
//
//  Function name: getAccountNum
// 
//  DESCRIPTION:   This function checks the user inputs account number
//                 to make sure it is a valid account number 
//  
//  Parameters:    AccNo (int *) : the pointer which points to the
//                                 integer being checked
//
//  Return values:  no return values
//  
********************************************************************/

void getAccountNum(int *AccNo)
{
    int valid = 0;
    char hold[100];

    if ( debugmode == 1 )
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: getAccountNum\n");
        printf("PARAMETER NAME: AccNo\n");
        printf("VALUE of AccNo: %d\n", *AccNo);
        printf("===================================================\n");
        printf("\n");
    }

    while (!valid)
    {
        if (scanf("%d", AccNo) != 1)
        {
            printf("not an integer, try again\n");
            fgets(hold, 100, stdin);
        }
        else if (*AccNo <= 0)
        {
            printf("please put a positive value\n");
        }
        else
        {
            valid = 1;
        }
    }
    valid = 0;
}
