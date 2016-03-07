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
 * @file studentMgnSystem.c
 * @author Andreas HABEGGER
 * @date 26 Jan 2016
 * @brief This file is main file of Student Management System
 *
 * @see http://linux.bfh.ch/
 * @bug currently no bugs
 * @todo no open tasks
 */
/* meyec2 notiz*/

#include <stdio.h>

#include "helper.h"
#include "userctrl.h"
#include "studctrl.h"

#define MAX_ENTRIES 20
#define IS_LIST_FULL(entries, max) ((entries)<(max)?0:1)

void initStudentList(studRec_t studList[], int entries);

int whichRec(const char msg[], studRec_t studList[], int itemCount);

int main(void)
{
  studRec_t myList[MAX_ENTRIES];
  int studEntries = 0, index;
  char searchID[ID_SIZE];
  bool isEnable = true;
  bool menuPrinted = false;


  initStudentList(myList, MAX_ENTRIES);

  displayMenu();

  while(isEnable){
      switch(getSel()){
        case 1:
          if(!IS_LIST_FULL(studEntries, MAX_ENTRIES))
            addRec(myList, &studEntries);
          else
          {
            puts("List is full");
            fflush(stdout);
          }
          break;
        case 2:
          index = whichRec("delete", myList, studEntries) - 1;
          delRec(myList, &studEntries, index);
          break;
        case 3:
          index = whichRec("update", myList, studEntries) - 1;
          updateRec(myList, index);
          break;
        case 4:
          viewAll(myList, studEntries);
          break;
        case 5:
          index = whichRec("average", myList, studEntries) - 1;
          calcScoreAvr(myList, index);
          viewRec(myList,index);
          break;
        case 6:
          for(index = 0; index < studEntries; index++)
            calcScoreFinal(myList, index);
          index = searchRecMaxScore(myList, studEntries);
          puts("\nStudent with the higest score \n");
          fflush(stdout);
          viewRec(myList, index);
          break;
        case 7:
          for(index = 0; index < studEntries; index++)
            calcScoreFinal(myList, index);
          index = searchRecMinScore(myList, studEntries);
          puts("\nStudent with the lowest score \n");
          fflush(stdout);
          viewRec(myList, index);
          break;
        case 8:
          printf("Search for record by ID [max %u characters]: ", (ID_SIZE-1) );
          fflush(stdout);
          fgets(searchID, ID_SIZE-1, stdin);
          strtok(searchID,"\n");
          index = searchRec(myList, searchID, studEntries);
          if(index == -1)
          {
            printf("No record in the list with ID %s\n", searchID);
          fflush(stdout);
          }
          else
            viewRec(myList, index);
          break;
        case 9:
          bubbleSort(myList, studEntries);
          break;
        case 10:
          displayMenu();
          menuPrinted = true;
          break;
        case 11:
          puts("Stop application...");
          fflush(stdout);
          isEnable = false;
          break;
        default:
          break;
        }
      if(isEnable && !menuPrinted)
        displayChoise(10);
      else
        menuPrinted = !menuPrinted;
    }


//  viewRec(myList, 0);

  return 0;
}


void initStudentList(studRec_t studList[], int entries)
{
  for(entries--; entries >= 0; entries--)
    {
      studList[entries].fname = NULL;
      studList[entries].lname = NULL;
      studList[entries].email = NULL;
      studList[entries].quiz1 = 0;
      studList[entries].quiz2 = 0;
      studList[entries].termExam = 0;
      studList[entries].finalExam = 0;
      studList[entries].finalGrade = 0;
      studList[entries].avrScore = 0;
    }
}

int whichRec(const char msg[], studRec_t studList[], int itemCount)
{
  int record = 0;
  printf("Which record do you want to %s : ",msg);
  fflush(stdout);
//  flushStdin();

  while(1){
      scanf("%d", &record);
      flushStdin();
      if(record > 0 && record < itemCount+1)
        break;
      printf("Record %d is not valid! Valid entries [%d - %d]\n", record, 1, itemCount+1);
      fflush(stdout);
      printf("Do you want available records listed [y/N]\n");
      fflush(stdout);
      record = getchar();
      if(record == 'y')
        viewAll(studList, itemCount);
    }
  return (record);
}
