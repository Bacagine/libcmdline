/**
 * cmdline.c
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * My cmdline parse library
 *
 * Date: 21/10/2023
 */

#include "cmdline.h"

void vShowSyntax(PSTRUCT_CMDLINE astCmdOpt)
{
  int ii = 0;
 
  for(ii = 0; astCmdOpt[ii].iRequired != CMDDATA_NULL; ii++)
  {
    if(astCmdOpt[ii].iRequired == CMDDATA_NODATA)
    {
      if(astCmdOpt[ii].pszShort == NULL || !strcmp(astCmdOpt[ii].pszShort, ""))
      {
        printf("  --%s\n", astCmdOpt[ii].pszLong);
      }
      else if(astCmdOpt[ii].pszLong == NULL || !strcmp(astCmdOpt[ii].pszLong, ""))
      {
        printf("  -%s\n", astCmdOpt[ii].pszShort);
      }
      else
      {
        printf("  --%s, -%s\n", astCmdOpt[ii].pszLong, astCmdOpt[ii].pszShort);
      }
    }
    else
    {
      if(astCmdOpt[ii].pszShort == NULL || !strcmp(astCmdOpt[ii].pszShort, ""))
      {
        printf("  --%s=%s\n", astCmdOpt[ii].pszLong, astCmdOpt[ii].pszArgument);
      }
      else if(astCmdOpt[ii].pszLong == NULL || !strcmp(astCmdOpt[ii].pszLong, ""))
      {
        printf("  -%s%s\n", astCmdOpt[ii].pszShort, astCmdOpt[ii].pszArgument);
      }
      else
      {
        printf("  --%s=%s, -%s%s\n", astCmdOpt[ii].pszLong, astCmdOpt[ii].pszArgument,
                                     astCmdOpt[ii].pszShort, astCmdOpt[ii].pszArgument);
      }
    }
    printf("    %s\n\n", astCmdOpt[ii].pszHelp);
  }
}

void vPrintUsage(const char *pszMsg, PSTRUCT_CMDLINE astCmdOpt)
{
  printf("%s\n", pszMsg);
  vShowSyntax(astCmdOpt);
}

bool bParseCommandLine(int argc, char **argv, PSTRUCT_CMDLINE astCmdOpt)
{
  int ii = 0;
  int jj = 0;
  char *pszArgument = NULL;
  char *pszParameter = NULL;
  bool bLongCmd = false;
  bool bShortCmd = false;

  for(ii = 1; ii < argc; ii++)
  {
    pszArgument = strtok(argv[ii], "=");

    if(argv[ii][0] == '-' && argv[ii][1] == '-')
    {
      bLongCmd = true;

      pszParameter = strtok(NULL, "=");

      strcpy(pszArgument, &pszArgument[2]);
    }
    else if(argv[ii][0] == '-')
    {
      bShortCmd = true;
      pszParameter = (char *) malloc(sizeof(char) * strlen(pszArgument)-1);
      strcpy(pszParameter, &pszArgument[2]);

      snprintf(pszArgument, strlen(pszArgument), "%c", pszArgument[1]);
    }
    else
    {
      return false;
    }

    for(jj = 0; astCmdOpt[jj].iRequired != CMDDATA_NULL; jj++)
    {
      if(bLongCmd)
      {
        if(!strcmp(pszArgument, astCmdOpt[jj].pszLong))
        {
          astCmdOpt[jj].bSet = true;

          if(astCmdOpt[jj].iRequired == CMDDATA_REQUIRED)
          {
            if(pszParameter == NULL) return false;

            snprintf(astCmdOpt[jj].pszData, astCmdOpt[jj].lDataLength, "%s", pszParameter);
          }

          if(astCmdOpt[jj].iRequired == CMDDATA_OPTIONAL)
          {
            if(pszParameter == NULL)
            {
              bLongCmd = false;

              continue;
            }
            snprintf(astCmdOpt[jj].pszData, astCmdOpt[jj].lDataLength, "%s", pszParameter);
          }
        }
      } // bLongCmd
      else if(bShortCmd)
      {
        if(!strcmp(pszArgument, astCmdOpt[jj].pszShort))
        {
          astCmdOpt[jj].bSet = true;

          if(astCmdOpt[jj].iRequired == CMDDATA_NODATA)
          {
            bShortCmd = false;

            free(pszParameter);
            pszParameter = NULL;

            continue;
          }
          if(astCmdOpt[jj].iRequired == CMDDATA_REQUIRED)
          {
            if(pszParameter[0] == 0)
            {
              bShortCmd = false;

              free(pszParameter);
              pszParameter = NULL;

              return false;
            }
            snprintf(astCmdOpt[jj].pszData, astCmdOpt[jj].lDataLength, "%s", pszParameter);
          }

          if(astCmdOpt[jj].iRequired == CMDDATA_OPTIONAL)
          {
            if(pszParameter[0] == 0)
            {
              bShortCmd = false;

              free(pszParameter);
              pszParameter = NULL;

              continue;
            }

            snprintf(astCmdOpt[jj].pszData, astCmdOpt[jj].lDataLength, "%s", pszParameter);
          }
        }
      } // bShortCmd
      else
      {
        bLongCmd = false;
        bShortCmd = false;

        return false;
      }
    } // for

    if(bShortCmd)
    {
      free(pszParameter);
      pszParameter = NULL;

      bShortCmd = false;
    }

    if(bLongCmd)
    {
      bLongCmd = false;
    }
  } // for

  return true;
}

char *szGetProgramName(const char *szPathName)
{
  char *pszProgramName = 0;
#ifdef LINUX
  if((pszProgramName = strrchr(szPathName, '/')) != 0)
  {
    ++pszProgramName; /* Skip '/' */
  }
#else
  if((pszProgramName = strrchr(szPathName, '\\')) != 0)
  {
    ++pszProgramName; /* Skip '\' */
  }
#endif /* LINUX */
  else
  {
    pszProgramName = (char *) szPathName; /* Nenhum dir. component */
  }

  return pszProgramName;
}
