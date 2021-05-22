#!/bin/bash

MINISHELL_DIR="../"
MINISHELL="minishell"

TEST_DIR=`pwd`
INPUT_DIR="${TEST_DIR}/inputs"
OUTPUT_DIR="${TEST_DIR}/outputs"
MINISHELL_PATH="${TEST_DIR}/${MINISHELL_DIR}/${MINISHELL}"

BASH_RESULT="${OUTPUT_DIR}/bash_result.txt"
MINISHELL_RESULT="${OUTPUT_DIR}/minishell_result.txt"

RESET="\033[0m"
GREEN="\033[32m"
RED="\033[31m"

start_test()
{
	for file in `ls ${INPUT_DIR}`; do
		run_tests "${file}"
	done
}

run_tests()
{
	while read -r line; do
		TEST_CMD=`echo "$line"`
		print_usage "${TEST_CMD}"
		exec_cmd "$line"
	done < "${INPUT_DIR}/$1"
}

print_usage(){
	printf "$1\n"
}

exec_cmd()
{
	bash -c "$1"
	#${MINISHELL_PATH} -c "$1" #> ${MINISHELL_RESULT}
}

make -C "${MINISHELL_DIR}"
start_test $@
