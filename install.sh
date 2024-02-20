#!/bin/bash
# 
# install.sh: Script to install libcmdline.so
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmai.com>
# 
# Date: 19/02/2024

# Checking if user is root
if [[ $EUID -ne 0 ]]; then
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m This script must be run as root\n"
  else
    printf "E: This script must be run as root\n"
  fi

  exit 1
fi

printf "\n#############################\n"
printf "# Installing libcmdline.so #\n"
printf "#############################\n"

gzip -9 ./man/libcmdline.3
#gzip -9 ./doc/*
#gzip -9 ./LICENSE
gzip -9 ./AUTHORS
#gzip -9 ./NEWS
gzip -9 ./README

# Creating the documentation directory
mkdir -pv /usr/share/doc/libcmdline

# Install the library
cp -rvf ./include/cmdline /usr/include
cp -rvf ./lib/libcmdline.so /usr/lib

# Installing the documentation
cp -rvf ./man/libcmdline.3.gz /usr/share/man/man3
cp -rvf ./doc/* /usr/share/doc/libcmdline
#cp -rvf ./LICENSE.gz /usr/share/doc/libcmdline
cp -rvf ./AUTHORS.gz /usr/share/doc/libcmdline
# cp -rvf ./NEWS.gz /usr/share/doc/libcmdline
cp -rvf ./README.gz /usr/share/doc/libcmdline

printf "libcmdline was installed successfuly!\n"

