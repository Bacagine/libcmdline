#!/bin/bash
# 
# uninstall.sh: Script to uninstall libcmdline.so
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
# 
# Date: 19/02/2024

# Checking if user is root
if [[ $EUID -ne 0 ]]; then
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m This script must be run as root\n"
  fi
  
  print "E: This script must be run as root\n"

  exit 1
fi

if test -f /usr/lib/libcmdline.so; then
  printf "###############################\n"
  printf "# Uninstalling libcmdline.so #\n"
  printf "###############################\n"

  # Creating the documentation directory
  rm -rv /usr/share/doc/libcmdline

  # Install the binary of software and yout autocomplete script
  rm -rvf /usr/include/cmdline
  rm -rvf /usr/lib/libcmdline.so

  # Installing the documentation
  rm -rvf /usr/share/man/man3/libcmdline.3.gz

  printf "\nlibcmdline.so was uninstalled successfuly!\n"
else
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m libcmdline.so is not installed!\n"
  else
    printf "E: libcmdline.so is not installed!\n"
  fi

  printf "Nothing to do\n"

  exit 1
fi

