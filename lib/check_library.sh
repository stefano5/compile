declare -a test_array

path="/usr/include/"

test_array=(apiSO.c coloredMessage.c debug.c function.h management_date.c management_string.c printColor.c timeCount.c)
success=1

#test 1
for file in ${test_array[@]}
do
    #echo $file
    if [ ! -e "$path$file" ] 
    then 
        echo "$path$file missed!"
        success=0;
    fi
done

#test 2
for file in ${test_array[@]}
do
    if [ ! -s "$path$file" ] 
    then 
        echo "$path$file if exist, is empty!"
        success=0;
    fi
done

#test 3
for file in ${test_array[@]}
do
    if [ ! -f "$path$file" ] 
    then 
        success=0;
        echo "$path$file if exist, it have not permission to read!"
        ls -l $path$file
        echo "try  to use:      sudo chmod ugo+r $path$file"
    fi
done

if [ $success == 1 ]
then
    echo "Ok"    
fi


exit 0

