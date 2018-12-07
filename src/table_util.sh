#!/bin/bash

###########################################
## Use this script to align your cells on #
## Calc, Exel or other compatible program #
###########################################

#These tables have a limit of 1.048.576 lines for both;
#And a limit of AMJ columns to Calc;
#And a limit of XFD columns to Exel;

#Global variables:
	treat_string=''	#Well-defined on main!

function usage(){

{
	echo -e "\nBad parameter usage, please use this program like follows:\n\n"

	echo "$1 <txt_file_name> [-GP or -AP] [-L or -C] <step_number> <Nb_Iterations>"

	echo -e "\n<txt_file_name>: is the file with the text wich can be readed by the other program, like Calc, Exel, etc. Elements must be separeted horizontally with tabulation(s) and vertically with line(s)"
	echo "[-GP or -AP]: write '-GP' to use Geometric Progression ou use '-AP' to set a Arithmetic Progression."
	echo "[-L or -L]: writet '-L' to progress in lines or '-C' to progress in columns."
	echo "<step_number>: is the number that is mainly used in the progression. So it can't be zero."
	echo -e "<Nb_Iterations>: is the number os iterations that will be applied to the specified text file."
	
	echo -n -e "\n\nOr just use the following command to give help:\n$1 help\n\n"

} >&2

exit 2;}

function param_checker(){

	if [ ! -e "$1" ] ; then

		echo -e "\nThe file '$1' does not exist, closing program...\n" >&2;
		exit 2;
	fi

	if [ "$2" != "-AP" ] && [ "$2" != "-GP" ] ; then usage "$6"; fi

	if [ "$3" != "-L" ] && [ "$3" != "-C" ] ; then usage "$6"; fi

	if [[ ! "$4" =~ ^-?[0-9]{1,7}$  ]] ; then

		echo -e "\nAttention: '$4' is not a valid number!" >&2;
		usage "$6";
	fi

	if [ "$4" == '0' ] ; then

		echo -e "\nAttention: '$4' can't be zero!" >&2;
		usage "$6";
	fi

	if [[ ! "$5" =~ ^[0-9]+$  ]] ; then

		echo -e "\nAttention: '$5' is not a valid number!" >&2;
		usage "$6";
	fi

	if [ "$5" -lt '1' ] ; then

		echo -e "\nAttention: '$5' must be 1 or greater!" >&2;
		usage "$6";
	fi

return 0;}


function is_a_location(){

	if [[ "$1" =~ ^[A-Z]{1,3}[0-9]{1,7}$ ]] ; then return 0; fi

return -1;}


function genTable(){

	local curLine; local line; local count1; local count2; local number; local j; local k; local l;

#To print a specific line use: sed -n "$var"p "file_name" ou sed -n "$var1","$var2"p "file_name" para imprimir as linhas de "$var1" a "$var2"

	for(( line=1, i=0; line <= $2; line++, i++)) ; do

		curLine=$(sed -n "$line"p "$1");

		if [ "$curLine" != '' ] ; then #[@empty_cell&>#

			for(( j=0; j < ${#curLine}; j++)) ; do

				if [[ ${treat_string:$j:1} == [A-Z] ]] ; then

					count1=0;
					count2=0;
					k=$j;

					while [[ ${treat_string:$k:1} == [A-Z] ]] ; do k=$((++k)); done	#Counts how many chars composes the number sinse index $j...

					l=$((k-j));	#length (l) of the analised number!

					number="${treat_string:$j:$l}";	#Gets the number like a substring...
					number=$(echo "$number+$4"|bc);	#Applies the AP in that number...

					treat_string="${treat_string:0:$j}""$number""${treat_string:$k}";	#Puts it back in the same relative place (it may change the total length...)
					j=$((j+${#number}));			#To avoid "re-analizing" the same number, j jump to its final position+1;
				fi

			done
		fi
	done

return 0;}


function main(){

	local main_string; local treat_string; local lastLines;

	echo -e "\nStarting to process the text:\n"

	nbLines=$(cat "$1");
	nbLines=$(echo "$nbLines" | wc -l);

	lastLines=$(wc -l <"$1");
	lastLines=$((lastLines-nbLines));	#Getting the total lines in the file, and the total blank lines at the file's final.

	genTable "$1" "$nbLines" '' "$4";

	main_string=$(cat "$1");		#Original file copy string...
	treat_string="$main_string";	#String to be treated and after applied to the main String;

	if [ "$2" == '-AP' ] ; then

		if [ "$3" == '-L' ] ; then

			if (( $4 > 0 )) ; then

				for (( i=1; i < $5; i++)) ; do	#Makes all the iterations, except one (the initial is equal...);

					echo -n -e ".";

					for (( j=0; j < ${#treat_string}; j++)) ; do

						if [[ "${treat_string:$j:1}" =~ ^[0-9]+$ ]] ; then

							k=$j;

							while [[ "${treat_string:$k:1}" =~ ^[0-9]+$ ]] ; do k=$((++k)); done	#Counts how many chars composes the number sinse index $j...

							l=$((k-j));		#length (l) of the analised number!

							number="${treat_string:$j:$l}";	#Gets the number like a substring...
							number=$((number+$4));			#Applies the AP in that number...

							treat_string="${treat_string:0:$j}""$number""${treat_string:$k}";	#Puts it back in the same relative place (it may change the total length...)

							j=$((j+${#number}));	#To avoid "re-analizing" the same number, j jump to its final position+1;
						fi
					done

					for (( j=0; j < $lastLines; j++)) ; do main_string="$main_string\n#@empty_cell&#"; done	#This treatment is just to put an id on where there will be just an empty line at the final of the program!
					main_string="$main_string\n$treat_string"	#The main String is concatenated with the new transformed inicial string, recursivelly, until all the iterations asked be passed;
				done

			#elif [ "$4" -lt '0' ] ; then

				#Here must enter the code to solve AP in cases that the step were negative!!!!!!!!!!!!

			fi

		#elif [ "$3" == '-C' ] ; then
		
			#Here must be put the same as above, but to work with columns... (hard)
		
		fi

	#elif [ "$2" == '-GP' ] ; then

		#Part to deal the GP case of choice... (hard) 

	fi

	{ echo -n -e "$main_string" | sed 's/^#@empty_cell&#//g';  } >"${1%.txt}_pos_processed.txt"

	echo -e "\nClosing Script normally. Job is finished!\n\n"

exit 0;}


if [ "$#" == '1' ] && ( [ "$1" == "help" ] || [ "$1" == "--help" ] || [ "$1" == "-h" ] ) ; then

	echo -n -e "\nHello, thank you for using it! I hope it makes your life easier!"

	echo -n -e "\n\nUse this program to adjust the alignment of formulas in tables, such"
	echo -n -e " the used in Calc, Exel or any other program that works with the same cell format."

	echo -n -e "\n\nYou can use this program to make the step in the cells grow like an AP or a GP, diferent"
	echo -n -e " from the table programs, in wich you have only the option to grow like an AP with r=1."
	echo -n -e "\nIt may causes problems to you, like it did to me... So I made this program, really hope it helps you!"

	echo -n -e "\n\nThat's important for to you realise that it's better if the original text if separeted horizontally by"
	echo -n -e " tabulations and vertically with \_n(new line), it does not make diference for this program, but it does for your table program!"

	echo -n -e "\n\nFollow the Usage to know how it works! Just write $0 <anything_else> to see it.\n\n"
	exit 0;
	
elif [ "$#" != '5' ] ; then

	usage "$0";
else

	param_checker "$1" "$2" "$3" "$4" "$5" "$0";

	main "$1" "$2" "$3" "$4" "$5";
fi
