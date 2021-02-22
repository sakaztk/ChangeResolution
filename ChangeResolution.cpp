#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>

using namespace std;

static void ShowHelp(char **argv)
{
	TCHAR szPath[_MAX_PATH];
	TCHAR szDir[_MAX_DIR];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szFName[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	_tsplitpath_s(szPath, szDrive, szDir, szFName, szExt);
	::wcout << "Usage:" << ::endl;
	::wcout << "  " << szFName << " [-list] | [-name] | [-current] | WIDTH HEIGHT | NAME" << ::endl;
	::wcout << ::endl;
	::wcout << "Options:" << ::endl;
	::wcout << "  -c, --current #Show the current resolution." << ::endl;
	::wcout << "  -l, --list    #Show the available resolutions." << ::endl;
	::wcout << "  -n, --name    #Show the defined resolution names." << ::endl;
	::wcout << "  WIDTH HEIGHT  #Change the resolution to WIDTH x HEIGHT." << ::endl;
	::wcout << "  NAME          #Change the resolution to NAME." << ::endl;
	::wcout << ::endl;
	::wcout << "Examples:" << ::endl;
	::wcout << "  " << szFName << " 1024 768  #Change the resolution to 1024x768." << ::endl;
	::wcout << "  " << szFName << " SXGA      #Change the resolution to SXGA." << ::endl;
	::wcout << "  " << szFName << " MAX       #Change the resolution to maximum possible." << ::endl;
}

void ShowList()
{
	DEVMODE ExistDisplayMode;
	int i = 0;
	int	height = 0;
	int	width = 0;
	int lastH = 0;
	int lastW = 0;

	while (EnumDisplaySettings(NULL, i, &ExistDisplayMode))
	{
		height = ExistDisplayMode.dmPelsHeight;
		width = ExistDisplayMode.dmPelsWidth;
		if ((lastH != height) && (lastW != width))
		{
			::wcout << width << "x" << height << ::endl;
			lastW = width;
			lastH = height;
		}
		i++;
	}
}
void ShowName()
{
	DEVMODE ExistDisplayMode;
	/*
	int i = 0;
	while (EnumDisplaySettings(NULL, i, &ExistDisplayMode))
	{
		i++;
	}
	*/
	EnumDisplaySettings(NULL, 0, &ExistDisplayMode);
	int width = ExistDisplayMode.dmPelsWidth;
	int height = ExistDisplayMode.dmPelsHeight;

	::wcout << "Name    Resolution" << ::endl;
	::wcout << "======  ==========" << ::endl;
	::wcout << "CGA     320x200" << ::endl;
	::wcout << "EGA     640x350" << ::endl;
	::wcout << "DCGA    640x400" << ::endl;
	::wcout << "SVGA    800x600" << ::endl;
	::wcout << "XGA     1024x768" << ::endl;
	::wcout << "HD      1280x720" << ::endl;
	::wcout << "FWXGA   1366x768" << ::endl;
	::wcout << "SXGA    1280x1024" << ::endl;
	::wcout << "XGA++   1600x900" << ::endl;
	::wcout << "UXGA    1600x1200" << ::endl;
	::wcout << "FHD     1920x1080" << ::endl;
	::wcout << "WUXGA   1920x1200" << ::endl;
	::wcout << "WQHD    2560x1440" << ::endl;
	::wcout << "WQXGA   2560x1600" << ::endl;
	::wcout << "QSXGA   2560x2048" << ::endl;
	::wcout << "QHD+    3200x1800" << ::endl;
	::wcout << "WQSXGA  3200x2048" << ::endl;
	::wcout << "QUXGA   3200x2400" << ::endl;
	::wcout << "4K      3840x2160" << ::endl;
	::wcout << "WQUXGA  3840x2400" << ::endl;
	::wcout << "5K      5120x2880" << ::endl;
	::wcout << "8K      7680x4320" << ::endl;
	::wcout << "16K     17280x4320" << ::endl;
	::wcout << "------  ----------" << ::endl;
	::wcout << "MAX     " << width << "x" << height << ::endl;
}

bool ShowCurrent()
{
	DEVMODE deviceMode = { 0 };
	deviceMode.dmSize = sizeof(deviceMode);
	deviceMode.dmDriverExtra = 0;
	if (EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &deviceMode, 0))
	{
		::wcout << deviceMode.dmPelsWidth << "x" << deviceMode.dmPelsHeight << ::endl;
	}
	else
	{
		::wcerr << "Failed to get current resolution." << ::endl;
		return false;
	}
	return true;
}

static BOOL ParseArgs(int argc, char **argv, int *width, int *height)
{
	char *arg = NULL;
	int n = 0;
	string str;

	if (width == NULL || height == NULL)
	{
		return FALSE;
	}
	if (argc == 1)
	{
		ShowHelp(argv);
		exit(0);
	}
	else if (argc == 2)
	{
		arg = argv[1];
		str = arg;
		string p = argv[1];
		transform(p.begin(), p.end(), p.begin(), toupper);

		if (p == "-?" || p == "/?" || p == "-H" || p == "/H" || p == "--HELP" || p == "/HELP")
		{
			ShowHelp(argv);
			exit(0);
		}
		else if (p == "-L" || p == "/L" || p == "--LIST" || p == "/LIST")
		{
			ShowList();
			exit(0);
		}
		else if (p == "-N" || p == "/N" || p == "--NAME" || p == "/NAME")
		{
			ShowName();
			exit(0);
		}
		else if (p == "-C" || p == "/C" || p == "--CURRENT" || p == "/CURRENT" || p == "--NOW" || p == "/NOW")
		{
			ShowCurrent();
			exit(0);
		}
		else if (p == "CGA")
		{
			*width = 320; *height = 200;
		}
		else if (p == "EGA")
		{
			*width = 640; *height = 350;
		}
		else if (p == "DCGA")
		{
			*width = 640; *height = 400;
		}
		else if (p == "VGA")
		{
			*width = 640; *height = 480;
		}
		else if (p == "SVGA")
		{
			*width = 800; *height = 600;
		}
		else if (p == "XGA")
		{
			*width = 1024; *height = 768;
		}
		else if ((p == "HD") || (p == "HD720") || (p == "720P") || (p == "HD720P"))
		{
			*width = 1280; *height = 720;
		}
		else if (p == "FWXGA")
		{
			*width = 1366; *height = 768;
		}
		else if (p == "SXGA")
		{
			*width = 1280; *height = 1024;
		}
		else if (p == "XGA++")
		{
			*width = 1600; *height = 900;
		}
		else if (p == "UXGA")
		{
			*width = 1600; *height = 1200;
		}
		else if ((p == "FHD") || (p == "FULLHD") || (p == "FULL-HD") || (p == "HD1080") || (p == "1080P"))
		{
			*width = 1920; *height = 1080;
		}
		else if (p == "WUXGA")
		{
			*width = 1920; *height = 1200;
		}
		else if (p == "WQHD")
		{
			*width = 2560; *height = 1440;
		}
		else if (p == "WQXGA")
		{
			*width = 2560; *height = 1600;
		}
		else if (p == "QSXGA")
		{
			*width = 2560; *height = 2048;
		}
		else if (p == "QHD+")
		{
			*width = 3200; *height = 1800;
		}
		else if (p == "WQSXGA")
		{
			*width = 3200; *height = 2048;
		}
		else if (p == "QUXGA")
		{
			*width = 3200; *height = 2400;
		}
		else if ((p == "4K") || (p == "QFHD"))
		{
			*width = 3840; *height = 2160;
		}
		else if (p == "WQUXGA")
		{
			*width = 3840; *height = 2400;
		}
		else if (p == "5K")
		{
			*width = 5120; *height = 2880;
		}
		else if (p == "8K")
		{
		*width = 7680; *height = 4320;
		}
		else if (p == "16K")
		{
		*width = 17280; *height = 4320;
		}
		else if (p == "MAX")
		{
			DEVMODE ExistDisplayMode;
			int i = 0;
			while (EnumDisplaySettings(NULL, i, &ExistDisplayMode))
			{
				i++;
			}
			*width = ExistDisplayMode.dmPelsWidth;
			*height = ExistDisplayMode.dmPelsHeight;
		}
		else
		{
			return FALSE;
		}
	}
	else if (argc == 3)
	{
		arg = argv[1];
		n = atoi(arg);
		if (n <= 0) {
			return FALSE;
		}
		*width = n;

		arg = argv[2];
		n = atoi(arg);
		if (n <= 0) {
			return FALSE;
		}
		*height = n;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

int main(int argc, char **argv)
{
	DEVMODE deviceMode = { 0 };
	int	newWidth = 0;
	int	newHeight = 0;
	int	currentWidth = 0;
	int	currentHeight = 0;

	if (!ParseArgs(argc, argv, &newWidth, &newHeight))
	{
		::wcerr << "Invalid Argument(s)." << ::endl << ::endl;
		return EXIT_FAILURE;
	}
	deviceMode.dmSize = sizeof(deviceMode);
	deviceMode.dmDriverExtra = 0;
	if (EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &deviceMode, 0))
	{
		currentWidth = deviceMode.dmPelsWidth;
		currentHeight = deviceMode.dmPelsHeight;
		if ((currentWidth != newWidth) || (currentHeight != newHeight))
		{
			deviceMode.dmPelsWidth = newWidth;
			deviceMode.dmPelsHeight = newHeight;
			if (ChangeDisplaySettingsEx(NULL, &deviceMode, NULL, 0, NULL) == DISP_CHANGE_SUCCESSFUL)
			{
				SendMessage(HWND_BROADCAST, WM_DISPLAYCHANGE, (WPARAM)(deviceMode.dmBitsPerPel), MAKELPARAM(newWidth, newHeight));
				::wcout << "Succeeded: " << newWidth << "x" << newHeight << ::endl;
			}
			else
			{
				::wcerr << "Failed: " << newWidth << "x" << newHeight << ::endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			::wcout << "Already Same Resolution: " << newWidth << "x" << newHeight << ::endl;
		}
	}
	return EXIT_SUCCESS;
}