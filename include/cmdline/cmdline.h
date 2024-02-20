/**
 * cmdline.h
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *  
 * My cmdline parse library
 *
 * Date: 21/10/2023
 */

#ifndef _CMDLINE_H_
#define _CMDLINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CMDTYPE_INT    0
#define CMDTYPE_STR    1
#define CMDTYPE_NULL   3

#define CMDDATA_NODATA   0
#define CMDDATA_REQUIRED 1
#define CMDDATA_OPTIONAL 2
#define CMDDATA_NULL     3

/**
 * This structure that represents a command line
 * command
 */
typedef struct STRUCT_CMDLINE
{
  char *pszLong;       /* --help                                           */
  char *pszShort;      /* -h                                               */
  int iRequired;       /* If command require arguments                     */
  int iDataType;       /* integer, string                                  */
  char *pszArgument;   /* file, number, etc                                */
  bool bSet;           /* if the command is setted                         */
  char *pszDefault;    /* Default value of the command                     */
  char *pszData;       /* The variable with receive the argument           */
  long lDataLength;    /* The length of variable with receive the argument */
  char *pszHelp;       /* Help message                                     */
} STRUCT_CMDLINE, *PSTRUCT_CMDLINE;

/**
 * Print the help message for the user
 */
void vShowSyntax(PSTRUCT_CMDLINE astCmdOpt);
void vPrintUsage(const char *pszMsg, PSTRUCT_CMDLINE astCmdOpt);

/**
 * Check if what wass passed on the command line is valid
 */
bool bParseCommandLine(int argc, char **argv, PSTRUCT_CMDLINE astCmdOpt);

/**
 * This function is based in the examples of the book 
 * "Aprenda em 24 horas Programacao para Linux"
 *
 * This function return the name of argv[0] withouth the path,
 * for example, if argv[0] == "/usr/bin/program", the function returns
 * only the string "program".
 */
char *szGetProgramName(const char *szPathName);

#endif /* _CMDLINE_H_ */
