# Exercice1 : Les bases

# Material des personnages
* Localiser le dossier des personnages sous Content/Potato/Characters
* Créer un MaterialInstance appelé "MI_{character}"
** Définir M_Male_Body comme parent
** Observer l'existance d'un paramètre BodyColor dans M_Male_Body
** Assigner une couleur au paramètre BodyColor
* Assigner le MaterialInstance au personnages
** Ouvrir le blueprint d'un personnage BP_{character}
** Sélectionner le Mesh
** Assigner Material -> Element0 avec le MaterialInstance défini
* Exécuter pour tous les personnages

# Mise en place de l'acteur Potato
* Créer une structure FNutritionalInformations
** Anoter par USTRUCT()
** Définir des champs calories, carbs, fat et proteins
** Exposer ces champs à l'editor avec UPROPERTY(EditAnywhere)
* Créer une classe APotato descendante de AActor
** Anoter par UCLASS
** Définir champ weight et nutritionalInformations
** Exposer ces champs à l'editor avec UPROPERTY(EditAnywhere)
* Mise en place du modèle
** Création du StaticMeshes
*** Importer ImportAssets/Potato/potatoes.FBX
*** Considérer utiliser un Import Uniform Scale de 5
** Création des Textures
*** Importer les textures ImportAssets/Potato/potato_texture.jpg
** Création des Materials
*** Créer nouveau Material 
*** Définir Texture Sample vers texture en fournir dans Base Color
*** Définir Constant 0 à Metallic et Specular
*** Définir Constant 1 à Roughness
** Créer blueprint
*** Choisir APotato comme classe parent
*** Ajouter un StaticMeshComponent
**** Assigner le StaticMesh précédement défini
**** Assigner le Material précédement défini 
