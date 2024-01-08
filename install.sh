cd ./lib
./install.sh
cd ..

gcc compile.c -o compile 1> /dev/null #2> /dev/null
sudo cp compile /usr/bin/ 1> /dev/null #2> /dev/null

if [ -e" /usr/bin/compile " ]; then
    echo "Compile is now ready"    
else 
    echo "Compilation failed. Do you have all source file?"
fi
