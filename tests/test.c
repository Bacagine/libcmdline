/**
 * main.c
 *
 * Written by Gustavo Bacagine
 *
 * Description: A test to libcmdline
 *
 * Date: 21/10/2023
 */

/******************************************************************************
 *                                                                            *
 *                                 Includes                                   *
 *                                                                            *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "cmdline.h"

/******************************************************************************
 *                                                                            *
 *                             Defines and macros                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Program information defines
 */
#define VERSION        "1.0"
#define DESCRIPTION    "This software is a template"
#define COPYRIGHT      "Copyright (C) 2023"
#define DEVELOPER      "Gustavo Bacagine"
#define DEV_MAIL       "gustavo.bacagine@protonmail.com"
#define CONF_FILE_NAME "./template.conf"
#define LOG_FILE_NAME  "./template.log"
#define GITHUB_URL     "https://www.github.com/Gustavo Bacagine/template"

/**
 * This macro is used to remove
 * unused warnings during the
 * compilation.
 */
#define UNUSED(X) (void) X

#define TRUE  true
#define FALSE false

#ifndef _MAX_PATH
  #define _MAX_PATH 256
#endif

/******************************************************************************
 *                                                                            *
 *                     Global variables and constants                         *
 *                                                                            *
 ******************************************************************************/

/**
 * Receive the name of program
 */
const char *gkpszProgramName = NULL;

/******************************************************************************
 *                                                                            *
 *                           Command Line Options                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Structure that represnts
 * command line arguments
 */
typedef struct STRUCT_COMMAND_LINE
{
  char szTrace        [_MAX_PATH];
  char szDebugLevel   [2];
  char szConfFile     [_MAX_PATH];
  char szPrmDir       [_MAX_PATH];
  char szDbDir        [_MAX_PATH];
  char szIP           [128];
  char szHost         [128];
  char szProxy        [128];
  char szProxyUser    [128];
  char szProxyPassword[ 64];
} STRUCT_COMMAND_LINE, *PSTRUCT_COMMAND_LINE;

STRUCT_COMMAND_LINE gstCmdLine;

/**
 * Long            Short                 Required                   DataType                         Argument
 *  Set             Default               Data                       DataLength
 * Help
 */
STRUCT_CMDLINE astCmdOpt[] = {
/* 00 */
  { "help",        "h",                  CMDDATA_NODATA,             CMDTYPE_NULL,                   "",
     FALSE,         "",                   NULL,                       0,
    "Show this message and exit"
  },
/* 01 */
  { "version",     "v",                  CMDDATA_NODATA,             CMDTYPE_NULL,                   "",
     FALSE,         "",                   NULL,                       0,
    "Show the version and exit."
  },
/* 02 */
  { "trace",       "t",                   CMDDATA_REQUIRED,          CMDTYPE_STR,                    "<file>",
     FALSE,         "/var/log/trace.log",  gstCmdLine.szTrace,        sizeof(gstCmdLine.szTrace),
    "<file> is the path of the debug file"
  },
/* 03 */
  { "debug-level", "d",                   CMDDATA_REQUIRED,           CMDTYPE_INT,                   "<number>",
     FALSE,         "0",                   gstCmdLine.szDebugLevel,    sizeof(gstCmdLine.szDebugLevel),
    "<number> is the level of debug level"
  },
/* 04 */
  { "conf-file",   "c",                   CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<file>",
     FALSE,         "/etc/program.conf",   gstCmdLine.szConfFile,      sizeof(gstCmdLine.szConfFile),
    "<file> is the path of the configuration file (the default is /etc/program.conf)"
  },
/* 05 */
  { "prm-dir",     "p",                   CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<directory>",
     FALSE,         "../prm",              gstCmdLine.szPrmDir,        sizeof(gstCmdLine.szPrmDir),
    "<directory> is the path of the software parameter directory (default is ../prm)"
  },
/* 06 */
  { "db-dir",      "D",                   CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<directory>",
     FALSE,         "../db",               gstCmdLine.szDbDir,         sizeof(gstCmdLine.szDbDir),
    "<directory> is the path of the database directory of the software (default is ../db)"
  },
/* 07 */
  { "ip",          "i",                   CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<ip>",
     FALSE,         "",                    gstCmdLine.szIP,            sizeof(gstCmdLine.szIP),
    "<ip> is the IP of the server",
  },
/* 08 */
  { "host",        "H",                   CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<host>",
     FALSE,         "",                    gstCmdLine.szHost,          sizeof(gstCmdLine.szHost),
    "<host> is the hostname of the server"
  },
/* 09 */
  { "proxy",       "",                    CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<proxy>",
     FALSE,         "",                    gstCmdLine.szProxy,         sizeof(gstCmdLine.szProxy),
    "<proxy> is the proxy"
  },
/* 10 */
  { "proxy-user",  "",                    CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<proxy>",
     FALSE,         "",                    gstCmdLine.szProxy,         sizeof(gstCmdLine.szProxy),
    "<proxy> is the name of the proxy user"
  },
/* 11 */
  { "proxy-password",  "",                CMDDATA_REQUIRED,           CMDTYPE_STR,                   "<proxy>",
     FALSE,         "",                    gstCmdLine.szProxy,         sizeof(gstCmdLine.szProxy),
    "<proxy> is the password of the proxy user"
  },
/* NOTE: NULL indicates the end of the array, NEVER REMOVE IT! */
  { NULL,         NULL,                   CMDDATA_NULL,               CMDTYPE_NULL,                  "",
     FALSE,        "",                     NULL,                       0,
    NULL
  }
};

/******************************************************************************
 *                                                                            *
 *                            Prototype functions                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Print the version of the software
 */
void vPrintVersion(void);

void vPrintVersion(void)
{
  printf("%s %s\n"
         "Build in %s %s\n"
         "%s %s\n"
         "For reporting bugs, send a email to <%s>\n", gkpszProgramName, 
                                                       VERSION,
                                                       __DATE__,
                                                       __TIME__,
                                                       COPYRIGHT,
                                                       DEVELOPER,
                                                       DEV_MAIL
  );
}

/******************************************************************************
 *                                                                            *
 *                                   main                                     *
 *                                                                            *
 ******************************************************************************/
int main(int argc, char **argv)
{
  gkpszProgramName = szGetProgramName(argv[0]);

  if(!bParseCommandLine(argc, argv, astCmdOpt)) 
  {
    char szMsg[256];

    memset(szMsg, 0, sizeof(szMsg));

    snprintf
    (
      szMsg, sizeof(szMsg),
      "Usage: %s --options=<arguments>\nWhere the options and arguments may be receive the following content:\n", argv[0]
    );
    
    vPrintUsage(szMsg, astCmdOpt);
    
    exit(EXIT_FAILURE);
  }
  
  /**
   * Show a help message
   */
  if(astCmdOpt[0].bSet)
  {
    char szMsg[256];

    memset(szMsg, 0, sizeof(szMsg));

    snprintf
    (
      szMsg, sizeof(szMsg),
      "Usage: %s --options=<arguments>\nWhere the options and arguments may be receive the following content:\n", argv[0]
    );
    
    vPrintUsage(szMsg, astCmdOpt);

    return 0;
  }

  /**
   * Show the version of the program
   */
  if(astCmdOpt[1].bSet)
  {
    vPrintVersion();

    return 0;
  }

  /**
   * Show the name of the trace file
   */
  if(astCmdOpt[2].bSet)
  {
    printf("Trace File in astCmdOpt.: [%s]\n", astCmdOpt[2].pszData);
    printf("Trace File in gstCmdLine: [%s]\n", gstCmdLine.szTrace);
  }
  
  /**
   * Show the debug level
   */
  if(astCmdOpt[3].bSet)
  {
    printf("DEBUG LEVEL: [%d]\n", atoi(gstCmdLine.szDebugLevel));
  }
  
  /**
   * Show the name of the configuration file
   */
  if(astCmdOpt[4].bSet)
  {
    printf("CONF FILE: [%s]\n", gstCmdLine.szConfFile);
  }

  /**
   * Show the name of the PRM directory
   */
  if(astCmdOpt[5].bSet)
  {
    printf("PRM DIR: [%s]\n", gstCmdLine.szPrmDir);
  }

  return 0;
}
