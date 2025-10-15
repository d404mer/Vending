#include "InteractiveCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AInteractiveCube::AInteractiveCube()
{
    PrimaryActorTick.bCanEverTick = false;

    // ������� �������� ���������
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // ������� ��� ����
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetupAttachment(RootComponent);

    // ����������� �������� ��� ��������������
    InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
    InteractionCollision->SetupAttachment(CubeMesh);
    InteractionCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    InteractionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // ������� ��������� ��� ����������� ������
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
    TextRenderComponent->SetupAttachment(CubeMesh);
    TextRenderComponent->SetRelativeLocation(FVector(0, 0, 150.f)); // ��� �����
    TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
    TextRenderComponent->SetVerticalAlignment(EVRTA_TextCenter);
    TextRenderComponent->SetWorldSize(24.f);
    TextRenderComponent->SetText(FText::FromString(""));
    TextRenderComponent->SetHiddenInGame(true); // ���������� �����

    // ��������� �� ���������
    InteractionText = FString(TEXT("Never gonna give you up!"));
    TextDisplayTime = 3.0f;
}

void AInteractiveCube::BeginPlay()
{
    Super::BeginPlay();
}

void AInteractiveCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractiveCube::Interact()
{
    // ������������� ����
    if (InteractionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
    }

    // ���������� �����
    if (TextRenderComponent)
    {
        TextRenderComponent->SetText(FText::FromString(InteractionText));
        TextRenderComponent->SetHiddenInGame(false);

        // ������������� ������ ��� ������� ������
        GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &AInteractiveCube::HideText, TextDisplayTime, false);
    }

    // �������� ������� ��� UI (�� ������ ������)
    OnInteraction.Broadcast(InteractionText);

    // �������� � �������
    UE_LOG(LogTemp, Warning, TEXT("%s"), *InteractionText);
}

void AInteractiveCube::HideText()
{
    if (TextRenderComponent)
    {
        TextRenderComponent->SetHiddenInGame(true);
        TextRenderComponent->SetText(FText::FromString(""));
    }
}