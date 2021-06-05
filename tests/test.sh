#!/bin/bash

MINISHELL_DIR="../"
MINISHELL="minishell"

TEST_DIR=`pwd`
TESTS_DIR="${TEST_DIR}/test"
INPUT_DIR="${TEST_DIR}/inputs"
OUTPUT_DIR="${TEST_DIR}/outputs"

BASH_STDOUT="${OUTPUT_DIR}/bash_stdout.txt"
BASH_STDERR="${OUTPUT_DIR}/bash_stderr.txt"
BASH_RESULT=0
MINISHELL_STDOUT="${OUTPUT_DIR}/minishell_stdout.txt"
MINISHELL_STDERR="${OUTPUT_DIR}/minishell_stderr.txt"
MINISHELL_RESULT=0

RESET="\x1b[0m"
RED="\x1b[31m"
GREEN="\x1b[32m"
BLUE="\x1b[34m"
CYAN="\x1b[36m"


start_test()
{
	clean_output
	set_pwd
	for file in `ls ${INPUT_DIR}`;do
		run_tests "${file}"
	done
	clean_output
}

clean_output () {
	rm -f ${BASH_STDOUT} ${BASH_STDERR} ${MINISHELL_STDOUT} ${MINISHELL_STDERR}
	if [ -e "${TESTS_DIR}" ]; then
		chmod -R 777 ${TEST_DIR}
		rm -rf ${TESTS_DIR}
	fi
}

set_pwd()
{
	cd ${TEST_DIR}
	cd ${MINISHELL_DIR}
	MINISHELL_PATH="`pwd`/${MINISHELL}"
	cd ${TEST_DIR}
}

run_tests()
{
	printf "^^^^^^^^^^"$1"^^^^^^^^^^^^\n"
	while read -r line; do
		TEST_CMD=`echo "$line" | cut -d ',' -f 1`
		SETUP_CMD=`echo "$line" | cut -d ',' -f 2- -s`
		print_usage "$TEST_CMD"
		exec_cmd "$TEST_CMD"
		prepare_test
	done < "${INPUT_DIR}/$1"
}

print_usage(){
	printf "%-50s" "$1"
}

set_test_dir () {
	if [ -e "${TESTS_DIR}" ]; then
		chmod -R 777 ${TESTS_DIR}
		rm -rf ${TESTS_DIR}
	fi
	mkdir -p ${TESTS_DIR}
	cd ${TESTS_DIR}
	eval "${SETUP_CMD}"
	cd ${TESTS_DIR}
}

exec_cmd()
{
	set_test_dir
	bash -c "$1" > ${BASH_STDOUT} 2> ${BASH_STDERR}
	BASH_RESULT=$?
	set_test_dir
	${MINISHELL_PATH} -c "$1" > ${MINISHELL_STDOUT} 2> ${MINISHELL_STDERR}
	MINISHELL_RESULT=$?
}

prepare_test()
{
	STDOUT_DIFF=`diff ${MINISHELL_STDOUT} ${BASH_STDOUT}`
	STDERR_DIFF=`diff ${MINISHELL_STDERR} ${BASH_STDERR}`
	if [ -n "${STDOUT_DIFF}" -o -n "${STDERR_DIFF}" -o "${MINISHELL_RESULT}" != "${BASH_RESULT}" ]; then
		printf "${RED}ERROR${RESET}\n"
		printf "${GREEN}STDOUT DIFF: ${STDOUT_DIFF}${RESET}\n"
		printf "${RED}STDERR DIFF: ${STDERR_DIFF}${RESET}\n"
		printf "${CYAN}RESULT: MINISHELL: ${MINISHELL_RESULT} BASH: ${BASH_RESULT}${RESET}\n"
	else
		printf "${GREEN}SUCCESS${RESET}\n"
	fi
}

make -C "${MINISHELL_DIR}"
start_test $@