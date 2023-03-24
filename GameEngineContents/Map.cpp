#include "Map.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "MapObject.h"
#include "WeaponInterFace.h"
//ScreenSize: { 1280, 960 }
//BackGround_Hrz: 5120


Map* Map::MainMap = nullptr;
int Map::MapMode = 0;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	MainMap = this;

	if (nullptr == MainMap)
	{
		MsgAssert("MainMap이 nullptr입니다.");
		return;
	}


	Maps.push_back("MapCity.bmp");
	Maps.push_back("MapBooks.bmp");
	Maps.push_back("MapCars.bmp");
	Maps.push_back("MapTrain.bmp");

	ColMaps.push_back("MapCity_Ground.bmp");
	ColMaps.push_back("MapBooks_Ground.bmp");
	ColMaps.push_back("MapCars_Ground.bmp");
	ColMaps.push_back("MapTrain_Ground.bmp");

	MapName = Maps[MapMode];
	ColMapName = ColMaps[MapMode];

	//입력 키 생성
	if (false == GameEngineInput::IsKey("FreeMoveSwitch"))
	{
		GameEngineInput::CreateKey("FreeMoveSwitch", '0');
		GameEngineInput::CreateKey("FreeLeft", VK_LEFT);
		GameEngineInput::CreateKey("FreeRight", VK_RIGHT);
		GameEngineInput::CreateKey("FreeUp", VK_UP);
		GameEngineInput::CreateKey("FreeDown", VK_DOWN);

		//디버깅 모드_충돌맵 확인
		GameEngineInput::CreateKey("DebugMode", '9');
	}

	//마우스 좌측 키 입력 생성
	if (false == GameEngineInput::IsKey("LandHole"))
	{
		GameEngineInput::CreateKey("LandHole", VK_LBUTTON);
	}


	//MapRender 생성
	MapRender = CreateRender(WormsRenderOrder::Map);
	MapRender->SetImage(MapName);
	float4 MapScale = MapRender->GetImage()->GetImageScale();
	MapRender->SetPosition(MapScale.half());
	MapRender->SetScaleToImage();

	//ColMapRender 생성
	{
		ColMapRender = CreateRender(WormsRenderOrder::Map);
		ColMapRender->SetImage(ColMapName);
		ColMapRender->SetPosition(MapScale.half());
		ColMapRender->SetScaleToImage();

        ColMapRender->Off();
	}

	//BackGround_Sky
	{
		GameEngineRender* BackGround = CreateRender(WormsRenderOrder::BackGround);
		BackGround->SetImage("gradient.bmp");
		BackGround->SetPosition(MapScale.half());
		BackGround->SetScaleToImage();
	}
	//BackGround_Mountain
	{
		GameEngineRender* BackGround = CreateRender(WormsRenderOrder::BackGround);
		BackGround->SetImage("Midground.bmp");
		BackGround->SetPosition(MountainPos);
		BackGround->SetScale(BackScale);
	}
	//BackGround_Wave
	{
		GameEngineRender* WaveBack = CreateRender(WormsRenderOrder::BackGround);
		WaveBack->SetImage("Under_Water.bmp");
		WaveBack->SetPosition(WaveBackPos);
		WaveBack->SetScale(BackScale);
	}
	//Wave Animation
    {
        GameEngineRender* Wave0 = CreateRender(WormsRenderOrder::BackGround);
        Wave0->SetImage("Water_sprite.bmp");
        Wave0->SetPosition(WaveAnimPos0);
        Wave0->SetScale(WaveScale);
        Wave0->CreateAnimation({ .AnimationName = "Wave0",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
        Wave0->ChangeAnimation("Wave0");

    }
	int RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);					//Animation을 시작할 랜덤한 인덱스
	{
		GameEngineRender* Wave1 = CreateRender(WormsRenderOrder::Wave);
		Wave1->SetImage("Water_sprite.bmp");
		Wave1->SetPosition(WaveAnimPos1);
		Wave1->SetScale(WaveScale);
		Wave1->CreateAnimation({ .AnimationName = "Wave1",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave1->ChangeAnimation("Wave1", RandIdx);

	}
    RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave2 = CreateRender(WormsRenderOrder::Wave);
		Wave2->SetImage("Water_sprite.bmp");
		Wave2->SetPosition(WaveAnimPos2);
		Wave2->SetScale(WaveScale);
		Wave2->CreateAnimation({ .AnimationName = "Wave2",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave2->ChangeAnimation("Wave2", RandIdx);
	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave3 = CreateRender(WormsRenderOrder::Wave);
		Wave3->SetImage("Water_sprite.bmp");
		Wave3->SetPosition(WaveAnimPos3);
		Wave3->SetScale(WaveScale);
		Wave3->CreateAnimation({ .AnimationName = "Wave3",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave3->ChangeAnimation("Wave3", RandIdx);

	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave4 = CreateRender(WormsRenderOrder::Wave);
		Wave4->SetImage("Water_sprite.bmp");
		Wave4->SetPosition(WaveAnimPos4);
		Wave4->SetScale(WaveScale);
		Wave4->CreateAnimation({ .AnimationName = "Wave4",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave4->ChangeAnimation("Wave4", RandIdx);

	}
    

    MapObject* Object1 = GetLevel()->CreateActor<MapObject>(WormsRenderOrder::MapObject);
    float4 pos = Object1->GetRandomPos();
    Object1->SetPos(pos);

    MapObject* Object2 = GetLevel()->CreateActor<MapObject>(WormsRenderOrder::MapObject);
    Object2->SetPos(Object2->GetRandomPos());
}

void Map::Update(float _DeltaTime)
{
	
	if (true == GameEngineInput::IsDown("LandHole"))
	{
		float4 Pos = GetLevel()->GetMousePosToCamera();
		MapModifier::MainModifier->CreateHole(Pos, 20);

		return;
	}

  

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DebugMode"))							//디버깅 모드_충돌맵 혹은 맵을 볼 수 있음
	{
		if (false == IsColMap)
		{
			IsColMap = true;
			MapRender->Off();
			ColMapRender->On();
		}
		else
		{
			IsColMap = false;
			MapRender->On();
			ColMapRender->Off();
		}
	}

	std::string PlayLevel = "FreeMoveSwitch Key : 0, DebugMode Key: 9";
	GameEngineLevel::DebugTextPush(PlayLevel);
}

bool FreeMove = false;
bool Map::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FreeMoveSwitch"))
	{
		FreeMove = !FreeMove;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("FreeLeft"))
		{
			GetLevel()->SetCameraMove(float4::Left * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeRight"))
		{
			GetLevel()->SetCameraMove(float4::Right * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeUp"))
		{
			GetLevel()->SetCameraMove(float4::Up * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeDown"))
		{
			GetLevel()->SetCameraMove(float4::Down * FreeSpeed * _DeltaTime);
		}
	}

	return FreeMove;
}

HDC Map::GetMapDC() const
{
	HDC hdc = MapRender->GetImage()->GetImageDC();
	return hdc;
}

HDC Map::GetColMapDC() const
{
	HDC hdc = ColMapRender->GetImage()->GetImageDC();
	return hdc;
}

void Map::Render(float _DeltaTime)
{
	std::string MousePosStr = "MousePosition : ";
	MousePosStr += GetLevel()->GetMousePosToCamera().ToString();
	GameEngineLevel::DebugTextPush(MousePosStr);
}