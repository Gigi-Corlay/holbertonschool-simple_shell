#!/bin/bash

# Test général du simple shell

echo "Compilation du shell..."
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
if [ $? -ne 0 ]; then
    echo "Échec de la compilation"
    exit 1
fi

echo "Lancement du shell..."
# On lance le shell dans un sous-processus pour tester les entrées
# Ici, on envoie quelques commandes et Ctrl+D
# echo -e permet de simuler les entrées clavier

echo -e "pwd\nenv\nls\nexit" | ./hsh

echo "Test terminé."
