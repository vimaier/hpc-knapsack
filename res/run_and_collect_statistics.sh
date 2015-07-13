#!/bin/bash

# Activate environment variables for intel compiler
 source /opt/intel/composerxe/bin/compilervars.sh intel64

# if numberOfArguments == 1
if [ "$#" == 1 ]; then
# The first parameter ($1) should be the path to the build dir
  cd $1
fi

# Create statistics dir if it does not exist yet
if [ ! -d statistics ]; then
  mkdir statistics
fi


NREXECUTIONS=10
echo $NREXECUTIONS

function execute_filename {
  # First parameter ($1) should be the file name without extionsion
  echo "Executing for  file $1"
  ./knapsackStarter $NREXECUTIONS "res/$1.txt"
  # Create subdir in statistics if it does not exist yet
  if [ ! -d statistics/$1 ]; then
    mkdir statistics/$1
  fi
  # Move created statistics files
  mv statistics_* statistics/$1
}

execute_filename firstFileExample
execute_filename secondFileExample
execute_filename thirdFileExample
execute_filename fourthFileExample
execute_filename fifthFileExample
