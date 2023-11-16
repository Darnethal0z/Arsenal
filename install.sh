#!/bin/bash


if [ "$1" == "build" ]; then

	# If you want to remove some features on the final library before compilation, 
	# you can modify the variables below according of what you want to disable.

	ARSENAL_ENABLE_DISPLAY_FEATURES=true
	ARSENAL_ENABLE_STRING_FEATURES=true
	ARSENAL_ENABLE_USER_INPUT_FEATURES=true
	ARSENAL_ENABLE_NETWORK_FEATURES=true
	ARSENAL_ENABLE_RANDOM_FEATURES=true

	# ===========================

	if [ ! -d build ]; then

		mkdir build # 2> /dev/null

	fi

	[[ $ARSENAL_ENABLE_DISPLAY_FEATURES == true ]] && gcc -fPIC -Wall -Ofast -c arsenal/display.c -o build/display.o
	[[ $ARSENAL_ENABLE_STRING_FEATURES == true ]] && gcc -fPIC -Wall -Ofast -c arsenal/network.c -o build/network.o
	[[ $ARSENAL_ENABLE_USER_INPUT_FEATURES == true ]] && gcc -fPIC -faggressive-loop-optimizations -Wall -Ofast -c arsenal/user_input.c -o build/user_input.o
	[[ $ARSENAL_ENABLE_NETWORK_FEATURES == true ]] && gcc -fPIC -faggressive-loop-optimizations -Wall -Ofast -c arsenal/random.c -o build/random.o
	[[ $ARSENAL_ENABLE_RANDOM_FEATURES == true ]] && gcc -fPIC -faggressive-loop-optimizations -Wall -Ofast -c arsenal/string.c -o build/string.o

	gcc -shared build/*.o -o build/libarsenal.so

	rm -f build/*.o
 
elif [ "$1" == "install" ]; then

	if [ `id -u` -ne 0 ]; then

		echo "ERROR : The installation must be run as root"
		exit

	fi

	cp build/libarsenal.so /usr/lib/libarsenal.so
	chmod 0755 /usr/lib/libarsenal.so

	ldconfig

	cp arsenal/arsenal.h /usr/include/

fi