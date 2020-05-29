for dir in `ls`
do 
	if test -d $dir
	then
		for file in `ls ./$dir/*`
		do
			  ./get_eeg_val $file 
		done
	else
		continue;
	fi
done
