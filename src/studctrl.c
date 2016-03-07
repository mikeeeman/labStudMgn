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
 * @file studctrl.c
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

#include "studctrl.h"

/*
 * Global private read only variables
 */

static const ScoreRec scoreTypes[] = {
  { 0, "Exit"},
  { 1, "Quiz 1"},
  { 2, "Quiz 2"},
  { 3, "Term Exam"},
  { 4, "Final Exam"}
};

/*
 * Private function declarations
 */

static void addScore(studRec_t studList[], int itemCount);

static int changeRec(const char msg[]);


/*
 * Public function definitions
 */
int addRec(studRec_t studList[], int *itemCount)
{
  size_t chars = 0;

  puts("Add new student record !!");
  fflush(stdout);

  printf("Set student's ID of new record [max %u characters]: ", (ID_SIZE-1) );
  fflush(stdout);
  scanf("%6s", studList[*itemCount].id );
  flushStdin();

  printf("Set student's family name : ");
  fflush(stdout);
  getline(&(studList[*itemCount].lname), &chars, stdin);
  strtok(studList[*itemCount].lname,"\n");

  printf("Set student's first name : ");
  fflush(stdout);
  chars = 0;
  getline(&(studList[*itemCount].fname), &chars, stdin);
  strtok(studList[*itemCount].fname,"\n");

  printf("Set student's email address [name@domain]: ");
  fflush(stdout);
  chars = 0;
  getline(&(studList[*itemCount].email), &chars, stdin);
  strtok(studList[*itemCount].email,"\n");

  printf("Set student's gender [m/f]: ");
  fflush(stdout);
  scanf("%1s", studList[*itemCount].sex );
  flushStdin();

  printf("Do you want add scores ? [y/N] ");
  fflush(stdout);
  if('y' == getchar())
  {
    flushStdin();
    addScore(studList, *itemCount);
  }

  (*itemCount)++;

  return EXIT_SUCCESS;

}

int searchRec(studRec_t studList[], char id[ID_SIZE], int itemCount)
{
  int index = -1;

  for(itemCount--;itemCount >= 0; itemCount--)
  {
    if(0 == strcmp(studList[itemCount].id, id))
    {
      index = itemCount;
      break;
    }
  }
  return index;
}

int searchRecMaxScore(studRec_t studList[], int itemCount)
{
  int isMaxScore = MIN_SCORE;
  int maxScoreIndex = -1;
  if(itemCount == 1)
    maxScoreIndex = 0;
  else if (itemCount > 1)
  {
    for(itemCount--; itemCount >= 0; itemCount--)
      if(isMaxScore < studList[itemCount].finalScore)
      {
        isMaxScore = studList[itemCount].finalScore;
        maxScoreIndex = itemCount;
      }
  }
  return maxScoreIndex;
}


int searchRecMinScore(studRec_t studList[], int itemCount)
{
  int isMinScore = MAX_SCORE;
  int minScoreIndex = -1;
  if(itemCount == 1)
    minScoreIndex = 0;
  else if (itemCount > 1)
  {
    for(itemCount--; itemCount >= 0; itemCount--)
      if(isMinScore > studList[itemCount].finalScore)
      {
        isMinScore = studList[itemCount].finalScore;
        minScoreIndex = itemCount;
      }
  }
  return minScoreIndex;
}


void viewRec(studRec_t studList[], int itemIdx)
{

  printf(" %s\t",studList[itemIdx].id);
  fflush(stdout);
  printf(" %s\t",studList[itemIdx].fname);
  fflush(stdout);
  printf(" %s\t",studList[itemIdx].lname);
  fflush(stdout);
  printf(" %s\t",studList[itemIdx].email);
  fflush(stdout);
  printf("  %s  ",studList[itemIdx].sex);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].quiz1);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].quiz2);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].termExam);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].finalExam);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].finalScore);
  fflush(stdout);
  printf(" %3.2f ",studList[itemIdx].avrScore);
  fflush(stdout);
  printf(" %d ",studList[itemIdx].finalGrade);
  fflush(stdout);
  printf("\n");
  return;
}

void viewAll(studRec_t studList[], int itemCount)
{
  int index = 0;

  printf("  ID       First Name     Family Name        E-Mail        G    Q1   Q2   TExam  FExam  Score   Avr  Grade\n");
  fflush(stdout);
  printf("------- --------------- ------------------ -------------- ---- ---- ----  ------ ------ ------ ----- -----\n");
  fflush(stdout);

  for(index = 0; index < itemCount; index++)
    viewRec(studList, index);

  return;
}

int delRec(studRec_t studList[], int *itemCount, int itemIdx)
{
  if(itemIdx<0 || itemIdx >= *itemCount)
  {
    puts("Error : index is not a valid position");
    fflush(stdout);
    return EXIT_FAILURE;
  }

  free(studList[itemIdx].fname);
  free(studList[itemIdx].lname);
  free(studList[itemIdx].email);

  for(; itemIdx < (*itemCount)-1; itemIdx++)
  {
    copyRec(&(studList[itemIdx]), &(studList[itemIdx+1]));
  }

  studList[itemIdx].id[0] = '\0';
  studList[itemIdx].fname = NULL;
  studList[itemIdx].lname = NULL;
  studList[itemIdx].email = NULL;
  studList[itemIdx].sex[0] = '\0';
  studList[itemIdx].quiz1 = 0;
  studList[itemIdx].quiz2 = 0;
  studList[itemIdx].termExam = 0;
  studList[itemIdx].finalExam = 0;
  studList[itemIdx].finalScore = 0;
  studList[itemIdx].finalGrade = Ns;
  studList[itemIdx].avrScore = 0;

  (*itemCount)--;

  return EXIT_SUCCESS;
}

void updateRec(studRec_t studList[], int itemIdx)
{

  size_t chars = 0;

  puts("Update student record... !!");
  fflush(stdout);

  if(changeRec("student's ID"))
  {
    printf("Set new student ID record [max %u characters]: ", (ID_SIZE-1) );
    fflush(stdout);
    scanf("%6s", studList[itemIdx].id );
    flushStdin();
  }

  if(changeRec("family name"))
  {
    free(studList[itemIdx].lname);
    printf("Set student's family name : ");
    fflush(stdout);
    chars = 0;
    getline(&(studList[itemIdx].lname), &chars, stdin);
  }

  if(changeRec("first name"))
  {
    free(studList[itemIdx].fname);
    printf("Set student's first name : ");
    fflush(stdout);
    chars = 0;
    getline(&(studList[itemIdx].fname), &chars, stdin);
  }

  if(changeRec("email address"))
  {
    free(studList[itemIdx].email);
    printf("Set student's email address [name@domain]: ");
    fflush(stdout);
    chars = 0;
    getline(&(studList[itemIdx].email), &chars, stdin);
  }


  if(changeRec("gender"))
  {
    printf("Set student's gender [m/f]: ");
    fflush(stdout);
    scanf("%1s", studList[itemIdx].sex );
    flushStdin();
  }

  printf("Do you want add/update scores ? [y/N] ");
  fflush(stdout);
  if('y' == getchar())
  {
    flushStdin();
    addScore(studList, itemIdx);
  }

  return;
}

void calcScoreFinal(studRec_t studList[], int itemIdx)
{
  studList[itemIdx].finalScore = (studList[itemIdx].quiz1 + studList[itemIdx].quiz2 +
                                  studList[itemIdx].termExam + studList[itemIdx].finalExam);
  return;

}

void calcScoreAvr(studRec_t studList[], int itemIdx)
{
  calcScoreFinal(studList, itemIdx);
  studList[itemIdx].avrScore = (studList[itemIdx].finalScore)/4;

  return;
}

void bubbleSort(studRec_t studList[], int itemCount)
{
  studRec_t temp;
  int noSwap = 1, idx = 0;

  if(itemCount > 1)
  {
    while(1)
    {
      noSwap = 1;
      for(idx = 0; idx < (itemCount-1); idx++)
      {
        if(studList[idx].finalScore < studList[idx+1].finalScore )
        {
          copyRec(&temp, &(studList[idx]));
          copyRec(&(studList[idx]), &(studList[idx+1]));
          copyRec(&(studList[idx+1]), &temp);
          noSwap = 0;
        }
      }
      if(noSwap)
        break;
    }
  }
  return;
}

void copyRec(studRec_t *dest, studRec_t *src)
{
  strcpy(dest->id, src->id);
  dest->fname = src->fname;
  dest->lname = src->lname;
  dest->email = src->email;
  strcpy(dest->sex, src->sex);
  dest->quiz1 = src->quiz1;
  dest->quiz2 = src->quiz2;
  dest->termExam = src->termExam;
  dest->finalExam = src->finalExam;
  dest->finalScore = src->finalScore;
  dest->finalGrade = src->finalGrade;
  dest->avrScore = src->avrScore;
  return;
}

/*
 * Private function definitions
 */

static void addScore(studRec_t studList[], int itemCount)
{
  int typeOfScore = 0, index;

  do{
    puts("What score do you want to edit:");
    fflush(stdout);
    for(index=0; (unsigned)index < sizeof(scoreTypes)/sizeof(ScoreRec); index++)
    {
      printf("%d\t%s\n",scoreTypes[index].code, scoreTypes[index].desc);
      fflush(stdout);
    }
    typeOfScore = getchar();
    typeOfScore -= '0';

    printf("Your choise is %d\n", typeOfScore);
    fflush(stdout);
    switch(typeOfScore){
      case 1:
        printf("Add score for %s [00.00 - 99.99]:", scoreTypes[typeOfScore].desc);
        fflush(stdout);
        scanf("%f", &(studList[itemCount].quiz1) );
        flushStdin();
        break;
      case 2:
        printf("Add score for %s [00.00 - 99.99]:", scoreTypes[typeOfScore].desc);
        fflush(stdout);
        scanf("%f", &(studList[itemCount].quiz2) );
        flushStdin();
        break;
      case 3:
        printf("Add score for %s [00.00 - 99.99]:", scoreTypes[typeOfScore].desc);
        fflush(stdout);
        scanf("%f", &(studList[itemCount].termExam) );
        flushStdin();
        break;
      case 4:
        printf("Add score for %s [00.00 - 99.99]:", scoreTypes[typeOfScore].desc);
        fflush(stdout);
        scanf("%f", &(studList[itemCount].finalExam) );
        flushStdin();
        break;
      default:
        puts("No valid value!");
        fflush(stdout);
        break;
    }
  }while(typeOfScore != 0);
}

static int changeRec(const char msg[])
{
  char willChange = 0;

  while(1)
  {
    printf("\nWould you like to change the record for %s [y/n]:",msg);
    fflush(stdout);
    scanf("%c", &willChange);
    flushStdin();
    if(willChange == 'y' || willChange == 'Y')
    {
      willChange = 1;
      break;
    }
    else if(willChange == 'n' || willChange == 'N')
    {
      willChange = 0;
      break;
    }
  }
  return willChange;
}
