// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "WallRunningComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTSYSTEM_API UWallRunningComponent : public UActorComponent
{

	GENERATED_BODY()

private:

	///reference to character

	ACharacter* ac_wallRunCharacter;
	UCharacterMovementComponent* uc_movementComponent;

	///variables for wall running state

	bool b_isWallRunning;
	bool b_isJumping;
	FVector fv_wallRunDirection;
	FVector fv_wallNormal;

	///variables for manipulating gravity

	float f_wallRunGravityScale;
	float f_normalGravityScale;


	// Checks for wall on either side of the actor this component is attached to.
	void WallCheck();

	//called when wall run is to start and begins wall run functionality.
	void WallRunStart(const FVector& wallNormal);

	//called when wall run is to stop and ends wall run functionality.
	void WallRunStop();


public:
	// Sets default values for this component's properties
	UWallRunningComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:

	UFUNCTION()
	void OnJump();

	UFUNCTION()
	void OnLanded(const FHitResult& Hit);





};
