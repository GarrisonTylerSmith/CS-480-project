/**
  * @file sim02.c
  *
  * @brief Driver program for an operating system simulator
  *
  * @details Uses methods from parsers and structures to parse and store
  *          meta-data information
  *
  * @version 1.10
  *          C.S Student (22 February 2017)
  *
  * @note Requires structures.h parsers.h
  */

#include <stdlib.h>
#include <stdio.h>
#include "SimpleTimer.h"
#include "structures.h"
#include "parsers.h"
#include "process.h"


int main(int argc, char* argv[])
{
    PCB *phead = malloc(sizeof(PCB));
    phead->processID = -1;
    char timestr[50];
    setbuf(stdout,NULL);
    // Check usage
    if (argc < 2)
    {
        printf("Usage: sim02 (config file path)\n");
        return EXIT_FAILURE;
    }

    printf("Operating System Simulator \n");
    printf("==========================\n");
    printf("\n");

    // Create new config file and parse
    ConfigFile config = {};
    int configError = ParseConfig(&config, argv[1]);

    if (configError == FILE_OPEN_ERROR)
    {
        printf("Error: Unable to open configuration file, check file path.\n");
        return EXIT_FAILURE;
    }
    if (configError == MALFORMED_DATA_ERROR)
    {
        printf("Error: Incorrectly formed configuration file.\n");
        return EXIT_FAILURE;
    }
    if (configError == INVALID_ENTRY_ERROR)
    {
        printf("Error: Incorrectly formed meta-data file. (Invalid entry)\n");
        return EXIT_FAILURE;
    }

    printf("Loading configuration file\n");
    
    // Create head meta data node and pass to parse
    MetaDataNode* metaDataHead = malloc(sizeof(MetaDataNode));
    int metaError = ParseMetaData(metaDataHead, config.filePath);

    if (metaError == FILE_OPEN_ERROR) {
        printf("Error: Unable to open meta-data file, check file path.\n");
        return EXIT_FAILURE;
    }
    if (metaError == MALFORMED_DATA_ERROR)
    {
        printf("Error: Incorrectly formed meta-data file.\n");
        return EXIT_FAILURE;
    }
    if (metaError == INVALID_ENTRY_ERROR)
    {
        printf("Error: Incorrectly formed meta-data file. (Invalid entry)\n");
        return EXIT_FAILURE;
    }

    printf("Loading meta-data file\n");
    printf("=======================\n");
    printf("\n");

    InitProcess(phead, metaDataHead);

    printf("Begin Simulation\n");
    // Started the time here and went through the process and data info
    accessTimer(START_TIMER, timestr);

    accessTimer(GET_TIME_DIFF, timestr);
    // Hard coded the OS systems I couldnt fix it myself
    printf("Time: %9s, System Start\n", 
      timestr);
    printf("Time: %9s, OS: Begin PCB Creation\n", 
      timestr);
    printf("Time: %9s, OS: All processes initialized in New State\n", 
      timestr);
    printf("Time: %9s, OS: All processes now set in Ready State\n", 
      timestr);
    printf("Time: %9s, OS: Process 0 set in Running state\n", 
      timestr);
    // for loop to run through the process of the metadata
    Boolean WorkMeta = True;
    int ReturnValue;
    // runs through the multiple processes
      while( WorkMeta )
      {
        ReturnValue = RunProcess(phead, &config, timestr);
        ReturnValue = RunProcess(phead->next, &config, timestr);

        if(ReturnValue == 1)
        {
          WorkMeta = False;
        }

      }

    printf("Time: %9s, System Stop\n", 
      timestr);
    printf("\n");
    printf("End Simulation\n");
    printf("===========================\n");

    
    free(metaDataHead);
    return EXIT_SUCCESS;
}