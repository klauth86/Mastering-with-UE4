#include "MasteringInventory.h"
#include "MasteringCharacter.h"
#include "MasteringWeaponPickup.h"
#include "Engine/World.h"

#define UNLIMITED_AMMO -1

// Sets default values for this component's properties
UMasteringInventory::UMasteringInventory() {
	PrimaryComponentTick.bCanEverTick = true;

	MyOwner = Cast<AMasteringCharacter>(GetOwner());
	check(GetOwner() == nullptr || MyOwner != nullptr);
}

void UMasteringInventory::SelectBestWeapon() {
	int highestWeaponPower = CurrentWeaponPower;
	FWeaponProperties bestWeapon;
	bool hasResult = false;

	for (auto WeaponIt = WeaponsArray.CreateConstIterator(); WeaponIt; ++WeaponIt) {
		const FWeaponProperties &currentProps = *WeaponIt;

		// skip any weapons that don't have ammo, ammo of -1 is a special case meaning it has unlimited ammo
		if (currentProps.Ammo == 0)
			continue;

		if (currentProps.WeaponPower > highestWeaponPower) {
			highestWeaponPower = currentProps.WeaponPower;
			bestWeapon = currentProps;
			hasResult = true;
		}
	}

	if (hasResult) {
		SelectWeapon(bestWeapon);
		CurrentWeaponPower = highestWeaponPower;
	}
}

void UMasteringInventory::SelectWeapon(FWeaponProperties Weapon) {
	MyOwner->EquipWeapon(Weapon.WeaponClass);
	CurrentWeapon = Weapon.WeaponClass;

	OnSelectedWeaponChanged.Broadcast(Weapon);
}

void UMasteringInventory::AddDefaultWeapon() {
	if (DefaultWeaponPickup != nullptr) {
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn a pickup and immediately add it to our player
		AMasteringWeaponPickup* defaultPickup = GetWorld()->SpawnActor<AMasteringWeaponPickup>(DefaultWeaponPickup, FVector(0.0f), FRotator(0.0f), ActorSpawnParams);
		defaultPickup->HavePlayerPickup(MyOwner);
	}
}

void UMasteringInventory::AddWeapon(FWeaponProperties props) {
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt) {
		FWeaponProperties &currentProps = *WeaponIt;
		if (currentProps.WeaponClass == props.WeaponClass) {
			checkSlow(AmmoCount >= 0);
			currentProps.Ammo += props.Ammo;
			return; // our work is done if we found the gun already in inventory, just update ammo
		}
	}

	WeaponsArray.Add(props);

	OnWeaponAdded.Broadcast(props);
}

void UMasteringInventory::ChangeAmmo(TSubclassOf<class AMasteringWeapon> Weapon, const int ChangeAmount) {
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt) {
		FWeaponProperties &currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon) {
			if (currentProps.Ammo == UNLIMITED_AMMO) // unlimited ammo gun, we're done
				return;

			currentProps.Ammo = FMath::Clamp(currentProps.Ammo + ChangeAmount, 0, 999);
			if (currentProps.Ammo == 0) // gun is now empty!
			{
				OnWeaponRemoved.Broadcast(currentProps);

				CurrentWeaponPower = -1; // force us to select any better weapon that does have ammo
				SelectBestWeapon();
			}
			return; // our work is done if we found the gun already in inventory, just update ammo
		}
	}
}

int UMasteringInventory::FindCurrentWeaponIndex() const {
	int currentIndex = 0;
	for (auto WeaponIt = WeaponsArray.CreateConstIterator(); WeaponIt; ++WeaponIt, ++currentIndex) {
		const FWeaponProperties &currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon)
			break;
	}

	checkSlow(currentIndex < WeaponsArray.Num());

	return currentIndex;
}

void UMasteringInventory::SelectNextWeapon() {
	int currentIndex = FindCurrentWeaponIndex();

	if (currentIndex == WeaponsArray.Num() - 1) // we're at the end
	{
		SelectWeapon(WeaponsArray[0]);
	}
	else {
		SelectWeapon(WeaponsArray[currentIndex + 1]);
	}
}

void UMasteringInventory::SelectPreviousWeapon() {
	int currentIndex = FindCurrentWeaponIndex();

	if (currentIndex > 0) // we're not at the start
	{
		SelectWeapon(WeaponsArray[currentIndex - 1]);
	}
	else {
		SelectWeapon(WeaponsArray[WeaponsArray.Num() - 1]); // select the last
	}
}