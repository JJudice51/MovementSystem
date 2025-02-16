// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "ac_WallRunComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTSYSTEM_API UWallRunComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	//reference to character
	ACharacter* m_wallRunCharacter;
	UCharacterMovementComponent* m_movementComponent;

public:	
	// Sets default values for this component's properties
	UWallRunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	


		
};
