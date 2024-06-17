# Raymarcher

## Description

Ce projet implémente un raymarcher, une technique de rendu qui utilise les champs de distance signés (SDF). Le raymarcher rend des objets 3D en calculant la distance minimale à la surface des objets à chaque point dans l'espace.

## Fonctionnalités

- **Objets** : Prend en charge le rendu des sphères, des plans, des cubes et d'un "nice cube" personnalisé (une combinaison d'un cube et d'une sphère).
- **Raymarching** : Algorithme principal pour le rendu des scènes avec plusieurs objets.
- **Ombres et Réflexions** : Support de base pour les ombres et les réflexions afin d'améliorer le réalisme.
- **Sortie d'image** : Rend la scène dans un fichier image au format PPM.

## Structure du Code

### Principales Classes et Fonctions

#### `Objet`
Une classe de base abstraite pour les objets 3D. Elle définit l'interface pour calculer la SDF, la couleur et les propriétés de réflexion des objets.

#### `Sphere`, `Plan`, `Cube`, `Nice_cube`, `Triangle`
Implémentations concrètes de la classe `Objet`. Chaque classe définit son propre calcul SDF, couleur et propriétés de réflexion.

#### Fonctions de Combinaison SDF
Fonctions pour combiner les SDF pour des formes complexes :
- `intersectSDF`
- `unionSDF`
- `differenceSDF`

#### `raymarch`
La fonction principale qui effectue le raymarching pour trouver les intersections avec les objets dans la scène.

#### `calculate_color`
Calcule la couleur à un point dans la scène, en prenant en compte les ombres et les réflexions.

### Fonction Principale

La fonction `main` configure la scène, effectue le raymarching pour chaque pixel, et sauvegarde l'image rendue.

### Auteur
Abdoulaye Baldé
