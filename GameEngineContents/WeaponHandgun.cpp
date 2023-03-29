#include "WeaponHandgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MapModifier.h"
#include "Player.h"
#include "SmokeSparkEffect.h"

WeaponHandgun::WeaponHandgun()
{
}

WeaponHandgun::~WeaponHandgun()
{
}

void WeaponHandgun::Start()
{
	// 샷건 기본 설정
	WeaponName = "Handgun";
	MoveSpeed = 600.0f;
	Dir = float4::Right;
	//float Dmg = 0.0f;
	BombScale = 11;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함

	//AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Handgun);
	SetCurPlayer();


	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
	AimingLine->SetScale({ 20,20 });


}

void WeaponHandgun::Update(float _DeltaTime)
{
    // 총알 수만큼 init
	while (BulletCount > HandgunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponHandgunInit();
	}
    if (false == isFire)
    {
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
        SetAimFrameIndex();

        if (AimIndex != NextAimIndex && CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON && CurPlayer->GetCurWeapon()->GetWeaponNumber() == WeaponNumber)
        {
            float Ratio = 6 * _DeltaTime;
            AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);
            CurPlayer->ChangePlayerAnimation("HandgunAim", static_cast<int>(AimIndex));
            AimingLine->On();
            AimingLine->SetPosition(Dir * 200); // 조준선 이동
            if (Dir.x > 0)
            {
                AimingLine->SetAngle(Dir.GetAnagleDeg());
            }
            else
            {
                AimingLine->SetAngle(-Dir.GetAnagleDeg());
            }
        }
        else
        {
            AimingLine->Off();
        }
        CheckFiring(); // 방향체크, 발사 체크
    }
	Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함

    // 모든 총알발사되어 터졌는지 체크
	if (true == IsDone())
	{
		isWeaponDone = true;
        GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요
    }
}

void WeaponHandgun::SetAimFrameIndex()
{
    float Angle = Dir.GetAnagleDeg();


    int NewIndex = 0;
    if (Dir.x > 0 && Angle > 270)
    {
        Angle = Angle - 360;
    }

    else if (Dir.x < 0)
    {
        Angle = 180 - Angle;
    }

    NewIndex = Angle / 5 + 15;

    if (NewIndex < 0)
    {
        NewIndex = 0;
    }
    NextAimIndex = NewIndex;

}

bool WeaponHandgun::IsDone()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == HandgunCollision[i]->IsUpdate())
		{
			return false;
		}

	}
	return true;
}

void WeaponHandgun::CheckFiring()
{
	if (false == isFire)
	{
		if (PressShoot()) // 발사체크
		{
			isFire = true;
            AimingLine->Off();
            CurPlayer->ChangePlayerAnimation("HandgunFire", static_cast<int>(AimIndex));

		}
		float4 PlayerPos = CurPlayer->GetPos();
		SetPos(PlayerPos);
		Dir = GetShootDir(); // 방향 조정

	}

}


void WeaponHandgun::Firing(float _DeltaTime)
{
	if (true == isFire && false == isWeaponDone)
	{
        /*CurPlayer->ChangePlayerAnimation("HandgunFire", static_cast<int>(AimIndex));*/
        GetLevel()->SetCameraPos(HandgunCollision[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());

		DelayTime -= _DeltaTime;
		if (DelayTime < 0)
		{
			DelayTime = 0.5f;
			for (int i = 0; i < BulletCount; i++)
			{
				if (isShooted[i] == false)
				{
					isShooted[i] = true;
					break;
				}

			}
		}

		for (int i = 0; i < BulletCount; i++)
		{
			if (true == isShooted[i] && true == HandgunCollision[i]->IsUpdate())
			{
                if (isIsFireAnimationDone == false && i == BulletCount - 1 && isWeaponDone == false)
                {
                    CurPlayer->ChangePlayerAnimation("Idle");
                    isIsFireAnimationDone = true;
                }

				HandgunCollision[i]->SetMove(Dir * _DeltaTime * MoveSpeed);
				if (true == CheckCollision(HandgunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
				{
                    SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                    Smoke->SetPos(HandgunCollision[i]->GetActorPlusPos());
                    Smoke->CreateSmokeSpark(6, 2, BombScale);

					GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();								  // 1. Bomb 콜리전 가져오기
					BombCollision->SetPosition(GetPos() + HandgunCollision[i]->GetPosition());											  // 2. Bomb 콜리전 이동

					AttackPlayer(BombCollision);																						  // 3. Bomb콜리전 Player Check

					MapModifier::MainModifier->CreateHole(GetPos() + HandgunCollision[i]->GetPosition(), BombScale);					  // 4. 구멍 만들기


					HandgunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
				}
			}
		}
	}
}


void WeaponHandgun::WeaponHandgunInit()
{
	// Handgun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 25,25 });

	HandgunCollision.push_back(Collision);
	isShooted.push_back(false);
	DelayTime = 0.5f;

}

void WeaponHandgun::ResetWeapon()
{
	isFire = false;
	DelayTime = 0.5f;
	for (int i = 0; i < BulletCount; i++)
	{
		isShooted[i] = false;
		HandgunCollision[i]->SetPosition(float4::Zero);
		HandgunCollision[i]->On();
	}
}