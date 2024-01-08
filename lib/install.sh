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
        echo "$path$file linking!"
   	sudo ln -s "$PWD/$file" "$path$file"
    fi
done
