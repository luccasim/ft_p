## ft_p

# Introduction

Ce projet consiste à implémenter un client et un serveur permettant le transfert de fichier en réseau TCP/IP  

# Conception 
Le serveur attend une connexion avec un client. C'est un serveur qui fork lorsque la connexion réussit. Toute suite de commande envoyé au serveur sera executé (stoké dans un fichier .tmp) et renvoyé sous chaine de caractère au client.  
Du coté client, on peut ce connecter au serveur avec la commande "netcat" avec des droits basic, ou via notre client avec des droits.   

# Problématiques
Un protocol de communication client/serveur, afin de s'assuré si le retour d'une request dois s'affiché sur stdin/stdrr. Un envoi de donnée afin d'identifié un client etc...

# Bonus
+ Mode debug sur le serveur  
+ lcd, lls, lpwd  
+ Changement des droits d'accès  
+ (Gestion et changement) d'un prompt  
+ Autres commandes : "shutdown, name, cmd, mkdir, rmdir"  

# Sources
http://broux.developpez.com/articles/c/sockets/  
