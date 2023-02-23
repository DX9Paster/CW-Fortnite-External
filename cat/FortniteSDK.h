#pragma once
#include "common.h"
#include <structs.h>

Camera GetCamera();

class ARootComponent
{
public:
	
	Vector3 RelativeLocation()
	{
		return read<Vector3>((uintptr_t)this + 0x128);
	}

};

class APlayerState
{
public:

	int TeamIndex()
	{
		return read<int>((uintptr_t)this + 0x1098);
	}
};

class AFortPawn
{
public:
	uint64_t Mesh()
	{
		return read<uint64_t>((uintptr_t)this + 0x310);
	}

	auto isVisible() -> bool
	{
		float fLastSubmitTime = read<float>(this->Mesh() + 0x330);
		float fLastRenderTimeOnScreen = read<float>(this->Mesh() + 0x338);

		const float fVisionTick = 0.06f;
		bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

		return bVisible;
	}

	
	Vector3 GetBone(int id)
	{
		uintptr_t offset_bonearray = 0x5a0;

		DWORD_PTR bonearray = read<DWORD_PTR>(this->Mesh() + offset_bonearray);
		if (bonearray == NULL) {
			bonearray = read<DWORD_PTR>(this->Mesh() + offset_bonearray + 0x10);
		}
		FTransform bone = read<FTransform>(bonearray + (id * 0x60));

		FTransform ComponentToWorld = read<FTransform>(this->Mesh() + 0x240);

		D3DMATRIX Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}


	APlayerState* PlayerState()
	{
		return (APlayerState*)read<uintptr_t>((uintptr_t)this + 0x2a8);
	}

	ARootComponent* RootComponent()
	{
		return (ARootComponent*)read<uintptr_t>((uintptr_t)this + 0x190);
	}
};

class APlayerController
{
public:
	AFortPawn* AcknowledgedPawn()
	{
		return (AFortPawn*)read<uintptr_t>((uintptr_t)(this + 0x328));
	}

};

class ULocalPlayer {
public:
	Vector3 W2S(Vector3 WorldLocation)
	{
#define M_PI	3.14159265358979323846264338327950288419716939937510
		Camera vCamera = GetCamera();

		auto Location = vCamera.Location;
		auto Rotation = vCamera.Rotation;
		auto Fov = vCamera.FieldOfView;

		Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);
		Vector3 output;
		float delta[3];
		float sp = 0, cp = 0, sy = 0, cy = 0, sr = 0, cr = 0;
		float axisx[3];
		float axisy[3];
		float axisz[3];
		float transformed[3];

		delta[0] = WorldLocation.x - Location.x;
		delta[1] = WorldLocation.y - Location.y;
		delta[2] = WorldLocation.z - Location.z;

		sp = sinf(Rotation.x * M_PI / 180);
		cp = cosf(Rotation.x * M_PI / 180);
		sy = sinf(Rotation.y * M_PI / 180);
		cy = cosf(Rotation.y * M_PI / 180);
		sr = sinf(Rotation.z * M_PI / 180);
		cr = cosf(Rotation.z * M_PI / 180);

		axisx[0] = cp * cy;
		axisx[1] = cp * sy;
		axisx[2] = sp;

		axisy[0] = sr * sp * cy - cr * sy;
		axisy[1] = sr * sp * sy + cr * cy;
		axisy[2] = -sr * cp;

		axisz[0] = -(cr * sp * cy + sr * sy);
		axisz[1] = cy * sr - cr * sp * sy;
		axisz[2] = cr * cp;

		transformed[0] = delta[0] * axisy[0] + delta[1] * axisy[1] + delta[2] * axisy[2];
		transformed[1] = delta[0] * axisz[0] + delta[1] * axisz[1] + delta[2] * axisz[2];
		transformed[2] = delta[0] * axisx[0] + delta[1] * axisx[1] + delta[2] * axisx[2];

		if (transformed[2] < 1)
			transformed[2] = 1;

		if (transformed[2] / 100 > 0)
		{
			float tmpx = 0, tmpy = 0;

			tmpx = (float)(Process::WindowWidth / 2);
			tmpy = (float)(Process::WindowHeight / 2);

			output.x = tmpx + transformed[0] * tmpx / tanf(Fov * M_PI / 360) / transformed[2];
			output.y = tmpy - transformed[1] * tmpx / tanf(Fov * M_PI / 360) / transformed[2];

			return output;
		}

		return Vector3(0, 0, 0);
	}
	
	APlayerController* PlayerController()
	{
		return (APlayerController*)read<uintptr_t>((uintptr_t)this + 0x30);
	}
};

class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer()
	{
		return (ULocalPlayer*)read<uintptr_t>((uintptr_t)this);
	}
};

class UGameInstance {
public:
	ULocalPlayers* LocalPlayers()
	{
		return (ULocalPlayers*)read<uintptr_t>((uintptr_t)this + 0x38);
	}
};

class UWorld_t
{
public:
	UGameInstance* GameInstance()
	{
		return (UGameInstance*)read<uintptr_t>((uintptr_t)this + 0x1A8);
	}
};

UWorld_t* Uworld;

std::vector<AFortPawn*> playerList;
AFortPawn* LocalPawn;
ULocalPlayer* Localplayer;
APlayerController* PlayerController;

typedef struct _LootEntity {
	std::string GNames;
	uintptr_t ACurrentItem;
}LootEntity;

static std::vector<LootEntity> LootentityList;

void drawLoop(int Width, int Height) {
	while (true) {
		std::vector<AFortPawn*> tmpList;

		Uworld = read<UWorld_t*>(base_Drv + OFFSET_UWORLD);
		auto Gameinstance = Uworld->GameInstance();
		Localplayer = Gameinstance->LocalPlayers()->LocalPlayer();
		PlayerController = Localplayer->PlayerController();
		LocalPawn = PlayerController->AcknowledgedPawn();
		
		auto Persistentlevel = read<uintptr_t>((uintptr_t)Uworld + 0x30);//Persistentlevel
		DWORD ActorCount = read<DWORD>(Persistentlevel + 0xA0); //AcotrCount
		uintptr_t AActors = read<uintptr_t>(Persistentlevel + 0x98); //AActors

		for (int i = 0; i < ActorCount; i++) {
			AFortPawn* CurrentActor = read<AFortPawn*>(AActors + i * 0x8);
			
			if (CurrentActor == LocalPawn) continue;
			int MyTeamId = LocalPawn->PlayerState()->TeamIndex();
			int ActorTeamId = CurrentActor->PlayerState()->TeamIndex();
			if (MyTeamId == ActorTeamId) continue;
			
			auto player = read<float>((uintptr_t)CurrentActor + 0x4270);
			if (player == 10) {
				tmpList.push_back(CurrentActor);
			}

		}
		playerList = tmpList;
		Sleep(1);
	}

}

Camera GetCamera()
{
	Camera FGC_Camera;
	auto a1 = (uintptr_t)LocalPawn->RootComponent();

	int64 v1 = read<int64>((uintptr_t)Localplayer + 0xd0);
	int64 v9 = read<int64>(v1 + 0x10); // 0x10

	FGC_Camera.FieldOfView = 80.0f / (read<double>(v9 + 0x680) / 1.19f); // 0x600

	FGC_Camera.Rotation.x = read<double>(v9 + 0x7D0);
	FGC_Camera.Rotation.y = read<double>(a1 + 0x148);

	uint64_t FGC_Pointerloc = read<uint64_t>((uintptr_t)Uworld + 0x100);
	FGC_Camera.Location = read<Vector3>(FGC_Pointerloc);

	return FGC_Camera;
}