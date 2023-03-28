#pragma once
#include "Weapon.h"

// 설명 : F3-1 Shotgun 샷건
class MapModifier;
class WeaponShotgun : public Weapon
{
public:
	// constrcuter destructer
	WeaponShotgun() ;
	~WeaponShotgun();

	// delete Function
	WeaponShotgun(const WeaponShotgun& _Other) = delete;
	WeaponShotgun(WeaponShotgun&& _Other) noexcept = delete;
	WeaponShotgun& operator=(const WeaponShotgun& _Other) = delete;
	WeaponShotgun& operator=(WeaponShotgun&& _Other) noexcept = delete;

	void ResetWeapon();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:

	int BulletCount = 2;

	std::vector <GameEngineCollision*> ShotGunCollision;							// index에 해당하는 총알 콜리전
	std::vector <float4> ShotGunDir;												// index에 해당하는 총알 발사 방향
	GameEngineRender* AimingLine = nullptr;


	std::vector<bool> isShooted;													// index에 해당하는 총알이 발사되었는지

	bool IsDone();
	void WeaponShotgunInit();														// 총알 추가
	void WeaponMove(GameEngineCollision* _Col, float _DeltaTime, float4 _Dir);		// 총알 이동
	void Firing(float _DeltaTime);	
	void CheckFiring();

    float AimIndex = 15;
    int NextAimIndex = 15;
    void SetAimFrameIndex();

    bool isIsFireAnimationDone = false;

};

