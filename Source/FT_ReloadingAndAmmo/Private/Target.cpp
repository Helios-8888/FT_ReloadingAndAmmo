// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/StaticMeshComponent.h" 

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	RootComponent = TargetMesh;

	// Set up overlap events
	TargetMesh->SetGenerateOverlapEvents(true);
	TargetMesh->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	bIsHit = false;
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsMoving && bIsHit == false)
	{
		SetActorLocation(GetActorLocation() + FVector(MoveDirection * 100.0f * DeltaTime, 0.0f, 0.0f));

		// ping pong the target between 
		if (GetActorLocation().X >= 2850.0f || GetActorLocation().X <= 130.0f)
		{
			MoveDirection *= -1;
		}
	}
}

void ATarget::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapBegin triggered"));
	bIsHit = true;
	
	// hide the mesh for a bit
	TargetMesh->SetVisibility(false);
	TargetMesh->SetGenerateOverlapEvents(false);
}