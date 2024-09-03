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
//  FILE:        database.c
//  
//  DESCRIPTION:
//   This file holds the function definition of the database
//   functions for project 1
//  
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

/*****************************************************************
//
//  Function name: addRecord
//  
//  DESCRIPTION:   adds a new record to the database in descending 
//                 order and does not allow duplicates
//  
//  Parameters:    start (struct record **) : a pointer that points to
//                                            the pointer called start
//                 accountNo (int) : the account number that is used when
//                                   creating and adding a new record
//                 name (char []) : the name used when creating and
//                                  adding a new record
//                 address (char []) : the addressed used when creating
//                                     and adding a new record
//
//  
//  Return values:  -1 : record could not be added
//                   0 : record successfully added 
//  
********************************************************************/

extern int debugmode;

int addRecord(struct record ** start, int accountNo, char name[ ], char address[ ] )
{
    struct record *temp;
    struct record *tracker;
    struct record *back;
    int result;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: addRecord\n");
        printf("PARAMETER NAME: accountNo\n");
        printf("VALUE OF accountNo: %d\n", accountNo);
        printf("PARAMETER NAME: name \n");
        printf("VALUE OF name: %s\n", name);
        printf("PARAMETER NAME: address \n");
        printf("VALUE OF address: \n%s", address);
        printf("\n===================================================\n");
        printf("\n");
    }

    if (*start == NULL)
    {
        *start = (struct record *)malloc(sizeof(struct record));
        (*start)->accountno = accountNo;
        strcpy((*start)->name, name);
        strcpy((*start)->address, address);
        (*start)->next = NULL;
        result = 0;
    }
    else if (*start != NULL)
    {
        if ((*start)->accountno == accountNo)
        {
            result = -1;
        }
        if ((*start)->accountno < accountNo)
        {
            temp = (struct record *)malloc(sizeof(struct record));
            temp->accountno = accountNo;
            strcpy(temp->name, name);
            strcpy(temp->address, address);
            temp->next = *start;
            *start = temp;
            result = 0;
        }
        else if ((*start)->accountno > accountNo)
        {
            tracker = *start;
            while (tracker != NULL)
            {
                if (accountNo == tracker->accountno)
                {
                    result = -1;
                    tracker = NULL;
                }
                else if ((accountNo < tracker->accountno) && (tracker->next != NULL))
                {
                    back = tracker;
                    tracker = tracker->next;
                }
                else if ((accountNo < tracker->accountno) && (tracker->next == NULL))
                {
                    temp = (struct record *)malloc(sizeof(struct record));
                    temp->accountno = accountNo;
                    strcpy(temp->name, name);
                    strcpy(temp->address, address);
                    tracker->next = temp;
                    temp->next = NULL;
                    result = 0;
                    tracker = NULL;
                }
                else if ( accountNo > tracker->accountno )
                {
                    temp = (struct record *)malloc(sizeof(struct record));
                    temp->accountno = accountNo;
                    strcpy(temp->name, name);
                    strcpy(temp->address, address);
                    back->next = temp;
                    temp->next = tracker;
                    result = 0;
                    tracker = NULL;
                }
            }
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: printAllRecords
//    
//  DESCRIPTION:   a function that prints all records in the database
//    
//  Parameters:    start (struct record *) : the starting address
//    
//  Return values:  no return values
//    
***********************************************************************/

void printAllRecords(struct record * start)
{
    struct record * temp;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: printAllRecords\n");
        printf("===================================================\n");
        printf("\n");
    }

    if (start == NULL)
    {
        printf("no records to print\n");
    }
    else if (start != NULL)
    {
        temp = start;
        while (temp != NULL)
        {
            printf("Account Number: %d\n", temp->accountno);
            printf("Name: %s\n", temp->name);
            printf("Address: %s\n", temp->address);
            printf("\n");

            temp = temp->next;
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//    
//  DESCRIPTION:   a function that finds the record specified
//                 by the account number
//    
//  Parameters:    start (struct record *) : the starting address
//                 accountNo (int) : account number used to find the
//                                   corresponding record
//    
//  Return values:  0 : record found
//                 -1 : record could not be found
//    
************************************************************************/

int findRecord(struct record * start, int accountNo)
{
    struct record * temp;
    int result;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: findRecord\n");
        printf("PARAMETER NAME: accountNo\n");
        printf("VALUE OF accountNo: %d\n", accountNo);
        printf("===================================================\n");
        printf("\n");
    }

    if (start == NULL)
    {
        result = -1;
    }
    else if (start != NULL)
    {
        if (accountNo > start->accountno)
        {
            result = -1;
        }
        if (accountNo == start->accountno)
        {
            printf("Account Number: %d\n", start->accountno);
            printf("Name: %s\n", start->name);
            printf("Address: %s\n", start->address);
            printf("\n");
        }
        else if (accountNo < start->accountno)
        {
            temp = start;
            result = -1;

            while (temp != NULL)
            {
                if (accountNo < temp->accountno)
                {
                    temp = temp->next;
                }
                else if (accountNo == temp->accountno)
                {
                    printf("Account Number: %d\n", temp->accountno);
                    printf("Name: %s\n", temp->name);
                    printf("Address: %s\n", temp->address);
                    printf("\n");
                    result = 0;
                    temp = NULL;
                }
                else if (accountNo > temp->accountno)
                {
                    temp = NULL;
                }
            }
        }
    }
    return result;
}

/*****************************************************************
//
//  Function name: deleteRecord
//    
//  DESCRIPTION:   a function that deletes a record
//                 specified by the account number
//  
//  Parameters:    start (struct record **) : a pointer that points to
//                                            the pointer called start
//                 accountNo (int) : account number used to find the
//                                   corresponding record
//    
//  Return values:  0 : record successfully deleted
//                 -1 : record could not be deleted
//  
************************************************************************/

int deleteRecord(struct record ** start, int accountNo)
{
    struct record * temp;
    struct record * back;
    int result;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: deleteRecord\n");
        printf("PARAMETER NAME: accountNo\n");
        printf("VALUE OF accountNo: %d\n", accountNo);
        printf("===================================================\n");
        printf("\n");
    }

    if (*start == NULL)
    {
        result = -1;
    }
    else if (*start != NULL)
    {
        if (accountNo > (*start)->accountno)
        {
            result = -1;
        }
        if (accountNo == (*start)->accountno)
        {
            temp = *start;
            (*start) = (*start)->next;
            free(temp);
            result = 0;
        }
        else if (accountNo < (*start)->accountno)
        {
            temp = *start;
            result = -1;

            while (temp != NULL)
            {
                if (accountNo < temp->accountno)
                {
                    back = temp;
                    temp = temp->next;
                }
                else if (accountNo == temp->accountno)
                {
                    back->next = temp->next;
                    free(temp);
                    result = 0;
                    temp = NULL;
                }
                else if (accountNo > temp->accountno)
                {
                    temp = NULL;
                }
            }
        }
    }
    return result;
}

/*****************************************************************
//
//  Function name: writefile
//      
//  DESCRIPTION:   a function that writes all of the contents of the
//                 linked list to a file
//    
//  Parameters:    start (struct record *) : starting address of the 
//                                           linked list
//                 filename (char []) : the file name being written to
//     
//  Return values:  0 : file was able to be accessed
//                 -1 : file was not able to be accessed
//   
*****************************************************************************/

int writefile(struct record * start, char filename[])
{
    int success = 0;
    FILE * outfile;
    struct record * temp;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: writefile\n");
        printf("PARAMETER NAME: filename\n");
        printf("VALUE OF filename: %s\n", filename);
        printf("===================================================\n");
        printf("\n");
    }

    outfile = fopen(filename, "w");

    if (outfile == NULL)
    {
        success = -1;
    }
    else
    {
        temp = start;
        while (temp != NULL)
        {
            fprintf(outfile, "%d\n", temp->accountno);
            fprintf(outfile, "%s\n", temp->name);
            fprintf(outfile, "%s]\n", temp->address);

            temp = temp->next;
        }
    }
    return success;
}

/*****************************************************************
//
//  Function name: readfile
//        
//  DESCRIPTION:   a function that reads from the file the records are
//                 stored into and puts into the linked list
//    
//  Parameters:    start (struct record **) : a pointer that points to
//                                            the pointer called start
//                 filename (char []) : the file name that is being read from
//      
//  Return values:  0 : file successfully opened
//                 -1 : file could not be opened
//     
*********************************************************************************/

int readfile(struct record ** start, char filename[])
{
    FILE *infile;
    int success = 0;
    int accountNo;
    int index = 0;
    char character;
    int length;

    char name[30];
    char address[50];
    char hold[100];

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: readfile\n");
        printf("PARAMETER NAME: filename\n");
        printf("VALUE OF filename: %s\n", filename);
        printf("===================================================\n");
        printf("\n");
    }

    infile = fopen(filename, "r");

    if (infile == NULL)
    {
        success = -1;
    }
    else
    {
        while (fscanf(infile, "%d", &accountNo) != EOF)
        {
            fgets(hold, 100, infile);

            fgets(name, 30, infile);
            length = strlen(name);
            if (length > 0 && name[length - 1] == '\n')
            {
                name[length - 1] = '\0';
            }

            for (index = 0; index < 50; index++)
            {
                character = fgetc(infile);
                address[index] = character;

                if (character == ']')
                {
                    address[index] = '\0';
                    index = 50;
                }
            }
            index = 0;
            addRecord(start, accountNo, name, address);
        }
        fclose(infile);
    }
    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//      
//  DESCRIPTION:   a function that releases all records on the heap
//                 before the user exists the program and sets start
//                 back to NULL
//      
//  Parameters:    start (struct record **) : a pointer that points to
//                                            the pointer called start
//     
//  Return values:  No return values
//     
*********************************************************************************/

void cleanup(struct record ** start)
{
    struct record * temp;
    struct record * back;

    if (debugmode == 1)
    {
        printf("===================================================\n");
        printf("FUNCTION NAME: cleanup\n");
        printf("===================================================\n");
        printf("\n");
    }

    if (*start != NULL)
    {
        temp = *start;
        while (temp != NULL)
        {
            back = temp;
            temp = temp->next;
            free(back);
        }
    }
    *start = NULL;
}
