# Imagical

## English

Imagical is an image processing software with a Linux command-line interface. Several image processing operations have been implemented: rotation, translation, binarization, grayscale, histogram CSV export, gradient, inversion, saturation, erosion, dilatation, difference and SKIZ. These algorithms have been parallelized using OpenMP.

## Français

### Description

Imagical est un logiciel de traitement d’images avec une interface en ligne de commande fonctionnant sous Linux. Plusieurs types de traitement d’images ont été implémentés: rotation, translation, binarisation, niveaux de gris, export CSV de l’histogramme, gradient, inversion, saturation, érosion, dilatation, différence et SKIZ. Ces algorithmes ont été par la suite parallélisés en utilisant OpenMP.

### Commandes

#### Syntaxe

Le programme est appelé depuis le terminal en lançant le fichier Imagical dans le répertoire Imagical défini à l’installation, avec la commande ```./Imagical```.

Une ligne de commande doit ressembler à :

```./Imagical --traitement1 paramètre1.1 paramètre1.2 --traitement2 entrée.png sortie .png```

Où les arguments sont :

```./Imagical``` Nom du programme à exécuter

```--traitementX``` Nom du Xième traitement à appliquer (voir liste ci-dessous). Il est possible d’appliquer plusieurs traitements à la suite à une même image. L’ordre des traitements a une importance sur le résultat final.

```paramètreX.Y``` Yième paramètre du Xième traitement

```entree.png``` Image à traiter. Si le fichier de sortie n’est pas spécifié, le résultat du/des traitement(s) sera sauvegardé par-dessus et écrasera le fichier. Le fichier d’entrée doit exister et être au format *.png.

```sortie.png``` Argument optionnel. Si spécifié, le résultat du/des traitement(s) sera sauvegardé dans un fichier correspondant au nom spécifié. Si le fichier existe déjà, il sera écrasé, sinon un nouveau fichier sera crée. Les fichiers d’entrée et/ou de sortie doivent toujours être en fin de la ligne de commande.

#### Liste des traitements

- Rotation

```--rotation <degré> entree.png sortie.png```
- Translation

```--translation <décalage à gauche> <décalage en haut>```
- Binarisation

```--binarisation```
- Niveaux de gris

```--gray```
- Export de l’histogramme au format *.csv

```--exportCSV <sortieCSV.csv>```
- Gradient

```--gradient entrée.png sortie.png```
- Filtrage

```--filtrage <filtre>```

```<filtre>``` doit indiquer un fichier filtre. Un échantillon de filtre est fourni dans la dossier filtre situé dans le répertoire Imagical défini à l’installation.
- Inversion

```--inversion```
- Saturation

```--saturation <coefficient>```
- Erosion

```--erosion <coefficient>```
- Dilatation

```--dilatation <coefficient>```
- Difference

```--difference <entree2.png>```
- Skiz

```--skiz```

#### Parallélisation

- Parallélisation

```--parallel <nombre de threads>```

Pour exécuter le programme en séquentiel, omettez la commande ci-dessus ou indiquez 1 comme nombre de thread. Pour exécuter le programme en parallèle, ajoutez cette commande suivi du nombre de threads à n’importe quel endroit de la ligne de commande avant le/les noms de fichiers d’entrée/sortie. Cela va activer l’exécution parallèle pour l’ensemble des traitements d’image indiqués dans la ligne de commande.

- Chrono

```--chrono```

Cette commande va ajouter un compteur de temps en millisecondes pour chaque traitement.

#### Exemples

```./Imagical --inversion --filtre laplacien --dilatation 5 --exportCSV sortieCSV.csv entrée.png```

Le programme inverse l’image entrée.png, lui applique un filtre laplacien, fait une dilatation de coefficient 5. L’image résultat sera sauvegardée en écrasant le fichier initial entrée.png et exporté au format CSV dans un fichier nommé exportCSV.csv

```./Imagical --erosion 2 --gradient --translation 200 350 --difference entrée2.png entrée.png sortie.png```

Le programme effectue une érosion de coefficient 2, puis un gradient, applique une translation de 200 pixels vers la gauche et 350 pixels vers le haut, et fait la différence.

```./Imagical --inversion --chrono --dilatation 5 entrée.png```

Exécute le programme en séquentiel, en effectuant une inversion puis une dilatation de coefficient 5. Le temps pour chacun de ces deux traitements sera indiqué à l’utilisateur.

```./Imagical --parallel 2 --binarisation --skiz entrée.png```

Effectue une binarisation puis un skiz sur l’image entrée.png. Les algorithmes des deux traitements seront exécutés avec deux threads en parallèle.