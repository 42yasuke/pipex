/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chatgpt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:44:03 by jralph            #+#    #+#             */
/*   Updated: 2023/01/17 21:46:06 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();
    if (pid == 0) {
        // Processus fils
        close(pipefd[0]); // Ferme l'extrémité de lecture du pipe
        dup2(pipefd[1], 1); // Redirige la sortie standard vers l'extrémité d'écriture du pipe

        char *ls_args[] = {"ls", NULL};
        execve("/bin/ls", ls_args, NULL);
    } else {
        // Processus père
        close(pipefd[1]); // Ferme l'extrémité d'écriture du pipe
        dup2(pipefd[0], 0); // Redirige l'entrée standard vers l'extrémité de lecture du pipe

        char *wc_args[] = {"wc", "-l", NULL};
        execve("/usr/bin/wc", wc_args, NULL);
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}

/*

Ce code crée un pipe et utilise pipe() pour créer les descripteurs de fichiers pour l'extrémité de lecture et l'extrémité d'écriture du pipe. Il utilise ensuite fork() pour créer un processus fils et un processus père. Le processus fils utilise dup2() pour rediriger la sortie standard vers l'extrémité d'écriture du pipe et exécute la commande ls via execve. Le processus père utilise dup2() pour rediriger l'entrée standard vers l'extrémité de lecture du pipe, exécute la commande wc -l via execve et attend la fin du processus fils avec waitpid(pid, &status, 0);. Les données de sortie de la commande ls sont donc envoyées dans le pipe et utilisées en tant qu'entrée pour la commande wc -l

*/
