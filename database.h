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
//  FILE:        database.h
//
//  DESCRIPTION:
//   contains the function declarations that are defined in
//   database.c
//
****************************************************************/
#include "record.h"

int addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char []);
int readfile(struct record **, char []);
void cleanup(struct record **);
