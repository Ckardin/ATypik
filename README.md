<div style="text-align:center;">
    <img src="./Other/Logo.svg" alt="F&nµx">
</div>

<div style="text-align:center;">
<h1>ATypik</h1>
</div>

## Présentation

### Qu'est-ce que c'est ?

ATypik est une librairie définissant de nouveaux types ou uniformisant ceux déjà existants.
L'utilisation est simplifiée et une documentation Doxygen est présente dans le code (également compilée).

### Modules

Les modules contenus dans libATypik sont les suivants :

* Defines
  * Définit le type TriBool et uniformise les types de base à longueur fixe
* Tabs
  * Définit les tableaux à taille fixe, variable et sous forme de map
* Utils
  * Fonctions utiles générales
* StrUtils
  * Fonctions utiles liées aux chaines de caractères
* Int
  * Définit et permet la manipulation de grands entiers signés
* AlgoMath
  * Exponentiation rapide (classique + modulaire)
  * Algorithme d'Euclide étendu
  * Tests de primalité (Miller-Rabin, Fermat2 & Solovay-Strassen)
  * Nombres complexes

## Compatibilité

La librairie ATypik est multi-système (comme tous les outils Ashes), à condition de posséder un compilateur "GCC like" (Exemple : MinGW).

## Licence

La librairie ATypik est sous licence GPL V3 ou ultérieure. Celle-ci est appliquée à chaque fichier et peut être consultée via le document COPYING.

## Comment l'installer ?

### Dépendances

Une seule dépendance est nécessaire pour compiler libATypik :

* AScripts

Celle-ci peut être clonée et installée via mon github. <br />

Néanmoins, pour pouvoir compiler la doc, vous aurez besoin de `doxygen` et d'une distrib `latex` (comme TexLive ou MikTex).

### Installation

Vous pouvez tout simplement lancer les commandes suivantes :

    ./WindowsPrepare.ps1

OU

    ./LinuxPrepare.sh

OU

    ./LinuxPrepare.zsh

puis

    make

et enfin

    make install

À noter que le dossier d'installation est défini par la variable d'environnement ASHES_DIR (créée lors de l'installation d'AScripts).

## Tests

Si vous lancez la commande `make tests`, la compilation de ceux-ci se fera et ils s'exécuteront dans la foulée.
Si les tests réussissent, vous n'aurez que des OK qui s'afficheront.

Si l'affichage est différent, alors les tests ont échoué et je vous déconseille d'utiliser ATypik.
Vous pourrez donc déclarer le problème via les "issues" de Github.
