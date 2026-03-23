#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: ./compile.sh <main_file.c> [autres_fichiers.c ...] [lieux_librairies ...]"
    exit 1
fi

# Nom de l'exécutable sans l'extension .c
output_name="${1%.c}"

# Compilation avec tous les arguments ("$@")
gcc "$@" -o "$output_name" -Wall -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11