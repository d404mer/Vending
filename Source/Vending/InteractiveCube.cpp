#include "InteractiveCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AInteractiveCube::AInteractiveCube()
{
    PrimaryActorTick.bCanEverTick = false;

    // Создаем корневой компонент
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Создаем меш куба
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetupAttachment(RootComponent);

    // Настраиваем коллизию для взаимодействия
    InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
    InteractionCollision->SetupAttachment(CubeMesh);
    InteractionCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    InteractionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Создаем компонент для отображения текста
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
    TextRenderComponent->SetupAttachment(CubeMesh);
    TextRenderComponent->SetRelativeLocation(FVector(0, 0, 150.f)); // Над кубом
    TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
    TextRenderComponent->SetVerticalAlignment(EVRTA_TextCenter);
    TextRenderComponent->SetWorldSize(24.f);
    TextRenderComponent->SetText(FText::FromString(""));
    TextRenderComponent->SetHiddenInGame(true); // Изначально скрыт

    // Настройки по умолчанию
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
    // Воспроизводим звук
    if (InteractionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
    }

    // Показываем текст
    if (TextRenderComponent)
    {
        TextRenderComponent->SetText(FText::FromString(InteractionText));
        TextRenderComponent->SetHiddenInGame(false);

        // Устанавливаем таймер для скрытия текста
        GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &AInteractiveCube::HideText, TextDisplayTime, false);
    }

    // Вызываем делегат для UI (на всякий случай)
    OnInteraction.Broadcast(InteractionText);

    // Логируем в консоль
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