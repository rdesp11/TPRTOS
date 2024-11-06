# Appareil de mesure de CO2

Nous allons créer une application zephyr permettant de récupérer les données de CO2 depuis le capteur **SCD41**.

## Initialization de l’environnement de développement intégrez zephyr 

Vous pouvez suivre [le tutoriel](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) propre à votre Système d'exploitation jusqu'a la section **Get Zephyr and install Python dependencies**.

Pour les utilisateurs **Ubuntu**: 
`sudo apt install python3-venv`

## Initialization du projet

Dans un premier temps, nous allons créer un **espace de travail** (_workspace_) et un **manifest** `west`

```bash
cd ~ # déplacement dans le dossier _home_ de notre utilisateur
mkdir TpRTOS # création d'un dossier nommé
cd TpRTOS # déplacement dans le dossier TpRTOS
python3 -m venv .venv # création d'un environment python cela permet d'installé des dépendances python nécessaire :WARNING: cette command utiliser un chemin relatif, la commande dois donc toujours être executer dans le dossier correspondant 
source ./.venv/bin/activate # activation :WARNING: chemin relatif :point_up: :WARNING: l'activation de l’environnement python virtuel dois se faire A CHAQUE FOIS que vous voulez utiliser une commande west 
echo $VIRTUAL_ENV # permet de voir quel environnement python est utilisé 
pip install west # pip est un gestionnaire de paquet python, ici nous installons le paquet west pour pouvoir utiliser ce logiciel en ligne de commande
git clone https://gitlab.com/fabianlapotrepublic/TP/co2-measurement-device co2-measurement-device # clone en local d'un dépôt de code git distant (localisé https://github.com/zephyrproject-rtos/example-application) dans le dossier _co2-measurement-device_. Attention, ici le mot device ne signifie pas périphérique mais appareille puis que nous créer un manifest west pour générer un système d'exploitation permettant de créer un **appareil de mesure de co2**.
west init -l co2-measurement-device # initialisation du manifest west
west update # récupération des différents dépôt de code source des logiciels utiliser pour le projet CO2-measurement-device
west zephyr-export # export l'installation de Zephyr installation comme configuration CMake
pip install -r ./zephyr/scripts/requirements.txt # activation :WARNING: chemin relatif :point_up: :WARNING:
west build app # construire 
```

Il faut maintenant configuré vscode pour qu'il puisse comprendre la structure du code.

```bash
cd co2-measurement-device
```

Vscode devrais vous demande des configurations pour le compilateur et `co2-measurement-device/cmake`:
* Sélectionné le fichier de configuration CMakeLists.txt dans le dossier `app`
* Sélectionné `gcc` comme compilateur

Aller dans les configuration avec le raccourcie clavier `ctrl+,`, dans la bare de recherche de configuration entré `C_Cpp › Default: Compile Commands` et ajouté comme argument `build/compile_commands.json`

![commande de compilation](assets/image.png)

## Hello world

En informatique, lorsque nous commençons d'une feuille vierge il faut toujours 

## Clignoter la LED1

Actuellement, le code permet de faire tourner la le LED2 du kit de développement. 

* Pouvez-vous faire clignoter la le LED1 ?

Pour cela vous aurez besoin de:
* changé l’arborescence matériel
:info: vous pouvez actuellement voir l'arborescence créer `build/zephyr/zephyr.dts`
:Info: Lors que l'ont touche à des configuration de l’arborescence matériel, if faut reprendre la construction depuis **les condition originel** (_pristine_) de l'application west. `west build app --pristine`
* changé le code source de votre application
:info: la première instructiond de votre code
* construire la nouvelle image
:info: `west build app` permet de construire votre image qui est en suite situer dans `build/zephyr/zephyr.elf`
* flasher la nouvelle image
:info


:Info: afin de déboguer votre logiciel, vous pouvez vous connecté au port série en utilisant un utilitaire qui permet de communiquer avec des périphériques via des interfaces série en l’occurrence il s'agit dans notre cas de de interface UART. Pour ma part, j'utilise l'utilitaire **picocom**. `picocom -b 115200 /dev/ttyACM0`

## Ajout du capteur de CO2

Ajouter l’échantillonnage des valeurs de co2 en utilisant les informations contenue dans ce dépôt de code: https://github.com/nobodyguy/sensirion_zephyr_drivers

## Ajout d'un capteur de particule fine SPS30

A toi de jouer, il faut que tu ajoute le SPS30 pour récupérer les données de particule fine présent dans la pièce. Ce dépôt de code pourra-t-être utile https://github.com/Sensirion/embedded-sps

## Envois des données via le protocole Lorawan

Si tu es arrivé jusqu'ici bravo ! 

introduction de la notion de _subsystem_

Maintenant que tu vois comment fonctionne zephyr, utilise le lorawan pour envoyé les données échantillonnais.
