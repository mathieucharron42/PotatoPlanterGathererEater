# Exercice1 : Gameplay Framework

## Mise en place initiale du GameRole: APotatoGameRole
* Définir APotatoGameMode
	* Hériter de AGameMode
	* Laisser vide pour l'instant, suite à venir
* Assigner le APotatoGameRole au niveau
	* Ouvrir l'onglet Window -> World Settings
	* Assigner APotatoGameMode dans GameMode Override

## Mise en place du PlayerState: APotatoPlayerState
* Définir APotatoPlayerState
	* Hériter de APlayerState
	* Définir 1 champ
		* Role courrant
			* UPROPERTY(Transient)
			* FPotatoGameRole CurrentRole
	* Définir 2 méthodes
		* void SetCurrentRole(FPotatoGameRole)
		* FPotatoGameRole GetCurrentRole()
* Assigner le APotatoPlayerState au niveau
	* Ouvrir l'onglet Window -> World Settings
	* Assigner APotatoPlayerState dans Player State Class

## Mise en place du PlayerController: APotatoPlayerController
* Définir APotatoPlayerController
	* Hériter de APlayerController
	* Définir 3 méthodes
		* void ChangeRole()
			* But: Demander un changement de role
			* Récuperer le APotatoGameMode
			* Déléguer exécution par APotatoGameMode::ChangeRole(APotatoPlayerController*)
		* APotatoPlayerController::QuitGame()
			* But: Quitter la partie
			* Invoquer FGenericPlatformMisc::RequestExit(false);
		* virtual void SetupInputComponent() override
			* Binder les inputs aux méthodes
			* Binder sur "Switch" la méthode APotatoPlayerController::Server_ChangeRole
			* Binder sur "Quit" la méthode &APotatoPlayerController::QuitGame
* Assigner le APotatoPlayerController au niveau
	* Ouvrir l'onglet Window -> World Settings
	* Assigner APotatoPlayerController dans Player Controller Class

## Mise en place du GameState: APotatoGameState
* Définir APotatoGameState
	* Hériter de AGameState
	* Définir 1 champ
		* Indicateur de termination de la partie
			* UPROPERTY(Transient)
			* bool GameEnded = false
	* Définir 2 méthodes
		* bool GetGameEnded()
		* void SetGameEnded(bool gameEnded)
* Assigner le APotatoGameState au niveau
	* Ouvrir l'onglet Window -> World Settings
	* Assigner APotatoGameState dans Game State Class

## Compléter le GameMode: APotatoGameMode
* Compléter APotatoGameMode
	* Hériter de AGameMode
	* Définir 2 champs
		* Type de potato à spawner
			* UPROPERTY(EditAnywhere)
			* TSubclassOf<APotato> PotatoType;
		* Ensemble des rôles disponibles
			* UPROPERTY(EditAnywhere)
			* TArray<FPotatoGameMode> Roles;
	* Définir 4 méthodes
		* void CheckGameEnded()
			* But: Vérification de la fin de la partie
			* Collecter tous les UPotatoEatingComponent des APotatoBaseCharacters du world
			* Déterminer si tous les UPotatoEatingComponent retournent !UPotatoEatingComponent::IsHungry()
			* Si oui alors invoquer APotatoGameState::SetGameEnded(true) pour mettre fin à la partie sur le GameState associé
		* virtual void Tick(float dt) override
			* But: Fonction invoquée à chaque frame
			* Invoquer APotatoGameMode::CheckGameEnded()
		* APotatoBaseCharacter* APotatoBaseCharacter* FindSuitableCharacter(TSubclassOf<APotatoBaseCharacter> type)
			* But: Trouver personnage non-possédé d'un type spécifique	
			* Itérer sur tous les APotatoBaseCharacter du world
				* Valider si le APotatoBaseCharacter itéré correspond au type (AActor::IsA(type))
				* Valider si le APotatoBaseCharacter itéré n'est pas possédé par un joueur (APawn::GetController() == nullptr)
				* Si oui alors retourner le personnage
		* void ChangeRole(APotatoPlayerController* requester)
			* But: Changer de role
			* Récupérer APlayerState associé au requester
			* Itérer sur les Roles autres que celui de APlayerState::GetCurrentRole()
				* Chercher personnage compatible non-possédé (APotatoGameMode::FindSuitableCharacter)
				* Si personnage trouvé
					* Posséder personnage (APlayerController::Possess(character))
					* Assigner role itéré (APotatoPlayerState::SetCurrentRole(role))
				* Sinon, continuer la recherche
		* virtual APotatoGameMode::RestartPlayer(AController* playerController)
			* But: Assigner un role au joueur lorsqu'il débute la partie
			* Si playerController est un APotatoPlayerController (AActor::IsA<APotatoPlayerController>())
				* Invoquer ChangeRole(potatoPlayerController)
		* void SpawnPotato(const FTransform& transform, const FVector& velocity)
			* But: Créer une patate dans le monde
			* Invoquer UWorld::SpawnActor<APotato>(PotatoType, transform)
			* Invoquer UPrimitiveComponent::SetPhysicsLinearVelocity(velocity)
