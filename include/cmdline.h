/**
 * cmdline.h
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Description: Module to parse command line
 * 
 * Date: 18/10/2024
 */

#ifndef _CMDLINE_H_
#define _CMDLINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libgen.h>

typedef enum ENUM_CMDDATA {
  CMDDATA_NODATA,
  CMDDATA_REQUIRED,
  CMDDATA_OPTIONAL,
  CMDDATA_NULL
} ENUM_CMDDATA, *PENUM_CMDDATA;

typedef enum ENUM_CMDTYPE {
  CMDTYPE_BOOL,
  CMDTYPE_CHAR,
  CMDTYPE_INT,
  CMDTYPE_FLOAT,
  CMDTYPE_DOUBLE,
  CMDTYPE_STRING,
  CMDTYPE_NULL
} ENUM_CMDTYPE, *PENUM_CMDTYPE;

typedef struct STRUCT_CMDLINE {
  char *pszLong;
  char chShort;
  int iRequired;
  int iCmdDataType;
  char *pszExampleArg;
  bool bSet;
  void *pDefaultArg;
  void *pData;
  int iDataSize;
  char *pszHelp;
} STRUCT_CMDLINE, *PSTRUCT_CMDLINE;

extern const char *gkpszArgv0;
extern const char *gkpszProgramName;

/**
 * @brief Set the name of program
 * 
 * @param kpszArgv0 receive the argv[0]
 */
void vSetProgramName(char *kpszArgv0);

/**
 * @brief Get the name of the program
 * 
 * @return Return the name of the program
 */
const char *kpszGetProgramName(void);

/**
 * @brief Show command line help message
 * 
 * @param astCmdOpt command line options array
 */
void vShowHelp(PSTRUCT_CMDLINE astCmdOpt);

/**
 * @brief Parse command line and save the values in astCmdOpt
 * 
 * @param argc main argument counter
 * @param argv main argument vector
 * @param astCmdOpt command line options array
 * 
 * @return true or false
 */
bool bParseCommandLine(int argc, char **argv, PSTRUCT_CMDLINE astCmdOpt);

#ifdef __cplusplus
}
#endif

#endif
