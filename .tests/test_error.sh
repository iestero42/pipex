# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_error.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 16:25:58 by iestero-          #+#    #+#              #
#    Updated: 2023/08/12 16:40:29 by iestero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

YELLOW_BACK="\e[43m"
BLUE_FONT="\e[1;34m"
GREEN_FONT="\e[0;32m"
WHITE_FONT="\e[1;37m"
RED_FONT="\e[1;31m"
RESET_COLOR_FONT="\e[39m"
RESET_ALL="\e[0m"

SPACES="  "
FORMAT_TEXT="%-50s"

error_test__function() {
		comand=$1
		$comand 2> error.log
		result=$(cat error.log)
		rm error.log
		printf "${SPACES}${WHITE_FONT}${FORMAT_TEXT}${RESET_ALL}" "TEST: $comand: "
		if [ "$result" = "Error" ] || [ "$result" = "" ]; then
			printf "\t${GREEN_FONT}OK${RESET_ALL}\n"
		else
			printf "${RED_FONT}KO${RESET_ALL}\n"
		fi
	}

echo ""
printf "*********************************************************************************\n"
printf "***************************** ${BLUE_FONT}ERROR_TESTS PUSH_SWAP${RESET_ALL} *****************************\n"
printf "*********************************************************************************\n\n\n"

printf "\n${GREEN_FONT}BAD INPUT\n${RESET_ALL}\n"