#pragma once
#include "Weapon.h"

// ���� : F2-1 Grenade ����ź
class MapModifier;
class WeaponGrenade : public Weapon
{
public:
	// constrcuter destructer
	WeaponGrenade();
	~WeaponGrenade();

	// delete Function
	WeaponGrenade(const WeaponGrenade& _Other) = delete;
	WeaponGrenade(WeaponGrenade&& _Other) noexcept = delete;
	WeaponGrenade& operator=(const WeaponGrenade& _Other) = delete;
	WeaponGrenade& operator=(WeaponGrenade&& _Other) noexcept = delete;
	
	void ResetWeapon();

protected:

	void Start() override;
	void Update(float _DeltaTime) override;



private:

	void WeaponGrenadeInit();

	bool isExplosion = false;

	void SetCharge(); // charge
	void Firing(float _DeltaTime);

	GameEngineRender* WeaponRender = nullptr;		//����
	GameEngineCollision* WeaponCollision = nullptr;	//�ݸ���

};

