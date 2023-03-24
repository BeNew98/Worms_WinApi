#include "PlayLevel.h"
#include "WeaponSheep.h"
#include "WeaponBazooka.h"
#include "WeaponTorch.h"
#include "Map.h"
#include "Player.h"
#include "WeaponShotgun.h"
#include "WeaponGrenade.h"
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "GlobalValue.h"
#include "Leaf.h"
#include "WeaponHandgun.h"
#include "WeaponUzi.h"
#include "WeaponInterFace.h"
#include "WeaponAirStrike.h"
#include "HomingMissile.h"
#include "WeaponMinigun.h"
#include "WindUI.h"
#include "WeaponClusterBomb.h"
#include "AllPlayerHpUI.h"


#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>


GlobalValue GlobalValue::gValue;

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::SoundLoad()
{

}

void PlayLevel::ImageLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	GameEngineDirectory InterFace;
	InterFace.MoveParentToDirectory("ContentsResources");
	InterFace.Move("ContentsResources");
	InterFace.Move("Image");
	InterFace.Move("InterFace");

	{
		Dir.Move("Map");

		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity_Ground.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks_Ground.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars_Ground.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain_Ground.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("gradient.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Midground.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Under_Water.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite.bmp"));
		Image->Cut(1, 11);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite_surfice.bmp"));
		Image->Cut(1, 11);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ScatterLeaf.bmp"));
		Image->Cut(5, 3);
	}
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TrachCan.bmp"));
    }
	Dir.MoveParent();
	{
		Dir.Move("Weapon");

		GameEngineImage* bazooka = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazooka.bmp"));
		GameEngineImage* bazookaRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazookaRot.bmp"));

		GameEngineImage* Airplane = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Airplane.bmp"));

		GameEngineImage* Charging = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Charging.bmp"));
		Charging->Cut(1, 16);

		GameEngineImage* circle50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle50.bmp"));
		circle50->Cut(1, 9);

		GameEngineImage* sheepWalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkRight.bmp"));
		sheepWalkRight->Cut(1, 8);
		GameEngineImage* sheepWalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkLeft.bmp"));
		sheepWalkLeft->Cut(1, 8);

		GameEngineImage* AirMissile = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissile.bmp"));
		GameEngineImage* AirMissileRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissileRot.bmp"));

		GameEngineImage* BazSmoke = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BazSmoke.bmp"));
		BazSmoke->Cut(1, 64);
        GameEngineImage* HomingBlue = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingBlue.bmp"));
        GameEngineImage* HomingRed = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRed.bmp"));
        GameEngineImage* HomingRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRot.bmp"));



		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TempBomb.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grenade.bmp"));

		Dir.MoveParent();
	}
	{
		Dir.Move("Player");
		Dir.Move("Image");
		{
			//Left 플레이어 이미지
			GameEngineImage* IdleLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleLeft.bmp"));
			IdleLeft->Cut(1, 6);
			GameEngineImage* WalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkLeft.bmp"));
			WalkLeft->Cut(1, 15);		
			GameEngineImage* JumpReadyLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyLeft.bmp"));
			JumpReadyLeft->Cut(1, 10);

			GameEngineImage* FlyUpLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupLeft.bmp"));
			FlyUpLeft->Cut(1, 2);
			GameEngineImage* FlyDownLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownLeft.bmp"));
			FlyDownLeft->Cut(1, 2);

			GameEngineImage* bazAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimLeft.bmp"));
			bazAimLeft->Cut(1, 32);
			GameEngineImage* bazOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffLeft.bmp"));
			bazOffLeft->Cut(1, 7);
			GameEngineImage* bazOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnLeft.bmp"));
			bazOnLeft->Cut(1, 8);

            GameEngineImage* sheepOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffLeft.bmp"));
            sheepOffLeft->Cut(1, 10);
            GameEngineImage* sheepOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnLeft.bmp"));
            sheepOnLeft->Cut(1, 10);

            GameEngineImage* AirStrikeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffLeft.bmp"));
            AirStrikeOffLeft->Cut(1, 10);
            GameEngineImage* AirStrikeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnLeft.bmp"));
            AirStrikeOnLeft->Cut(1, 10);

            GameEngineImage* homingAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimLeft.bmp"));
            homingAimLeft->Cut(1, 32);
            GameEngineImage* homingOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffLeft.bmp"));
            homingOffLeft->Cut(1, 7);
            GameEngineImage* homingOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnLeft.bmp"));
            homingOnLeft->Cut(1, 7);

            GameEngineImage* GrenadeAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimLeft.bmp"));
            GrenadeAimLeft->Cut(1, 32);
            GameEngineImage* GrenadeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffLeft.bmp"));
            GrenadeOffLeft->Cut(1, 10);
            GameEngineImage* GrenadeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnLeft.bmp"));
            GrenadeOnLeft->Cut(1, 10);

            GameEngineImage* TorchFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireLeft.bmp"));
            TorchFireLeft->Cut(1, 15);
            GameEngineImage* TorchOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffLeft.bmp"));
            TorchOffLeft->Cut(1, 15);
            GameEngineImage* TorchOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnLeft.bmp"));
            TorchOnLeft->Cut(1, 15);

            GameEngineImage* UziAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimLeft.bmp"));
            UziAimLeft->Cut(1, 32);
            GameEngineImage* UziFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireLeft.bmp"));
            UziFireLeft->Cut(1, 32);
            GameEngineImage* UziOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffLeft.bmp"));
            UziOffLeft->Cut(1, 10);
            GameEngineImage* UziOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnLeft.bmp"));
            UziOnLeft->Cut(1, 10);

		}

		{
			//Right 플레이어 이미지
			GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
			IdleRight->Cut(1, 6);
			GameEngineImage* WalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkRight.bmp"));
			WalkRight->Cut(1, 15);
			GameEngineImage* JumpReadyRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyRight.bmp"));
			JumpReadyRight->Cut(1, 10);
			GameEngineImage* FlyUpRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupRight.bmp"));
			FlyUpRight->Cut(1, 2);
			GameEngineImage* FlyDownRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownRight.bmp"));
			FlyDownRight->Cut(1, 2);
			GameEngineImage* bazAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimRight.bmp"));
			bazAimRight->Cut(1, 32);
			GameEngineImage* bazOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffRight.bmp"));
			bazOffRight->Cut(1, 7);
			GameEngineImage* bazOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnRight.bmp"));
			bazOnRight->Cut(1, 8);

            GameEngineImage* sheepOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffRight.bmp"));
            sheepOffRight->Cut(1, 10);
            GameEngineImage* sheepOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnRight.bmp"));
            sheepOnRight->Cut(1, 10);

            GameEngineImage* AirStrikeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffRight.bmp"));
            AirStrikeOffRight->Cut(1, 10);
            GameEngineImage* AirStrikeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnRight.bmp"));
            AirStrikeOnRight->Cut(1, 10);

            GameEngineImage* homingAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimRight.bmp"));
            homingAimRight->Cut(1, 32);
            GameEngineImage* homingOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffRight.bmp"));
            homingOffRight->Cut(1, 7);
            GameEngineImage* homingOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnRight.bmp"));
            homingOnRight->Cut(1, 7);

            GameEngineImage* GrenadeAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimRight.bmp"));
            GrenadeAimRight->Cut(1, 32);
            GameEngineImage* GrenadeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffRight.bmp"));
            GrenadeOffRight->Cut(1,10);
            GameEngineImage* GrenadeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnRight.bmp"));
            GrenadeOnRight->Cut(1, 10);

            GameEngineImage* TorchFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireRight.bmp"));
            TorchFireRight->Cut(1, 15);
            GameEngineImage* TorchOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffRight.bmp"));
            TorchOffRight->Cut(1, 15);
            GameEngineImage* TorchOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnRight.bmp"));
            TorchOnRight->Cut(1, 15);


            GameEngineImage* UziAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimRight.bmp"));
            UziAimRight->Cut(1, 32);
            GameEngineImage* UziFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireRight.bmp"));
            UziFireRight->Cut(1, 32);
            GameEngineImage* UziOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffRight.bmp"));
            UziOffRight->Cut(1, 10);
            GameEngineImage* UziOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnRight.bmp"));
            UziOnRight->Cut(1, 10);
		}
		Dir.MoveParent();
	}
	{
		Dir.Move("UIImage");
		{
			//플레이어 UI 이미지
			//본인 캐릭턴에 상단 화살표 이미지
			GameEngineImage* BlueArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowBlue.bmp"));
			BlueArrowImage->Cut(1, 30);
			GameEngineImage* GreenArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowGreen.bmp"));
			GreenArrowImage->Cut(1, 30);
			GameEngineImage* MintArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowMint.bmp"));
			MintArrowImage->Cut(1, 30);
			GameEngineImage* PinkArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowPink.bmp"));
			PinkArrowImage->Cut(1, 30);
			GameEngineImage* RedArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowRed.bmp"));
			RedArrowImage->Cut(1, 30);
			GameEngineImage* YellowArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowYellow.bmp"));
			YellowArrowImage->Cut(1, 30);

			//캐릭터 체력 렌더 이미지
			GameEngineImage* BlueNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNumberRender.bmp"));
			BlueNumberImage->Cut(10, 1);
			GameEngineImage* GreenNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNumberRender.bmp"));
			GreenNumberImage->Cut(10, 1);
			GameEngineImage* MintNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNumberRender.bmp"));
			MintNumberImage->Cut(10, 1);
			GameEngineImage* RedNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNumberRender.bmp"));
			RedNumberImage->Cut(10, 1);
			GameEngineImage* PinkNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNumberRender.bmp"));
			PinkNumberImage->Cut(10, 1);
			GameEngineImage* YellowNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNumberRender.bmp"));
			YellowNumberImage->Cut(10, 1);

			//캐릭터 네임태그 이미지
			GameEngineImage* GreenNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNameTag.bmp"));
			GameEngineImage* YellowNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNameTag.bmp"));
			GameEngineImage* PinkNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNameTag.bmp"));
			GameEngineImage* MintNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNameTag.bmp"));
			GameEngineImage* RedNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNameTag.bmp"));
			GameEngineImage* BlueNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNameTag.bmp"));

			//캐릭터 체력 백그라운드 이미지
			GameEngineImage* PlayerHPBackgroundImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerHPBackground.bmp"));
			Dir.MoveParent();
		}
		//UI
		{
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("weaponSheet.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("2020.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("WeaponIcon.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("bazookaUI.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("clusterUI.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("grenadeUI.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("shotgunUI.bmp"));
			}


		}


        //WindBar UI
        {
        
            GameEngineImage* WindBarAnim = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBar.bmp"));
            WindBarAnim->Cut(5, 4);
        
            GameEngineImage* WindBarGauge = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windGauge.bmp"));
            GameEngineImage* WindBarHider = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBarHider.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarB.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarG.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarP.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarR.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarS.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarY.bmp"));
        }


	}
	
}

void PlayLevel::KeyLoad()
{
	if (false == GameEngineInput::IsKey("ChangePlayer"))
	{
		GameEngineInput::CreateKey("ChangePlayer", 'n');
		GameEngineInput::CreateKey("DebugCollision", '8');
		GameEngineInput::CreateKey("WeaponUp", 'W');
		GameEngineInput::CreateKey("WeaponDown", 'S');
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}
}

void PlayLevel::CreateLeaf(float _DeltaTime)
{
	AddWind.WindTime += _DeltaTime;
	if (AddWind.WindTime > 1.f)
	{
		for (int i = 0; i < 10; i++)
		{
			float4 Pos = { 300,-100 };
			Leaf* pLeaf = CreateActor<Leaf>();
			Pos.x *= i;
			Pos.x += 100.f;
			pLeaf->SetPos(Pos);
		}
		AddWind.WindTime -= 1.f;

	}
}

void PlayLevel::PlayerChange(float _DeltaTime)
{
	//Player벡터 오류 검사
	if (-1 == iPlayerNumber)
	{
		MsgAssert("PlayerNumber가 -1 입니다.");
	}

    if (GameEngineInput::IsDown("ChangePlayer"))
    {
        
    
	//벡터 인덱스 증가
	++iPlayerNumber;

	//초과시 0
	if (vecAllPlayer.size() == iPlayerNumber)
	{
		iPlayerNumber = 0;
	}

	//현재 플레이어의 턴 종료
	GlobalValue::gValue.GetPlayer()->SetIsMyTurn(false);

	//다음 플레이어가 현재 플레이어가됨
	GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);
	GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);

	CurPlayerPos = GlobalValue::gValue.GetPlayer()->GetPos();
	PrevCamPos = GetCameraPos();

    AllPlayerHpUI::AllHpUI->SetAllPlayerHP();
	bCamMove = true;
    }

	//플레이어가 변경되었다면
	if (bCamMove)
	{
		//1초동안 플레이어 카메라 위치 변경
		fLerpRatio += _DeltaTime * fLerpSpeed;
		SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - ScreenSize.half(), fLerpRatio));

		if (fLerpRatio > 1.f)
		{
			bCamMove = false;
			fLerpRatio = 0.f;

			AddWind.WindPhase = GameEngineRandom::MainRandom.RandomInt(-10, 10);
			AddWind.WindResult = AddWind.WindPower * (AddWind.MaxWind * (static_cast<float>(AddWind.WindPhase) / 10.f));

			GlobalValue::gValue.SetWindSpeed(AddWind.WindResult);
			GlobalValue::gValue.SetWindPhase(AddWind.WindPhase);
		}
	}
}

void PlayLevel::MoveCamForMouse(float _DeltaTime)
{
	float4 CurCamPos = GetCameraPos() + ScreenSize.half();
	float4 CurMousePos = GetMousePosToCamera();
	float4 DistancePos = CurMousePos - CurCamPos;
	float4 MoveCam = float4::Zero;

	if (DistancePos.x > 500.f)
	{
		MoveCam += float4::Right;
	}
	if (DistancePos.x < -500.f)
	{
		MoveCam += float4::Left;
	}
	if (DistancePos.y < -350.f)
	{
		MoveCam += float4::Up;
	}
	if (DistancePos.y > 350.f)
	{
		MoveCam += float4::Down;
	}

	if (MoveCam.ix() == 0 && MoveCam.iy() == 0)
	{
		return;
	}

	MoveCam.Normalize();
	SetCameraMove(MoveCam * fCamMoveSpeed * _DeltaTime);
}





void PlayLevel::Loading()
{
	
	SoundLoad();
	ImageLoad();
	KeyLoad();
	
	
	{
		WeaponInterFace* Actor = CreateActor<WeaponInterFace>();
	}
    {
        Map* Actor = CreateActor<Map>();
    }
	{
        WindUI* WindUIActor = CreateActor<WindUI>();
	}


	{
		MapModifier* ModifierActor = CreateActor<MapModifier>(WormsRenderOrder::Map);
	}
	

	{
		ScreenSize = GameEngineWindow::GetScreenSize();

		vecAllPlayer.reserve(6);
		for (size_t i = 0; i < 6; i++)
		{
			int iRandxPos = GameEngineRandom::MainRandom.RandomInt(0, 300);

			vecAllPlayer.push_back(CreateActor<Player>(WormsRenderOrder::Player));
			vecAllPlayer[i]->SetColImage(Map::MainMap->GetColMapName());

			float4 StartPos = float4{ 400,50 };
			StartPos.x *= i + 1;
			StartPos.x += iRandxPos;
			vecAllPlayer[i]->SetPos(StartPos);
		}

		iPlayerNumber = 0;

		GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);

		GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);
		SetCameraPos(GlobalValue::gValue.GetPlayer()->GetPos() - ScreenSize.half());
	}

    {
        AllPlayerHpUI* pAllPlayerHPUI = CreateActor<AllPlayerHpUI>();
    }
	//CreateActor<WeaponBazooka>();
	//CreateActor<WeaponSheep>();
	//CreateActor<WeaponAirStrike>();
	CreateActor<HomingMissile>();
	//CreateActor<WeaponTorch>();
}


void PlayLevel::Update(float _DeltaTime)
{
	//CreateLeaf(_DeltaTime);
    // 
    //ChangePlayer 키가 눌렸을때
    
    
    PlayerChange(_DeltaTime);
    
   
	//MoveCamForMouse(_DeltaTime);
	if (GameEngineInput::IsDown("DebugCollision"))
	{
		DebugRenderSwitch();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//CreateActor<WeaponHandgun>();
	//CreateActor<WeaponGrenade>();
	//CreateActor<WeaponUzi>();
	//CreateActor<WeaponMinigun>();
    //CreateActor<WeaponClusterBomb>();
}