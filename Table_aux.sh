#!/bin/bash

###########################################
## Use this script to align your cells on #
## Calc, Exel ou any other table program. #
###########################################


function usage(){

{
	echo -e "\nBad parameter usage, please use this program like follows:\n\n"

	echo "$1 <txt_file_name> [-GP or -AP] [-L or -C] <step_number> <Nb_iterations>"

	echo -e "\n<txt_file_name>: is the file with the text wich can be readed by the other program, like Calc, Exel, etc. Elements must be separeted horizontally with tabulation(s) and vertically with line(s)"
	echo "[-GP or -AP]: write '-GP' to use Geometric Progression ou use '-AP' to set a Arithmetic Progression."
	echo "[-L or -L]: writet '-L' to progress in lines or '-C' to progress in columns."
	echo "<step_number>: is the number that is mainly used in the progression. So it can't be zero."
	echo -e "<stopping_number>: is the number that stops the progression. Must be 1 or greater.\n"

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

	unset main_string; unset treat_string;

	main_string="$(cat "$1")";		#Original file copy string...
	treat_string="$main_string";	#String to be treated and after applied to the main String;

	if [ "$2" == '-AP' ] ; then

		if [ "$3" == '-L' ] ; then

			if [ "$4" -gt '0' ] ; then

				for (( i=1; i < $5; i++)) ; do	#Faz tantas iterações quanto requisitadas...

					echo -n -e ". i = $i";

					for (( j=0; j < ${#treat_string}; j++)) ; do

						if [[ "${treat_string:$j:1}" =~ ^[0-9]+$ ]] ; then	#erro de lógica a apartir desse ponto!!!!!!!!!!!###################################################

							k=$j; #echo -n -e "\nj = $j para i = $i" #testeeeeeeeeeeeeeeeeeeeeeeeeeee

							while [[ "${treat_string:$k:1}" =~ ^[0-9]+$ ]] ; do k=$(echo "$k+1"|bc); done

							l=$(echo "$k-$j"|bc);	#length (l) se torna a posição final dessa substring que é um número!

							number=${treat_string:$j:$l};
							number=$(echo "$number+$4"|bc);

							treat_string="${treat_string:0:$j}""$number""${treat_string:$k}";

							unset k; unset l; unset number;
						fi
					done

					main_string="$main_string\n$treat_string";
				done

			#elif [ "$4" -lt '0' ] ; then



			fi

		fi

	fi

	#main_string="$main_string\n$treat_string"	#Forma como será feita a contatenação entre as Strings!

	echo -n -e "$main_string" >FFILLE
	unset main_string; unset treat_string;

	echo -n -e "\nEncerrando script normalmente. Trabalho concluído!\n\n"

exit 0;}


if [ "$#" != '5' ] ; then

	usage "$0";
else

	param_checker "$1" "$2" "$3" "$4" "$5" "$0";

	main "$1" "$2" "$3" "$4" "$5";
fi
