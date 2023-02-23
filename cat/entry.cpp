#include "common.h"
#include "overlay.hpp"
#include "FortniteSDK.h"

int AimboneInt = 0;
static const char* AimboneItems[]{
	"   Head",
	"   Neck",
	"   Chest",
	"   Pelvis",
};

bool common{ true };
bool uncommon{ true };
bool rare{ true };
bool epic{ true };
bool legendary{ true };
bool mythic{ true };

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA BuffaloPurple = { 94,23,235,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 129, 47, 212,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA coolcol = { 51, 171, 145, 255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 177, 181, 179,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}




		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}

};
Color Col;

std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}

void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}

void draw_cornered_box(int x, int y, int w, int h, ImColor color, int thickness) {
	float line_w = (w / 3);
	float line_h = (h / 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
}

void DrawLine(int x1, int y1, int x2, int y2, const ImU32& color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
}

static std::string ReadGetNameFromFName(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_Drv + 0xD55C20 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); // FNamePool
	uint16_t nameEntry = read<uint16_t>(NamePoolChunk);

	int nameLength = nameEntry >> 6;
	char buff[1024];
	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{
			buff[x] = read<char>(NamePoolChunk + 4 + x);
		}

		char* v2 = buff;
		signed int v4 = nameLength;
		int v5;
		uint64_t result;
		unsigned int v7; // ecx
		char v8; // dl
		uint64_t v9; // rcx
		uint16_t* v10; // rax

		v5 = 0;
		result = read<unsigned int>(base_Drv + 0xDF98EEC) >> 5;

		if (v4)
		{
			do
			{
				v7 = *v2++;
				v8 = result ^ (16 * v7) ^ (result ^ (v7 >> 4)) & 0xF;
				result = (unsigned int)(result + 4 * v5++);
				*(v2 - 1) = v8;
			} while (v5 < v4);
		}
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else
	{
		return ("");
	}
}

std::string GetNameFromFName(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_Drv + 0xD55C20 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); // FNamePool

	if (read<uint16_t>(NamePoolChunk) < 64)
	{
		DWORD a1 = read<DWORD>(NamePoolChunk + 4);
		return ReadGetNameFromFName(a1);
	}
	else
	{
		return ReadGetNameFromFName(key);
	}
}

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}

Vector3 localactorpos;

void ActorEsp()
{
	float closestDistance = FLT_MAX;
	AFortPawn* closestPawn = NULL;
	auto player = playerList;

	for (LootEntity LEntityList : LootentityList) {

		if (LocalPawn)
		{
			uintptr_t ItemRootComponent = read<uintptr_t>(LEntityList.ACurrentItem + 0x190);
			Vector3 ItemPosition = read<Vector3>(ItemRootComponent + 0x128);
			float ItemDist = localactorpos.Distance(ItemPosition) / 100.f;
			std::string null = ("");

			auto IsSearched = read<BYTE>((uintptr_t)LEntityList.ACurrentItem + 0xfb9);
			if (IsSearched >> 7 & 1) continue;

			if (strstr(LEntityList.GNames.c_str(), ("Tiered_Chest")) && options::chest)
			{
				if (ItemDist < 95) {
					Vector3 ChestPosition;
					ChestPosition = Localplayer->W2S(ItemPosition);
					std::string Text = null + ("Chest [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, ChestPosition.x, ChestPosition.y, &Col.orange_, true, true, Text.c_str());
				}
			}

			else if ((options::vehicle && (strstr(LEntityList.GNames.c_str(), ("MeatballVehicle_L_C")))))
			{
				if (ItemDist < 40) {
					Vector3 VehiclePosition = Localplayer->W2S(ItemPosition);
					std::string Text = null + ("Boat [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, VehiclePosition.x, VehiclePosition.y, &Col.white, true, true, Text.c_str());
				}
			}

			else if (options::loot && strstr(LEntityList.GNames.c_str(), ("FortPickupAthena")) || strstr(LEntityList.GNames.c_str(), ("Fort_Pickup_Creative_C")))
			{
				if (ItemDist < 95) {

					auto definition = read<uint64_t>(LEntityList.ACurrentItem + 0x2f8 + 0x18);
					BYTE tier = read<BYTE>(definition + 0x70);

					RGBA Color, RGBAColor;
					Vector3 ChestPosition = Localplayer->W2S(ItemPosition);

					if (options::loot)
					{
						auto DisplayName = read<uint64_t>(definition + 0x90);
						auto WeaponLength = read<uint32_t>(DisplayName + 0x38);
						wchar_t* WeaponName = new wchar_t[uint64_t(WeaponLength) + 1];

						//mem::read_physical((ULONG64)read<PVOID>(DisplayName + 0x30), (uint8_t*)WeaponName, WeaponLength * sizeof(wchar_t));

						std::string Text = wchar_to_char(WeaponName);
						std::string wtf2 = Text + (" [ ") + std::to_string((int)ItemDist) + ("M ]");
						if (tier == 2 && (uncommon))
						{
							Color = Col.darkgreen;
						}
						else if ((tier == 3) && (rare))
						{
							Color = Col.blue;
						}
						else if ((tier == 4) && (epic))
						{
							Color = Col.purple;
						}
						else if ((tier == 5) && (legendary))
						{
							Color = Col.orange;
						}
						else if ((tier == 6) && (mythic))
						{
							Color = Col.yellow;
						}
						else if ((tier == 0) || (tier == 1) && (common))
						{
							Color = Col.gray;
						}

						DrawString(14, ChestPosition.x, ChestPosition.y, &Color, true, true, wtf2.c_str());
					}
				}
			}
		}
	}

	for (unsigned long i = 0; i < player.size(); ++i) {
		AFortPawn* entity = player[i];

		uint64_t mesh = entity->Mesh();

		Vector3 player_screen = Localplayer->W2S(entity->GetBone(0));
		Vector3 BoxHead = entity->GetBone(98);
		Vector3 esp_head_screen = Localplayer->W2S(Vector3(BoxHead.x, BoxHead.y, BoxHead.z + 15));
		uintptr_t CurrentWeapon = read<int64>((uintptr_t)LocalPawn + 0x858);
		Vector3 bone66 = entity->GetBone(66);
		Vector3 Head = Localplayer->W2S(Vector3(bone66.x, bone66.y, bone66.z + 15));
		Vector3 bottom = Localplayer->W2S(entity->GetBone(0));

		float BoxHeight = player_screen.y - esp_head_screen.y;
		float CornerHeight = abs(Head.y - bottom.y);
		float Height1 = abs(Head.y - bottom.y);
		float Width1 = Height1 * 0.80;
		auto Persistentlevel = read<uintptr_t>((uintptr_t)Uworld + 0x30);//Persistentlevel
		uintptr_t AActors = read<uintptr_t>(Persistentlevel + 0x98); //AActors
		int CurrentActor = read<int>(AActors + i * 0x8);
		int curactorid = read<int>(CurrentActor + 0x18);
		float distance = LocalPawn->RootComponent()->RelativeLocation().Distance(bone66) / 100.f;

		static ImColor ESPColor;
		auto IsVisible = entity->isVisible();
		if (IsVisible) { ESPColor = ImColor(0, 255, 0, 255); }
		else { ESPColor = ESPColor = ImColor(255, 0, 0, 255); }
		//ESPColor = ImColor(0, 255, 0, 255);

		auto fname = GetNameFromFName(curactorid);

		if (distance <= options::MaxEspDistance)
		{
			if (options::esp)
			{
				if (options::DistanceEsp)
				{
					char name[64];
					std::string text = name;
					sprintf_s(name, ("                    [%.fm]"), distance);
					DrawString(14, Head.x - 15, Head.y - 5, &Col.white_, true, true, text.c_str());
				}

				//if (options::bot)
				//{
				//	if (strstr(fname.c_str(), ("PlayerPawn_Athena_C")) || strstr(fname.c_str(), ("PlayerPawn_Athena_Phoebe_C")) || strstr(fname.c_str(), ("BP_MangPlayerPawn")))
				//		DrawString(15, bottom.x, bottom.y, &Col.white, true, true, ("BOT/AI"));
				//	else
				//		DrawString(15, bottom.x, bottom.y, &Col.white, true, true, ("PLAYER"));
				//}

				if (options::SnapLines)
				{
					auto ScreenCenterX = (Process::WindowWidth / 2.0f), ScreenCenterY = (Process::WindowHeight / 2.0f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(ScreenCenterX, Process::WindowHeight - 10), ImVec2(bottom.x, bottom.y), ESPColor, options::Thicknessesp);
				}

				if (options::BoxEsp)
				{
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (Width1 / 2), Head.y), ImVec2(bottom.x + (Width1 / 2), bottom.y), ESPColor /*ImColor(94, 23, 235, 255)*/, 0, 0, options::Thicknessbox);
				}

				if (options::filledbox) {
					FilledRect(Head.x - (Width1 / 2), Head.y, Width1, CornerHeight, ESPColor);
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (Width1 / 2), Head.y), ImVec2(bottom.x + (Width1 / 2), bottom.y), ESPColor /*ImColor(94, 23, 235, 255)*/, 0, 0, options::Thicknessbox);
				}

				if (options::cornerbox) { 
					DrawCornerBox(Head.x - (Width1 / 2), Head.y, Width1, CornerHeight, options::Thicknessbox, ESPColor);
				}

				if (options::skeleton) {
					Vector3 vHeadBone = entity->GetBone(68);
					Vector3 vHip = entity->GetBone(2);
					Vector3 vNeck = entity->GetBone(67);
					Vector3 vUpperArmLeft = entity->GetBone(9);
					Vector3 vUpperArmRight = entity->GetBone(38);
					Vector3 vLeftHand = entity->GetBone(10);
					Vector3 vRightHand = entity->GetBone(39);
					Vector3 vLeftHand1 = entity->GetBone(30);
					Vector3 vRightHand1 = entity->GetBone(59);
					Vector3 vRightThigh = entity->GetBone(78);
					Vector3 vLeftThigh = entity->GetBone(71);
					Vector3 vRightCalf = entity->GetBone(79);
					Vector3 vLeftCalf = entity->GetBone(72);
					Vector3 vLeftFoot = entity->GetBone(73);
					Vector3 vRightFoot = entity->GetBone(80);
					Vector3 vHeadBoneOut = Localplayer->W2S(BoxHead);
					Vector3 vHipOut = Localplayer->W2S(vHip);
					Vector3 vNeckOut = Localplayer->W2S(vNeck);
					Vector3 vUpperArmLeftOut = Localplayer->W2S(vUpperArmLeft);
					Vector3 vUpperArmRightOut = Localplayer->W2S(vUpperArmRight);
					Vector3 vLeftHandOut = Localplayer->W2S(vLeftHand);
					Vector3 vRightHandOut = Localplayer->W2S(vRightHand);
					Vector3 vLeftHandOut1 = Localplayer->W2S(vLeftHand1);
					Vector3 vRightHandOut1 = Localplayer->W2S(vRightHand1);
					Vector3 vRightThighOut = Localplayer->W2S(vRightThigh);
					Vector3 vLeftThighOut = Localplayer->W2S(vLeftThigh);
					Vector3 vRightCalfOut = Localplayer->W2S(vRightCalf);
					Vector3 vLeftCalfOut = Localplayer->W2S(vLeftCalf);
					Vector3 vLeftFootOut = Localplayer->W2S(vLeftFoot);
					Vector3 vRightFootOut = Localplayer->W2S(vRightFoot);
					DrawLine(vHeadBoneOut.x, vHeadBoneOut.y, vNeckOut.x, vNeckOut.y, ESPColor, 0.8f);
					DrawLine(vHipOut.x, vHipOut.y, vNeckOut.x, vNeckOut.y, ESPColor, 0.8f);
					DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, ESPColor, 0.8f);
					DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, ESPColor, 0.8f);
					DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, ESPColor, 0.8f);
					DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, ESPColor, 0.8f);
					DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, ESPColor, 0.8f);
					DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, ESPColor, 0.8f);
					DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, ESPColor, 0.8f);
					DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, ESPColor, 0.8f);
					DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, ESPColor, 0.8f);
					DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, ESPColor, 0.8f);
					DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, ESPColor, 0.8f);
					DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, ESPColor, 0.8f);
				}
			}

			Vector3 w2shead = Localplayer->W2S(BoxHead);
			if (options::mouseaimbot) {
				auto dx = w2shead.x - (Process::WindowWidth / 2);
				auto dy = w2shead.y - (Process::WindowHeight / 2);
				auto dist = sqrtf(dx * dx + dy * dy);
				if (dist < options::AimFOV && dist < closestDistance && LocalPawn)
				{
					if (options::vischeck)
					{
						if (entity->isVisible())
						{
							closestDistance = dist;
							closestPawn = entity;
						}
					}
					else
					{
						closestDistance = dist;
						closestPawn = entity;
					}
				}
			}

			//if (options::silent)
			//{
			//	write<Vector3>((uintptr_t)Currentweapon + offset, Vector3(w2shead.x, 0, 0));
			//	write<Vector3>((uintptr_t)Currentweapon + offset, Vector3(w2shead.x, 0, 0));
			//}
		}
	}

	if (options::mouseaimbot)
	{

		if (closestPawn != 0)
		{
			if (closestPawn && GetAsyncKeyState(VK_RBUTTON))
			{
				if (options::mouseaimbot)
				{
					Vector3 hitbone = Localplayer->W2S(closestPawn->GetBone(options::hitbox));

					if (hitbone.x != 0 || hitbone.y != 0 || hitbone.z != 0)
					{
						if ((hitbone.GetDistance(hitbone.x, hitbone.y, hitbone.z, Process::WindowWidth / 2, Process::WindowHeight / 2) <= options::AimFOV))
						{
							aimat(hitbone.x, hitbone.y);
						}
					}
				}
			}
			else
			{
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
		}
	}
}

static int maintabs = 0;

namespace ImGui
{
	IMGUI_API bool Tab(unsigned int index, const char* label, int* selected, float width = 160, float height = 45)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImColor color = ImColor(27, 27, 27, 255)/*style.Colors[ImGuiCol_Button]*/;
		ImColor colortext = ImColor(155, 155, 155, 255)/*style.Colors[ImGuiCol_Text]*/;
		ImColor colortextActive = ImColor(255, 255, 255)/*style.Colors[ImGuiCol_Text]*/;
		ImColor colortextHover = ImColor(255, 255, 255)/*style.Colors[ImGuiCol_Text]*/;
		ImColor colorActive = ImColor(27, 27, 27, 255); /*style.Colors[ImGuiCol_ButtonActive]*/;
		ImColor colorHover = ImColor(27, 27, 27, 255)/*style.Colors[ImGuiCol_ButtonHovered]*/;

		if (index == *selected)
		{
			style.Colors[ImGuiCol_Text] = colortextActive;
			//style.Colors[ImGuiCol_Text] = colortextHover;

			style.Colors[ImGuiCol_Button] = colorActive;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorActive;
		}
		else
		{
			style.Colors[ImGuiCol_Text] = colortext;

			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}

		if (ImGui::Button(label, ImVec2(width, height)))
			*selected = index;

		ImVec2 P1, P2;
		ImDrawList* pDrawList;
		const auto& CurrentWindowPos = ImGui::GetWindowPos();
		const auto& pWindowDrawList = ImGui::GetWindowDrawList();

		if (maintabs == 0)
		{
			P1 = ImVec2(40, 65);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(140, 65);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddLine(P1, P2, ImColor(0, 40, 255, 255), 1);
		}
		if (maintabs == 1)
		{
			P1 = ImVec2(200, 65);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(300, 65);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddLine(P1, P2, ImColor(0, 40, 255, 255), 1);
		}
		if (maintabs == 2)
		{
			P1 = ImVec2(358, 65);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(458, 65);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddLine(P1, P2, ImColor(0, 40, 255, 255), 1);
		}

		style.Colors[ImGuiCol_Text] = colortext;

		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;

		return *selected == index;
	}
}

int current = 1;

ImColor hovered;
ImColor nothovered;

void check()
{
	if (current < 7)
	{
		if (current <= 4)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(7, 40 + current * 17), ImVec2(9, 56 + current * 17), IM_COL32(255, 255, 255, 255));
		}
		else
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(7, 43 + current * 17), ImVec2(9, 59 + current * 17), IM_COL32(255, 255, 255, 255));
		}
	}
	if (current > 7)
	{
		if (current < 10)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(7, 47 + current * 17), ImVec2(9, 63 + current * 17), IM_COL32(255, 255, 255, 255));
		}
		if (current >= 10)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(7, 48 + current * 17), ImVec2(9, 64 + current * 17), IM_COL32(255, 255, 255, 255));
		}
		if (current >= 11)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(7, 49 + current * 17), ImVec2(9, 65 + current * 17), IM_COL32(255, 255, 255, 255));
		}
	}
}

ImColor toggled_aim;
ImColor toggled_fov;
ImColor toggled_crosshair;
ImColor toggled_box;
ImColor toggled_corner;
ImColor toggled_skel;
ImColor toggled_snap;
ImColor toggled_dist;
ImColor toggled_loot;
ImColor toggled_chest;
ImColor toggled_vehicle;
ImColor toggled_currentw;
ImColor toggled_currenta;

void checktoggled()
{
	if (options::mouseaimbot)
	{
		toggled_aim = ImColor(0, 255, 0, 255);
	}
	if (!options::mouseaimbot)
	{
		toggled_aim = ImColor(255, 0, 0, 255);
	}
	if (options::drawfov)
	{
		toggled_fov = ImColor(0, 255, 0, 255);
	}
	if (!options::drawfov)
	{
		toggled_fov = ImColor(255, 0, 0, 255);
	}
	if (options::crosshair)
	{
		toggled_crosshair = ImColor(0, 255, 0, 255);
	}
	if (!options::crosshair)
	{
		toggled_crosshair = ImColor(255, 0, 0, 255);
	}
	if (options::crosshair)
	{
		toggled_crosshair = ImColor(0, 255, 0, 255);
	}
	if (!options::crosshair)
	{
		toggled_crosshair = ImColor(255, 0, 0, 255);
	}
	if (options::BoxEsp)
	{
		toggled_box = ImColor(0, 255, 0, 255);
	}
	if (!options::BoxEsp)
	{
		toggled_box = ImColor(255, 0, 0, 255);
	}
	if (options::cornerbox)
	{
		toggled_corner = ImColor(0, 255, 0, 255);
	}
	if (!options::cornerbox)
	{
		toggled_corner = ImColor(255, 0, 0, 255);
	}
	if (options::skeleton)
	{
		toggled_skel = ImColor(0, 255, 0, 255);
	}
	if (!options::skeleton)
	{
		toggled_skel = ImColor(255, 0, 0, 255);
	}
	if (options::SnapLines)
	{
		toggled_snap = ImColor(0, 255, 0, 255);
	}
	if (!options::SnapLines)
	{
		toggled_snap = ImColor(255, 0, 0, 255);
	}
	if (options::DistanceEsp)
	{
		toggled_dist = ImColor(0, 255, 0, 255);
	}
	if (!options::DistanceEsp)
	{
		toggled_dist = ImColor(255, 0, 0, 255);
	}
	if (options::loot)
	{
		toggled_loot = ImColor(0, 255, 0, 255);
	}
	if (!options::loot)
	{
		toggled_loot = ImColor(255, 0, 0, 255);
	}
	if (options::chest)
	{
		toggled_chest = ImColor(0, 255, 0, 255);
	}
	if (!options::chest)
	{
		toggled_chest = ImColor(255, 0, 0, 255);
	}
	if (options::vehicle)
	{
		toggled_vehicle = ImColor(0, 255, 0, 255);
	}
	if (!options::vehicle)
	{
		toggled_vehicle = ImColor(255, 0, 0, 255);
	}
	if (options::currentweapon)
	{
		toggled_currentw = ImColor(0, 255, 0, 255);
	}
	if (!options::currentweapon)
	{
		toggled_currentw = ImColor(255, 0, 0, 255);
	}
	if (options::currentammo)
	{
		toggled_currenta = ImColor(0, 255, 0, 255);
	}
	if (!options::currentammo)
	{
		toggled_currenta = ImColor(255, 0, 0, 255);
	}
}

void overlay::Render()
{
	//static int tab = 0;

	if (options::crosshair) {
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Process::WindowWidth / 2 - 11, Process::WindowHeight / 2), ImVec2(Process::WindowWidth / 2 + 1, Process::WindowHeight / 2), ImGui::GetColorU32({ options::CrossHair[0], options::CrossHair[1], options::CrossHair[2], 1.0f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Process::WindowWidth / 2 + 12, Process::WindowHeight / 2), ImVec2(Process::WindowWidth / 2 + 1, Process::WindowHeight / 2), ImGui::GetColorU32({ options::CrossHair[0], options::CrossHair[1], options::CrossHair[2], 1.0f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Process::WindowWidth / 2, Process::WindowHeight / 2 - 11), ImVec2(Process::WindowWidth / 2, Process::WindowHeight / 2), ImGui::GetColorU32({ options::CrossHair[0], options::CrossHair[1], options::CrossHair[2], 1.0f }), 1.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Process::WindowWidth / 2, Process::WindowHeight / 2 + 12), ImVec2(Process::WindowWidth / 2, Process::WindowHeight / 2), ImGui::GetColorU32({ options::CrossHair[0], options::CrossHair[1], options::CrossHair[2], 1.0f }), 1.0f);
	}

	if (options::drawfov)
	{
		auto ScreenCenterX = (Process::WindowWidth / 2.0f), ScreenCenterY = (Process::WindowHeight / 2.0f);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(options::AimFOV), ImGui::GetColorU32({ options::DrawFOVCircle[0], options::DrawFOVCircle[1], options::DrawFOVCircle[2], 1.0f }), options::Shape);
	}

	ActorEsp();

	if (GetAsyncKeyState(VK_INSERT) & 1) { ShowMenu = !ShowMenu; }
	if (ShowMenu == true) {

		ImGui::SetNextWindowPos(ImVec2(5, 5));
		ImGui::SetNextWindowSize(ImVec2(200, 600));
		ImGui::Begin(("catware.eu"), nullptr,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoInputs);

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImColor(180, 180, 180, 255);
		colors[ImGuiCol_TextDisabled] = ImColor(180, 180, 180, 255);
		colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 255);
		colors[ImGuiCol_Border] = ImColor(0, 255, 255, 255);
		colors[ImGuiCol_BorderShadow] = ImColor(0, 255, 255, 255);

		checktoggled();

		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(5, 5), ImVec2(205, 30), IM_COL32(2, 185, 255, 255));
		ImGui::GetOverlayDrawList()->AddText(ImVec2(60, 10), IM_COL32(0, 0, 0, 255), ("CatWare Lite"));
		//ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(5, 30), ImVec2(203, 600), IM_COL32(0, 0, 12, 255));;
		ImGui::GetOverlayDrawList()->AddText(ImVec2(8, 38), IM_COL32(2, 185, 255, 255), ("Aimbot"));



		check();


		ImGui::SetCursorPos(ImVec2(170, 45 + 15 * 4));
		ImGui::Text(("   %i"), options::mousesmoothness);
		ImGui::SetCursorPos(ImVec2(160, 43 + 16 * 5));
		ImGui::Text(("   %i"), options::AimFOV);
		if (AimboneInt == 0)
		{
			options::hitbox = 68;
			ImGui::SetCursorPos(ImVec2(150, 39 + 17 * 6));
			ImGui::Text(("    Head"), options::hitbox);
		}
		else if (AimboneInt == 1)
		{
			options::hitbox = 67;
			ImGui::SetCursorPos(ImVec2(150, 39 + 17 * 6));
			ImGui::Text(("    Neck"), options::hitbox);
		}
		else if (AimboneInt == 2)
		{
			options::hitbox = 7;
			ImGui::SetCursorPos(ImVec2(144, 39 + 17 * 6));
			ImGui::Text(("     Chest"), options::hitbox);
		}
		else if (AimboneInt == 3)
		{
			options::hitbox = 3;
			ImGui::SetCursorPos(ImVec2(138, 39 + 17 * 6));
			ImGui::Text(("       Pelvis"), options::hitbox);
		}



		//ImGui::GetOverlayDrawList()->AddText(ImVec2(13, 110 + 18 * 5), IM_COL32(255, 255, 255, 255), ("abdail"));

		ImGui::End();


		if (GetAsyncKeyState(VK_DOWN) & 1) {
			current += 1;
			if (current == 7) {
				current = 8;
			}
			if (current == 14) {
				current = 1;
			}
		}

		if (GetAsyncKeyState(VK_UP) & 1) {
			current -= 1;
			if (current == 0) {
				current = 13;
			}
			if (current == 7) {
				current = 6;
			}
		}

		if (GetAsyncKeyState(VK_RETURN) & 1) {
			if (current == 1) {
				options::mouseaimbot = !options::mouseaimbot;
			}
			if (current == 2) {
				options::drawfov = !options::drawfov;
			}
			if (current == 3) {
				options::crosshair = !options::crosshair;
			}
			if (current == 8) {
				options::BoxEsp = !options::BoxEsp;
			}
			if (current == 9) {
				options::cornerbox = !options::cornerbox;
			}
			if (current == 10) {
				options::skeleton = !options::skeleton;
			}
			if (current == 11) {
				options::SnapLines = !options::SnapLines;
			}
			if (current == 12) {
				options::DistanceEsp = !options::DistanceEsp;
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 1) {
			if (current == 4) {
				if (options::mousesmoothness == 3) {

				}
				else {
					options::mousesmoothness += -1;
				}
			}
			if (current == 5) {
				if (options::AimFOV == 50) {

				}
				else {
					options::AimFOV -= 10;
				}
			}
			if (current == 13)
			{
				if (options::MaxEspDistance == 100) {

				}
				else {
					options::MaxEspDistance -= 25;
				}
			}
			if (current == 6)
			{
				if (AimboneInt == 0) {

				}
				else {
					AimboneInt -= 1;
				}
			}
		}

		if (GetAsyncKeyState(VK_RIGHT) & 1) {
			if (current == 4) {
				if (options::mousesmoothness == 3) {
					options::mousesmoothness += 1;
				}
				if (options::mousesmoothness == 12)
				{
					
				}
				else {
					options::mousesmoothness += 1;
				}
			}
			if (current == 5) {
				if (options::AimFOV == 50) {
					options::AimFOV += 10;
				}
				if (options::AimFOV == 300) {

				}
				else {
					options::AimFOV += 10;
				}
			}
			if (current == 13)
			{
				if (options::MaxEspDistance == 300) {

				}
				else {
					options::MaxEspDistance += 25;
				}
			}
			if (current == 6)
			{
				if (AimboneInt == 3) {

				}
				else {
					AimboneInt += 1;
				}
			}
		}




int main() {
	if (CreateConsole == false)
		ShowWindow(GetConsoleWindow(), SW_HIDE);

	pid_Drv = GetProcessId(TargetProcess);


	if (!mem::find_driver()) {
		MessageBoxA(0, "fail", 0, 0);
	}

	base_Drv = mem::find_image();

	std::cout << std::hex << base_Drv << std::endl;

	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drawLoop), nullptr, NULL, nullptr);

	InitOverlay();
}
