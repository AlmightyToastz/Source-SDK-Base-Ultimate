#include "cbase.h"
#include "SteamCommon.h"
#ifdef CLIENT_DLL
#include "clientsteamcontext.h"
#endif
#include "filesystem.h"
#include "fmtstr.h"

#include "content_mounter.h"

#include "ienginevgui.h"
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>
#include <vgui/ILocalize.h>
#include "icommandline.h"
#include "tier3/tier3.h"

void AddPlatform(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/platform", path), "PLATFORM", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/platform/platform_misc.vpk", path), "PLATFORM", PATH_ADD_TO_HEAD);
}

void AddCSS(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/cstrike", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/cstrike/cstrike_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddDOD(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/dod", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/dod/dod_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddEP1(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/episodic", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/episodic/ep1_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddEP2(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/ep2", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/ep2/ep2_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddHL1(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl1", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/hl1/hl1_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddHL1MP(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl1mp", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/hl1mp/hl1mp_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddHL2(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl2", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/hl2/hl2_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddHL2MP(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/hl2mp", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/hl2mp/hl2mp_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddLostCoast(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/lostcoast", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/lostcoast/lostcoast_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void AddPortal(const char* path)
{
	filesystem->AddSearchPath(CFmtStr("%s/portal", path), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/portal/portal_pak.vpk", path), "GAME", PATH_ADD_TO_HEAD);
}

void MountExtraContent()
{
	KeyValuesAD gameinfo("GameInfo");
	gameinfo->LoadFromFile(filesystem, "gameinfo.txt");

	if (steamapicontext->SteamApps()->BIsAppInstalled(243730))
	{
		char sdk2013SPPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(243730, sdk2013SPPath, sizeof(sdk2013SPPath));

		if (gameinfo->GetBool("hl2content") || gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content"))
			AddHL2(sdk2013SPPath);

		if (gameinfo->GetBool("ep2content") || gameinfo->GetBool("ep1content"))
			AddEP1(sdk2013SPPath);

		if (gameinfo->GetBool("ep2content"))
			AddEP2(sdk2013SPPath);

		if (gameinfo->GetBool("lostcoastcontent"))
			AddLostCoast(sdk2013SPPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(243750))
	{
		char sdk2013MPPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(243750, sdk2013MPPath, sizeof(sdk2013MPPath));
		AddPlatform(sdk2013MPPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(243750) && gameinfo->GetBool("hl2mpcontent"))
	{
		char sdk2013MPPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(243750, sdk2013MPPath, sizeof(sdk2013MPPath));
		AddHL2(sdk2013MPPath);
		AddHL2MP(sdk2013MPPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(240) && gameinfo->GetBool("csscontent"))
	{
		char cssPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(240, cssPath, sizeof(cssPath));
		AddCSS(cssPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(300) && gameinfo->GetBool("dodcontent"))
	{
		char dodPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(300, dodPath, sizeof(dodPath));
		AddDOD(dodPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(380) && (gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content")))
	{
		char ep1Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(380, ep1Path, sizeof(ep1Path));
		AddEP1(ep1Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(420) && gameinfo->GetBool("ep2content"))
	{
		char ep2Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(420, ep2Path, sizeof(ep2Path));
		AddEP2(ep2Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(280) && gameinfo->GetBool("hl1content"))
	{
		char hl1Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(280, hl1Path, sizeof(hl1Path));
		AddHL1(hl1Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(360) && gameinfo->GetBool("hl1mpcontent"))
	{
		char hl1mpPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(360, hl1mpPath, sizeof(hl1mpPath));
		AddHL1(hl1mpPath);
		AddHL1MP(hl1mpPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(220) && (gameinfo->GetBool("hl2content") || gameinfo->GetBool("ep1content") || gameinfo->GetBool("ep2content")))
	{
		char hl2Path[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(220, hl2Path, sizeof(hl2Path));
		AddHL2(hl2Path);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(320) && gameinfo->GetBool("hl2mpcontent"))
	{
		char hl2mpPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(320, hl2mpPath, sizeof(hl2mpPath));
		AddHL2(hl2mpPath);
		AddHL2MP(hl2mpPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(340) && gameinfo->GetBool("lostcoastcontent"))
	{
		char lostCoastPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(340, lostCoastPath, sizeof(lostCoastPath));
		AddLostCoast(lostCoastPath);
	}

	if (steamapicontext->SteamApps()->BIsAppInstalled(400) && gameinfo->GetBool("portalcontent"))
	{
		char portalPath[MAX_PATH];
		steamapicontext->SteamApps()->GetAppInstallDir(400, portalPath, sizeof(portalPath));
		AddPortal(portalPath);
	}

	filesystem->AddSearchPath(CFmtStr("%s", CommandLine()->ParmValue("-game")), "GAME", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s", CommandLine()->ParmValue("-game")), "MOD", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s", CommandLine()->ParmValue("-game")), "MOD_WRITE", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s", CommandLine()->ParmValue("-game")), "DEFAULT_WRITE_PATH", PATH_ADD_TO_HEAD);
	filesystem->AddSearchPath(CFmtStr("%s/bin", CommandLine()->ParmValue("-game")), "GAMEBIN", PATH_ADD_TO_HEAD);
}