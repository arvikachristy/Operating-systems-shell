/****************************************************************************
 * Copyright (C) 2016 by Anastasia Arvika Christy                           *
 *                                                                          *
 *                                                                          *
 *  These functions adds the shell the capability to handle assignment to	*
 *  $HOME and $PATH from the command line (e.g., $HOME=/home/os2) and to 	*
 *  act upon These cd command by changing the working directory as specified*
 *  (or to the HOME directory by default).                                  *
 *                                                                          *
 ****************************************************************************/
 
int dollarHome(char* dollarInput, char* home);

int dollarPath(char* dollarInputPath, char* path);