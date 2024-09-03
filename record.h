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
//  DATE:        October 29, 2112
//  
//  FILE:        record.h
//  
//  DESCRIPTION:
//   defines the datatype 'record' and what it holds
//
********************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
