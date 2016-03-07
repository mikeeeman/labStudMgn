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
 * @file helper.c
 * @author Andreas HABEGGER
 * @date 26 Jan 2016
 * @brief File containing helper definitions used by the program SMS
 *
 * @see http://linux.bfh.ch/
 * @bug currently no bugs
 * @todo no open tasks
 */

#include "helper.h"

/*
 * Public function definitions
 */
void error_msg(char *msg)
{
  fprintf(stderr, msg);
  fflush(stdout);
  return;
}

void exitSeq(char **msg, int num)
{
  for(num--; num >= 0; num--)
    {
      free(msg[num]);
    }
}

void flushStdin(void)
{
  int c;
  while((c = getchar()) != '\n' && c != EOF)
    /* discard */ ;
}
