# Exercice1 : Les bases

## Material des personnages
* Localiser le dossier des personnages sous Content/Potato/Characters
* Créer un MaterialInstance
  * Définir M_Male_Body comme parent
  * Observer l'existance d'un paramètre BodyColor dans M_Male_Body
  * Assigner une couleur au paramètre BodyColor
* Assigner le MaterialInstance au personnages
  * Ouvrir le blueprint d'un personnage Characters/BP_{character}
  * Sélectionner le Mesh
  * Assigner Material -> Element0 avec le MaterialInstance défini
* Exécuter pour tous les personnages
* Valider que les personnages de scène ont bien un nouveau matériel !

## Mise en place de l'acteur Potato
* Créer une structure FNutritionalInformations
  * Anoter par USTRUCT()
  * Définir des champs calories, carbs, fat et proteins
  * Exposer ces champs à l'editor avec UPROPERTY(EditAnywhere)
* Créer une classe APotato descendante de AActor
  * Anoter par UCLASS
  * Définir champ weight et nutritionalInformations
  * Exposer ces champs à l'editor avec UPROPERTY(EditAnywhere)
* Mise en place du modèle
  * Création du StaticMeshes
  * Importer ImportAssets/Potato/potatoes.FBX
  * Considérer utiliser un Import Uniform Scale de 5
* Créer la Texture
  * Importer les textures ImportAssets/Potato/potato_texture.jpg
* Créer le Material
  * Créer nouveau Material 
  * Définir Texture Sample vers texture en fournir dans Base Color
  * Définir Constant 0 à Metallic et Specular
  * Définir Constant 1 à Roughness
* Créer le blueprint
  * Choisir APotato comme classe parent
  * Ajouter un StaticMeshComponent
  * Assigner le StaticMesh précédement défini
  * Assigner le Material précédement défini 
* Valider le blueprint Potato dans la scène !

## Mise en place de l'interaction "Plant"
* Définir classe UPotatoPlantingComponent 
	* Descendante de USceneComponent
	* Anoter UCLASS(meta=(BlueprintSpawnableComponent))
	* Définir 3 champs 
		* Nom du socket de spawn
			* UPROPERTY(EditAnywhere)
			* FName SpawnSocketName
		* Vélocité de spawn
			* UPROPERTY(EditAnywhere)
			* float SpawnVelocity
		* Type de potato à spawn
			* UPROPERTY(EditAnywhere)
			* TSubclassOf<APotato> PotatoClass;
	* Définir 4 méthodes
		* virtual void InitializeComponent()
			* S'enregistre sur APotatoBaseCharacter::OnSetupPlayerInput de son owner
		* virtual void UninitializeComponent()
			* Se désenregistre de APotatoBaseCharacter::OnSetupPlayerInput de son owner
		* void OnSetupPlayerInput(UInputComponent* inputComponent)
			* Bind l'input 'fire' sur PlantPotato
		* void PlantPotato()
			* Récupere le socket SpawnSocketName sur le modèle
			* Obtient la world transform du socket
			* Détermine une vélocité aléatoire dans un cône face au personnage d'une magnitude SpawnVelocity
			* Instancie une Potato de type PotatoClass à la transform et vélocité calculée
* Ajouter UPotatoPlantingComponent au PotatoPlanterCharacter
	* Ajouter champ pour stocker le component
		* UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		* UPotatoPlantingComponent* potatoPlantingComponent;
	* Créer et enregistrer component dans constructeur UPotatoPlanterCharacter()
		* potatoPlantingComponent = CreateDefaultSubobject<UPotatoPlantingComponent>(TEXT("PotatoPlantComponent"));
		* potatoPlantingComponent->SetupAttachment(RootComponent);
* Testez si le Potato Planter est maintenant capable de spawner des potatoes !

## Mise en place de l'interaction 'PickUp'
* Définir classe UPotatoPickUpComponent 
	* Descendante de USceneComponent
	* Anoter UCLASS(meta=(BlueprintSpawnableComponent))
	* Définir 3 champs
		* Potato actuellement tenue
			* UPROPERTY(Transient)
			* APotato* heldPotato;
		* Nom du socket de tenue
			* UPROPERTY(EditAnywhere)
			* FName heldSocketName = FName("socket_hand_r")
	* Définir 4 méthodes
		* virtual void InitializeComponent()
			* Enregistre OnSetupPlayerInput sur APotatoBaseCharacter::OnSetupPlayerInput de son owner
			* Enregistre OnOwnerOverlap sur APotatoBaseCharacter::OnActorBeginOverlap
			* Enregistre OnOwnerHit sur APotatoBaseCharacter::OnActorHit
		* virtual void UninitializeComponent()
			* Se désenregistre de APotatoBaseCharacter::OnSetupPlayerInput
			* Se désenregistre de APotatoBaseCharacter::OnActorBeginOverlap
			* Se désenregistre de APotatoBaseCharacter::OnActorHit
		* void OnSetupPlayerInput(UInputComponent* inputComponent)
			* Bind l'input 'release' sur DropPotato()
		* void OnOwnerOverlap(AActor* owningActor, AActor* otherActor)
			* Lors d'un overlap où otherActor est de type APotato, invoquer PickupPotato()
		* void OnOwnerHit(AActor* owningActor, AActor* otherActor, FVector normalImpulse, const FHitResult& hit)
			* Lors d'un hit où otherActor est de type APotato, invoquer PickupPotato()
		* void PickupPotato(APotato* potato)
			* Si IsHoldingPotato() est faux, alors invoque SetHeldPotato(potato)
		* void DropPotato()
			* Si IsHoldingPotato() est vrai, alors invoque SetHeldPotato(null)
		* bool IsHoldingPotato() const
			* Informe si heldPotato est assigné
		* void SetHeldPotato(APotato* potato)
			* Assigne _heldPotato
			* Si heldPotato vient d'être pris, désactiver physique + collision et attacher l'acteur au socket heldSocketName
			* Si heldPotato vient d'être déposé, activer physique + collision et détacher l'acteur du socket
* Ajouter UPotatoPickUpComponent au PotatoPlanterCharacter, PotatoGathererCharacter et PotatoEaterCharacter
	* Ajouter champ pour stocker le component
		* UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		* UPotatoPickUpComponent* potatoPickUpComponent = nullptr;
	* Créer et enregistrer component dans constructeur
		* potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
		* potatoPickUpComponent->SetupAttachment(RootComponent);
}
* Testez si les personnages sont maintenant capables de prendre et déposer des potatoes !
