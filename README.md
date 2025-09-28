<div style="text-align:center;">
    <img src="./Other/Logo.svg" alt="F&nµx">
</div>

<div style="text-align:center;">
<h1>ATypik</h1>
</div>

## Présentation

### Qu'est-ce que c'est ?

ATypik est une librairie définissant de nouveaux types ou uniformisant ceux déjà existants.
L'utilisation est simplifiée et une documentation Doxygen est présente dans le code (également compilable).

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
  * Algorithme de Stein (uniquement PGCD)
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

Également, les tests nécessitent une installation de GMP pour vérifier les résultats des modules Int et Math.
Donc, si vous souhaitez exécuter ces tests, il vous faudra avoir les headers et les libs de GMP dans un chemin 
que le compilateur reconnait nativement.

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
Si les tests réussissent, vous n'aurez que des OK qui s'afficheront. Également, un benchmark sera présent pour le module Int.
Ce dernier affichera des temps d'exécution en fonction de la taille des entiers générés.

Si l'affichage est différent, alors les tests ont échoué et je vous déconseille d'utiliser ATypik.
Vous pourrez donc déclarer le problème via les "issues" de Github.

## Documentation

Si vous lancez la commande `make dox` suivie de `installdox`, la doc sera compilée via Doxygen et Latex puis sera
installée.

## Politique IA

Pour le Module Int, étant donné que mes connaissances en mathématiques sont limitées à la Terminale S, il m'a fallu 
avoir recours à l'utilisation de l'IA pour m'aider dans certains algorithmes. Les algorithmes concernés ont un 
commentaire estampillé "OPTIMISATION IA" à côté de l'accolade fermante de la fonction concernée.

Bien sûr, ces rajouts/optimisations n'ont pas été faits sans vérification avant. J'ai vérifié que chaque algo donné 
par l'IA est correct, ne possède pas de faille apparente et ai ensuite optimisé au plus possible pour garantir une 
complexité en temps relativement correcte. Après tout, je suis pas douée en Maths mais en Algorithmique un peu quand 
même mdr :)

