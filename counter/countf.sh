#!/bin/sh
#Holden D. Rose CSC 222 HW2
var=""
var2=""
help="to use this program simply type coutf.sh [dir]. 
	  If no paratater is given then the current directory is used"
for foo in $@ #checks if help was asked for. If not addes argument to var
do
	if [ "$foo" = "-h" ]
		then
			echo $help
			exit 0
		else
			var="$var $foo"	
	fi		
done

if [ "$var" = "" ] #checks to see if var is empty and if yes addes current directoy to it
	then
		var="./"
fi		

count_stuff()
{
	for blah in $(ls $@)
			do
				if [ -f $blah ] #sees if current is a file. If it is increments count if not enters that directory and calls the function on that directory. Once done goes back 1 directory until back to a file
					then
						count=$(($count+1))
					else
						cd $blah
						var2="$(ls)"
						count_stuff $var2
						count=$(($count+1))
						cd ../
				fi		
			done
}
for foobar in $var
	do
		count=0
		cd $foobar
		count_stuff $foobar
		echo "count = $count"	
	done
exit 0