#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/Button.h>
#include <vector>
class WeaponInterFace : public GameEngineActor
{
public:
	static WeaponInterFace* Interface;
	static GameEngineLevel* Value;

	// constrcuter destructer
	WeaponInterFace();
	~WeaponInterFace();
	// delete Function
	WeaponInterFace(const WeaponInterFace& _Other) = delete;
	WeaponInterFace(WeaponInterFace&& _Other) noexcept = delete;
	WeaponInterFace& operator=(const WeaponInterFace& _Other) = delete;
	WeaponInterFace& operator=(WeaponInterFace&& _Other) noexcept = delete;
	
	
	void test();
protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _Time) override;

private:

	GameEngineRender* WaeponInterface = nullptr;
	GameEngineRender* WaeponIcon = nullptr;
	float4 MoveDir = float4::Zero;
	GameEngineCollision* WeaponInterFaceCollision = nullptr;
	GameEngineCollision* WeaponInterFaceCollision2 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision3 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision4 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision5 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision6 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision7 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision8 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision9 = nullptr;
	GameEngineCollision* WeaponInterFaceCollision10 = nullptr;

	Button* A = nullptr;

	std::vector<Button*> ButtonManager;
	bool InterfaceMove = true;
};