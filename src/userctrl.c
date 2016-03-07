/****************************************************************************
 * Copyright (C) 2016 by Andreas Habegger                                   *
 *                                                                          *
 * This file is part of Student Management System (SMS) - BTF1230           *
 *                                                                          *
 *   TMA is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   SMS is distributed in the hope that it will be useful, to students     *
 *   following the course BTF1230 at Bern University but WITHOUT ANY        *
 *   WARRANTY. See the GNU Lesser General Public License for more details.  *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with TMA.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file userctrl.c
 * @author Andreas HABEGGER
 * @date 26 Jan 2016
 * @brief In this file are all function descriptions (public and privat)
 * The public declared functions in coresponding header file are defined here. Additionally
 * are private (static) functions declared and described here.
 *
 * @see http://linux.bfh.ch/
 * @bug currently no bugs
 * @todo no open tasks
 */

#include "userctrl.h"

#define NUM_OF_OPTIONS sizeof(dialogue)/sizeof(OptionEntry)

/*
 * Global private read only variables
 */

static const OptionEntry dialogue[] = {
                 { 1 , "Add studnet records"},
                 { 2 , "Delete student record"},
                 { 3 , "Modify student record"},
                 { 4 , "View all student records "},
                 { 5 , "Calculate an average of a selected student's scores"},
                 { 6 , "Show student who gets the max total score"},
                 { 7 , "Show student who gets the min total score"},
                 { 8 , "Find student by ID"},
                 { 9 , "Sort recorts by total scores"},
                 { 10 ,"Display \"Control Menu\""},
                 { 11 ,"Exit program"}
                };

/*
 * Private function declarations
 */

static unsigned int isValid(unsigned int selection);

static const char menuHeader[] = "Control Menu - Student Management System";


/*
 * Public function definitions
 */

unsigned int getFirstEntry()
{
  return dialogue[0].code;
}

unsigned int getLastEntry()
{
  return dialogue[NUM_OF_OPTIONS-1].code;
}

void displayMenu(void)
{
  unsigned int index;

  puts("*******************************************************************************");
  fflush(stdout);
  printf("** \t\t%s \n",menuHeader);
  fflush(stdout);
  puts("*******************************************************************************\n");
  fflush(stdout);

  puts("Select one of the available options");
  fflush(stdout);
  for(index=0; index < NUM_OF_OPTIONS; index++)
  {
    printf("%3.u : %s\n", dialogue[index].code, dialogue[index].desc);
    fflush(stdout);
  }

  printf("\nWhat is your choise [%u - %u] : ",dialogue[0].code, dialogue[NUM_OF_OPTIONS-1].code);
  fflush(stdout);
}

void displayChoise(unsigned int help)
{
  printf("\nType %u for help dialogue : ",help);
  fflush(stdout);
  printf("\nWhat is your choise [%u - %u] : ",dialogue[0].code, dialogue[NUM_OF_OPTIONS-1].code);
  fflush(stdout);
}

unsigned int getSel(void)
{
  unsigned int selection = 0;

  scanf("%u",&selection);
  flushStdin();

  while( !isValid(selection) )
    {
      puts("Selection not valid. Try again :");
      fflush(stdout);
      scanf("%u",&selection);
      flushStdin();
    }

  return selection;
}

/*
 * Private function definitions
 */

static unsigned int isValid(unsigned int selection)
{
  unsigned int index;

  for(index = 0; index < NUM_OF_OPTIONS; index++)
    {
       if(dialogue[index].code == selection)
         return 1;
    }
  return 0;
}
