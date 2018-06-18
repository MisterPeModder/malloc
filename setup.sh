#!/bin/bash

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]
then
	echo "Script is not being sourced!"
	echo "try running this script using 'source'"
	exit
fi

echo "Setting up environement..."

KERNEL_NAME=$(uname -s 2> /dev/null)

if [[ $KERNEL_NAME = 'Linux' ]]
then
	if [[ ":$LD_LIBRARY_PATH:" != *$PWD* ]]
	then
		echo "Adding $PWD to ld library path"
		export LD_LIBRARY_PATH="$PWD:$LD_LIBRARY_PATH"
	else
		echo "Already added $PWD to ld library path"
	fi
	if [[ ":$LD_PRELOAD:" != *libft_malloc.so* ]]
	then
		echo "Adding libft_malloc.so to ld preload"
		export LD_PRELOAD="libft_malloc.so:$LD_PRELOAD"
	else
		echo "Already added libft_malloc.so to ld preload"
	fi

elif [[ $KERNEL_NAME = 'Darwin' ]]
then
	if [[ ":$DYLD_LIBRARY_PATH:" != *$PWD* ]]
	then
		echo "Adding $PWD to dyld library path"
		export DYLD_LIBRARY_PATH="$PWD:$DYLD_LIBRARY_PATH"
	else
		echo "Already added $PWD to dyld library path"
	fi
	if [[ ":$DYLD_INSERT_LIBRARIES:" != *libft_malloc.so* ]]
	then
		echo "Adding libft_malloc.so to dyld insert libraries"
		export DYLD_INSERT_LIBRARIES="libft_malloc.so:$DYLD_INSERT_LIBRARIES"
	else
		echo "Already added libft_malloc.so to dyld insert libraries"
	fi
	export DYLD_FORCE_FLAT_NAMESPACE=1
else
	echo "Unsupported kernel"
fi
echo "done"
