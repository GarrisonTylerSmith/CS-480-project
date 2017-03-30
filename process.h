/**
  * @file process.h
  *
  * @brief Header file for parsing helper funcitons
  *
  *
  * @version 1.10
  *          C.S Student (22 February 2017)
  *
  * @note Requires structures.h
  * @note Requires SimpleTimer.h
  */
#include "structures.h"
#include "SimpleTimer.h"


#ifndef PROCESS_H
#define PROCESS_H

typedef struct PCB
{
	enum {New, Ready, Running, Exit}states;
	MetaDataNode* current;
	int processID;
  struct PCB *next;

} PCB;

/**
  * @brief Function to initialize the PCB variables
  *
  * @details Initailizes which state that the PCB is in 
  *
  * @param[in] PCB
  *            Gets the process that we are going to start with
  *
  * @param[in] MetaDataNode
  *            Gets the beginning of the linked list within the data 
  *					structure
  *
  * @note None
  */
void InitProcess( PCB*, MetaDataNode*);

/**
  * @brief Function to runs the process within the program
  *
  * @details Runs the process frame by frame 
  *
  * @param[in] PCB
  *            Gets the process that we are going to start with
  *
  * @param[in] ConfigFile
  *            Gets the configfile that the data needs to execute 
  *				
  * @param[in] Char
  *				the timestr for keeping track of the time
  *
  * @note None
  */
int RunProcess( PCB*, ConfigFile*, char* );

#endif
