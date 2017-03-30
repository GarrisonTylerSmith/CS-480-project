#include "process.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
/**
  * @file process.c
  *
  * @brief Driver program process structures to run processes
  *
  * @details Allows to intiialize the process and then run the process
  *          
  *
  * @version 1.10
  *          C.S Student (22 February 2017)
  *
  * @note Requires process.h
  * @note Requires structures.h
  */

void InitProcess( PCB* phead, MetaDataNode* mhead )
{
    MetaDataNode* current;
    // PCB* totalCycles;
    PCB* newProcess = malloc(sizeof(PCB));
    MetaDataNode* prevCurrent;
    current = mhead;
    int processIncrement = 0;
    PCB* lastProcess;
    // loop to check if we have data in the file
    while(current != NULL)
    {
      // checks the start of the metadata file
        if( current->commandLetter == 'A' && strcmp(current->operation,"start") == 0 )
        {
          // makes a new process if we dont have one
            if(phead->processID == -1)
            {
                phead->states = New;
                phead->current = current->next;
                phead->processID = processIncrement++;
                lastProcess = phead;
            }
            // if we do have one add a new one to the existing one
            else
            {
                newProcess->states = New;
                newProcess->current = current->next;
                newProcess->processID = processIncrement++;
                lastProcess->next = newProcess;
                lastProcess = newProcess;
            }
        }

        prevCurrent = current;
        current = current->next;
        // gets the end of the metadata file
        if( prevCurrent->commandLetter == 'A' && strcmp(prevCurrent->operation,"end") == 0 )
        {
            prevCurrent->next = NULL;
        } 
    }
}

int RunProcess( PCB* process,ConfigFile* config, char* timestr )
{
    MetaDataNode* current = process->current;
    char* outputString = NodeToString(current);


    if(current->cycleTime != 0)
    {
        accessTimer(GET_TIME_DIFF, timestr);
        printf("Time: %9s, Process %d, %s start\n", 
            timestr, process->processID, outputString);
        delay(50);
        printf("Time: %9s, Process %d, %s end\n", 
            timestr, process->processID, outputString);
        
    }
    process->current = current->next;

    if(process->current == NULL)
    {
        return 1;
    }

    return 0;
}