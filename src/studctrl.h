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
 * @file  studctrl.h
 * @author Andreas HABEGGER
 * @date 26 Jan 2016
 * @brief Interface description of file studctrl.
 *
 * @see http://linux.bfh.ch/
 * @bug currently no bugs
 * @todo no open tasks
 */

#ifndef STUDCTRL_H
#define STUDCTRL_H

#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <string.h>


#define ID_SIZE 7
#define MIN_SCORE 0

#define MAX_SCORE 999

typedef enum { A, B, C, D, E, Fx, F, Ns } GRADE;

typedef struct studRec_s{
  char id[ID_SIZE];
  char* fname;
  char* lname;
  char* email;
  char  sex[2];
  float quiz1;
  float quiz2;
  float termExam;
  float finalExam;
  float finalScore;
  float avrScore;
  GRADE finalGrade;
} studRec_t;

typedef struct {
  int code;        /**< Code symbol of a menu record */
  char *desc;      /**< Corresponding menu record description */
} ScoreRec;

int addRec(studRec_t studList[], int *itemCount);

void copyRec(studRec_t *dest, studRec_t *src);

int delRec(studRec_t studList[], int *itemCount, int itemIdx);

void updateRec(studRec_t studList[], int itemIdx);

int searchRec(studRec_t studList[], char id[ID_SIZE], int itemCount);

int searchRecMaxScore(studRec_t studList[], int itemCount);

int searchRecMinScore(studRec_t studList[], int itemCount);

void viewRec(studRec_t studList[], int itemIdx);

void viewAll(studRec_t studList[], int itemCount);

void calcScoreFinal(studRec_t studList[], int itemIdx);

void calcScoreAvr(studRec_t studList[], int itemIdx);

void bubbleSort(studRec_t studList[], int itemCount);

#endif // STUDCTRL_H
