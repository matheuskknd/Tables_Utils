#!/bin/bash

###########################################
## Use this script to align your cells on #
## Calc, Exel or other compatible program #
###########################################

#These tables have a limit of 1.048.576 lines for both;
#And a limit of AMJ columns to Calc;
#And a limit of XFD columns to Exel;

aux=$(pwd);
cd "${0%./*}"

#Global variables:
	MAIN_pwd=$(pwd);	#Already well-defined!

cd "$aux"
unset aux;

function usage(){

{
	echo -e "\nBad parameter usage, please use this program like follows:\n\n"

	echo "$1 <txt_file_name> <Table_Program> <[keep|clean]> < [-G or -A] [-L or -C] <step_number> <Nb_Iterations> , any number of times>"

	echo -e "\n<txt_file_name>: is the file with the text wich can be readed by the other program, like Calc, Exel, etc. Elements must be separeted horizontally with tabulation(s) and vertically with line(s)"
	echo "<Table_Program>: is the table program you are using to render the table."
	echo "<[keep|clean]>: write 'keep' to print the rules after all the processing is done, or 'clean' otherwise."
	echo "[-G or -A]: write '-G' to use Geometric Progression ou use '-A' to set a Arithmetic Progression."
	echo "[-L or -C]: writet '-L' to progress in lines or '-C' to progress in columns."
	echo "<step_number>: is the number that is mainly used in the progression. So it can't be zero."
	echo "<Nb_Iterations>: is the number os iterations that will be applied to the specified text file."
	
	echo -n -e "\n\nOr just use the following command to give help:\n$1 help\n\n"

} >&2

exit 2;}


function userHelp(){

	echo -n -e "\nHello, thank you for using it! I hope it makes your life easier!"

	echo -n -e "\n\nUse this program to adjust the alignment of formulas in tables, such"
	echo -n -e " the used in Calc, Exel or any other program that works with the same cell format."

	echo -n -e "\n\nYou can use this program to make the step in the cells grow like an AP or a GP, diferent"
	echo -n -e " from the table programs, in wich you have only the option to grow like an AP with r=1."
	echo -n -e "\nIt may causes problems to you, like it did to me... So I made this program, really hope it helps you!"

	echo -n -e "\n\nThat's important for you to realise that it's going only to work if the original text if separeted horizontally by"
	echo -n -e " tabulations and vertically with \_n(new line), check even for absolute references, they won't changed!"

	echo -n -e "\n\nFollow the Usage to know how it works! Just write $0 <anything_else> to see it.\n\n"

exit 0;}


function param_checker(){

	local aux; local i=0;

	for aux in "$@" ; do

		if (( $i == 0 )) ; then

			if [ ! -e "$aux" ] ; then echo -e "\nThe file '$aux' does not exist, closing program...\n" >&2; exit 2; fi

		elif (( $i == 1 )) ; then

			if [ "$aux" != 'Calc' ] && [ "$aux" != 'Excel' ] ; then echo -e "\nAttention: '$aux' is an unkown program in this application. For now, it just guaranteed the compatibility with Calc and Excel!" >&2; usage "$0"; fi

		elif (( $i == 2 )) ; then

			if [ "$aux" != 'keep' ] && [ "$aux" != 'clean' ] ; then usage "$0"; fi

		elif (( ($i-3)%4 == 0 )) ; then

			if [ "$aux" != '-A' ] && [ "$aux" != '-G' ] ; then usage "$0"; fi

		elif (( ($i-3)%4 == 1 )) ; then

			if [ "$aux" != '-L' ] && [ "$aux" != '-C' ] ; then usage "$0"; fi

		elif (( ($i-3)%4 == 2 )) ; then

			if [[ ! "$aux" =~ ^-?[0-9]{1,7}$ ]] ; then

				echo -e "\nAttention: '$aux' is not a valid number!" >&2;
				usage "$0";
			fi

		else

			if [[ ! "$aux" =~ ^[0-9]+$  ]] ; then

				echo -e "\nAttention: '$aux' is not a valid number!" >&2;
				usage "$0";
			fi

			if (( "$aux" < 1 )) ; then

				echo -e "\nAttention: '$aux' must be 1 or greater!" >&2;
				usage "$0";
			fi
		fi

		i=$(($i+1));
	done

return 0;}


function main(){

	echo -n -e "\nStarting the script...\n"

####################################################
################### Compiling ######################
####################################################
	local aux;

	if [ ! -e "$MAIN_pwd/Makefile" ] ; then

		echo -e "\nMakefile not found, execute this script together that file."
		exit 1;
	else
		if [ ! -d "$MAIN_pwd/src" ] ; then

			echo -e "\nSource code (src/) not found, execute together that directory."
			exit 1;
		else

			aux=$( { make >'/dev/null'; } 2>&1; );

			if [ "$?" != 0 ] ; then

				echo -e "\n\nAn error ocurred during the program's compilation:\n\n$aux"
				make clean >'/dev/null' 2>&1
				exit 1;
			fi
		fi
	fi

	echo -e "\nCompilation well succeed!"
########################################################
################### Starting program ###################
########################################################

	echo -n -e "Starting to process the text...\n"

	"$MAIN_pwd/bin/./Table_Utils.run" "$@"

	echo -n -e "\nClosing Script normally. Job is finished!\n\n"

exit 0;}


if [ "$#" == '1' ] && ( [ "$1" == "help" ] || [ "$1" == "--help" ] || [ "$1" == "-h" ] ) ; then

	userHelp;

elif (( ($# - 3)%4 == 0 )) ; then

	param_checker "$@";
	main "$@";

else

	usage "$0";
fi
