/**
 * cmdline.c
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 * 
 * Description: Module to parse command line
 * 
 * Date: 18/10/2024
 */

#include "cmdline.h"

const char *gkpszArgv0 = NULL;
const char *gkpszProgramName = NULL;

void vSetProgramName(char *kpszArgv0) {
  gkpszArgv0 = kpszArgv0;
  gkpszProgramName = basename(kpszArgv0);
}

const char *kpszGetProgramName(void) {
  return gkpszProgramName;
}

void vShowHelp(PSTRUCT_CMDLINE astCmdOpt) {
  int ii = 0;
  printf("Usage: %s --parameter=<argument>\n", kpszGetProgramName());
  printf("Where parameter will be the following:\n\n");
  for ( ii = 0; astCmdOpt[ii].pszLong; ii++ ) {
    if ( astCmdOpt[ii].iRequired != CMDDATA_NODATA ) {
      printf(
        "  --%s=%s, -%c %s\n", 
        astCmdOpt[ii].pszLong, astCmdOpt[ii].pszExampleArg,
        astCmdOpt[ii].chShort, astCmdOpt[ii].pszExampleArg
      );
    }
    else {
      printf(
        "  --%s, -%c\n", 
        astCmdOpt[ii].pszLong, astCmdOpt[ii].chShort
      );
    }
    printf("    %s\n\n", astCmdOpt[ii].pszHelp);
  }
}

bool bParseCommandLine(int argc, char **argv, PSTRUCT_CMDLINE astCmdOpt) {
  int ii = 0;
  int jj = 0;
  int kk = 0;
  
  if ( gkpszProgramName == NULL ) vSetProgramName(argv[ii]);
  for ( ii = 1; ii < argc; ii++ ) {
    char szCurrentParameter[strlen(argv[ii])];
    char *pszLong = NULL;
    char chShort = '\0';
    char *pszArgument = NULL;
    bool bFound = false;
    
    memset(szCurrentParameter, 0x00, sizeof(szCurrentParameter));
    sprintf(szCurrentParameter, "%s", argv[ii]);
    
    for ( jj = 0; argv[ii][jj] != '\0'; jj++ ) {
      for ( kk = 0; astCmdOpt[kk].pszLong; kk++ ) {
        if ( jj == 0 && argv[ii][jj] == '-' ) {
          jj++;
          if ( jj == 1 && argv[ii][jj] == '-' ) {
            jj++;
            pszLong = strtok(szCurrentParameter, "=");
            if ( pszArgument == NULL ) pszArgument = strtok(NULL, "=");
            pszLong = &pszLong[2];
            if ( strcmp(astCmdOpt[kk].pszLong, pszLong) ) {
              jj = 0;
              continue;
            }
            if ( pszArgument == NULL || pszArgument[0] == 0 ) {
              if ( astCmdOpt[kk].iRequired == CMDDATA_REQUIRED ) {
                if ( astCmdOpt[kk].pDefaultArg == NULL ) return false;
                pszArgument = astCmdOpt[kk].pDefaultArg;
                astCmdOpt[kk].bSet = true;
                bFound = true;
                break;
              }
            }
            astCmdOpt[kk].bSet = true;
            bFound = true;
          }
          else {
            chShort = argv[ii][jj];
            if ( astCmdOpt[kk].chShort != chShort ) {
              jj = 0;
              continue;
            }
            if ( strlen(szCurrentParameter) == 2 ) {
              if ( ii + 1 == argc || argv[ii+1][0] == '-' ) {
                if ( ii + 1 != argc )
                  if ( strlen(argv[ii+1]) == 1 && astCmdOpt[kk+1].pDefaultArg == NULL ) return false;
                if ( astCmdOpt[kk].iRequired == CMDDATA_REQUIRED ) {
                  if ( astCmdOpt[kk].pDefaultArg == NULL || ( ii +1 != argc && strlen(argv[ii+1]) == 1 && argv[ii+1][0] == '-') ) return false;
                  pszArgument = astCmdOpt[kk].pDefaultArg;
                  astCmdOpt[kk].bSet = true;
                  bFound = true;
                  break;
                }
              }
              if ( ii + 1 == argc && astCmdOpt[kk].iRequired == CMDDATA_REQUIRED && astCmdOpt[kk].pDefaultArg == NULL ) return false;
              if ( astCmdOpt[kk].iRequired == CMDDATA_REQUIRED ) {
                ii++;
                sprintf(szCurrentParameter, "%s", argv[ii]);
                pszArgument = szCurrentParameter;
              }
            }
            else {
              pszArgument = &szCurrentParameter[2];
              if ( pszArgument == NULL ) {
                if ( ii + 1 == argc ) {
                  if ( astCmdOpt[kk].iRequired == CMDDATA_REQUIRED ) {
                    if ( astCmdOpt[kk].pDefaultArg == NULL ) return false;
                    pszArgument = astCmdOpt[kk].pDefaultArg;
                    astCmdOpt[kk].bSet = true;
                    bFound = true;
                    break;
                  }
                }
                ii++;
                jj = 0;
                pszArgument = argv[ii];
              }
            }
            astCmdOpt[kk].bSet = true;
            bFound = true;
          }
        }
        if ( bFound ) break;
        return false;
      }
      
      if ( astCmdOpt[kk].bSet ) {
        switch ( astCmdOpt[kk].iCmdDataType ) {
          case CMDTYPE_BOOL: {
            *(bool *) astCmdOpt[kk].pData = atoi(pszArgument);
            break;
          }
          case CMDTYPE_CHAR: {
            *(char *) astCmdOpt[kk].pData = atoi(pszArgument);
            break;
          }
          case CMDTYPE_INT: {
            *(int *) astCmdOpt[kk].pData = atoi(pszArgument);
            break;
          }
          case CMDTYPE_FLOAT: {
            *(float *) astCmdOpt[kk].pData = atof(pszArgument);
            break;
          }
          case CMDTYPE_DOUBLE: {
            *(double *) astCmdOpt[kk].pData = atof(pszArgument);
            break;
          }
          case CMDTYPE_STRING:
          default: {
            snprintf(astCmdOpt[kk].pData, astCmdOpt[kk].iDataSize, "%s", pszArgument);
            break;
          }
        }
      }
    }
  }
  
  return true;
}
