#!/bin/bash

###########################################
## Use this script to align your cells on #
## Calc, Exel ou any other table program. #
###########################################


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

	if [[ ! "$4" =~ ^-?[0-9]+$  ]] ; then

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


function main(){

	echo -n -e "\n\nComeçando a processar o texto passado...\n"

	main_string=$(cat "$1");		#Original file copy string...
	treat_string="$main_string";	#String to be treated and after applied to the main String;

	echo -n -e "$main_string\n" >'.BASH_TEMP_FILE.txt'
	last_lines=$(echo "$(wc -l <""$1"")-$(wc -l <.BASH_TEMP_FILE.txt)"|bc);
	rm '.BASH_TEMP_FILE.txt'

#To print a specific line use: sed -n "$var"p "file_name" ou sed -n "$var1","$var2"p "file_name" para imprimir as linhas de "$var1" a "$var2"
	
#	last_lines=$(wc -l "$1"|cut -d' ' -f1);					#Original number of bytes on the file...
#	last_lines=$(echo "$last_lines-${#main_string}-1"|bc);	#Diference found is the last lines missing! (-1 for some reason I don't know...)

	if [ "$2" == '-AP' ] ; then

		if [ "$3" == '-L' ] ; then

			if [ "$4" -gt '0' ] ; then

				for (( i=1; i < $5; i++)) ; do	#Makes all the iterations, except one (the initial is equal...);

					echo -n -e ".";

					for (( j=0; j < ${#treat_string}; j++)) ; do

						if [[ "${treat_string:$j:1}" =~ ^[0-9]+$ ]] ; then

							k=$j;

							while [[ "${treat_string:$k:1}" =~ ^[0-9]+$ ]] ; do k=$(echo "$k+1"|bc); done	#Counts how many chars composes the number sinse index $j...

							l=$(echo "$k-$j"|bc);	#length (l) of the analised number!

							number="${treat_string:$j:$l}";	#Gets the number like a substring...
							number=$(echo "$number+$4"|bc);	#Applies the AP in that number...

							treat_string="${treat_string:0:$j}""$number""${treat_string:$k}";	#Puts it back in the same relative place (it may change the total length...)

							j=$(echo "$j+${#number}"|bc);	#To avoid "re-analizing" the same number, j jump to its final position+1;

							unset k; unset l; unset number;
						fi
					done

					for (( j=0; j < $last_lines; j++)) ; do main_string="$main_string\n##ju5t_4_1in3##"; done	#This treatment is just to put an id on where there will be just an empty line at the final of the program!
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

	{ echo -n -e "$main_string"; } >"${1%.txt}_pos-processed.txt"
	sed -i 's/^##ju5t_4_1in3##//g' "${1%.txt}_pos-processed.txt"
	
	unset main_string; unset treat_string; unset last_lines;

	echo -n -e "\nEncerrando script normalmente. Trabalho concluído!\n\n"

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
