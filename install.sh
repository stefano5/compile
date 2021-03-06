if [ -f /bin/compile ]; then
    sudo rm /bin/compile
fi

if [ -f /bin/apiSO.c ]; then
    sudo rm /bin/apiSO.c
fi

if [ -f /bin/debug.c ]; then
    sudo rm /bin/debug.c
fi

if [ -f /bin/function.h ]; then
    sudo rm /bin/function.h
fi

if [ -f /bin/management_date.c ]; then
    sudo rm /bin/management_date.c
fi

if [ -f /bin/coloredMessage.c ]; then
    sudo rm /bin/coloredMessage.c
fi

if [ -f /bin/printColor.c ]; then
    sudo rm /bin/printColor.c
fi

if [ -f /bin/timeCount.c ]; then
    sudo rm /bin/timeCount.c
fi

if [ -f /bin/ia.c ]; then
    sudo rm /bin/ia.c
fi

sudo cp -r lib/* /usr/include/
gcc compile.c -o compile 1> /dev/null 2> /dev/null
sudo cp compile /bin/ > /dev/null 2> /dev/null

if [ -f /bin/compile ]; then
    echo "Compile is now ready"    
else 
    echo "Compilation failed. Do you have all source file?"
fi



