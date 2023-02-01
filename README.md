# pipex
pipex - Utilisation de la redirection de pipes pour exécuter des commandes en chaîne
Ce projet consiste à écrire un programme en C qui permet d'exécuter des commandes en chaîne en utilisant la redirection de pipes.

# Fonctionnalités
Exécution de plusieurs commandes en chaîne à l'aide de la redirection de pipes.
Prise en charge de l'exécution de commandes internes telles que ls et echo, ainsi que d'outils externes tels que grep et cat.
# Compilation
Pour compiler le projet, utilisez la commande make dans le répertoire racine. Cela générera un exécutable nommé pipex.

# Exécution
Pour exécuter le programme, utilisez la commande ./pipex [commande1] [commande2] ... . Les commandes doivent être séparées par des pipes | pour indiquer la redirection de sortie de la commande précédente vers la commande suivante.
