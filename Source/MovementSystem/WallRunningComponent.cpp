// Fill out your copyright notice in the Description page of Project Settings.


#include "WallRunningComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UWallRunningComponent::UWallRunningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//default values for variables

	b_isWallRunning = false;
	b_isJumping = false;
	f_wallRunGravityScale = 0.0f;
	f_normalGravityScale = 1.0f;

}


// Called when the game starts
void UWallRunningComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//ger owner and movement
	ac_wallRunCharacter = Cast<ACharacter>(GetOwner());
	if (ac_wallRunCharacter)
	{
		uc_movementComponent = ac_wallRunCharacter->GetCharacterMovement();

		//binding a jump event
		ac_wallRunCharacter->OnJumped().AddDynamic(this, &UWallRunningComponent::OnJump);
		ac_wallRunCharacter->LandedDelegate.AddDynamic(this, UWallRunningComponent::OnLanded);
	}

}


// Called every frame
void UWallRunningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWallRunningComponent::WallCheck()
{
	
}

void UWallRunningComponent::WallRunStart(const FVector& wallNormal)
{
}

void UWallRunningComponent::WallRunStop()
{
}

void UWallRunningComponent::OnJump()
{
}

void UWallRunningComponent::OnLanded(const FHitResult& Hit)
{
}



