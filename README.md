# Stage2A

*Analyse exploratoire des données spatialisées en utilisant des processus ponctuels*

## Auteur
 - DUGUE Clément

## Dépendances
 - gcc
 - g++
 - R
<br/>

## Dossier calculFGJK

Ce dossier contient la partie de calcul de fonction uniquement

#### Build
 - `cd ./calculFGJK`
 - `make main`

#### Execute
 - mettre un fichier avec la liste des points dans le dossier "POINTS"
 - changer les paramètres au besoin dans le dossier "PARAMS"
 - au choix:
	- `./calcul`
	- `./visualisation.sh` - si vous voulez afficher les courbes également
<br/>


## Dossier codeComplet

Ce dossier contient le code permettant de faire la génération des tests d'enveloppe.

#### Build
Pour génération de type "STRAUSS":
 - `cd ./codeComplet/STRAUSS`
 - `make`

Pour génération de type "AREAINT":
 - `cd ./codeComplet/AREAINT`
 - `make`

#### Execute
 - changer les paramètres au besoin dans le dossier "PARAMS"
 - aller dans le dossier "EXEC"

Pour génération de type "STRAUSS":
 - au choix:
	 - `./sim_cftp.exe ../PARAMS/nom_param.txt`
	 - `./enveloppes_sim_cftp.sh ../PARAMS/nom_param.txt`

Pour génération de type "AREAINT":
 - au choix:
	 - `./sim\_areaint.exe ../PARAMS/nom\_param.txt`
	 - `./enveloppes_sim_areaint.sh ../PARAMS/nom_param.txt`

Les 2 scripts permettent d'avoir une visualisation juste après les calculs.

<br/>

## Dossier intensite

Ce dossier contient le code pour les calculs d'intensité.

#### Build
 - `cd ./codeIntensite`
 - `make `


#### Execute
 - mettre un fichier avec la liste des points dans le dossier "POINTS"
 - changer les paramètres au besoin dans le dossier "PARAMS"
 - au choix:
	- `./intensite`
	- `./visualisation.sh` - si vous voulez afficher les courbes également

