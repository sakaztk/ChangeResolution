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
	wcout << "Usage:" << endl;
	wcout << "  " << szFName << " [-list] | [-name] | [-current] | WIDTH HEIGHT | NAME" << endl;
	wcout << endl;
	wcout << "Examples:" << endl;
	wcout << "  " << szFName << " -l        # Show the available resolutions." << endl;
	wcout << "  " << szFName << " -n        # Show the defined resolution names." << endl;
	wcout << "  " << szFName << " -c        # Show the current resolution." << endl;
	wcout << "  " << szFName << " 1024 768  # Change the resolution to 1024x768." << endl;
	wcout << "  " << szFName << " SXGA      # Change the resolution to SXGA." << endl;
	wcout << "  " << szFName << " MAX       # Change the resolution to maximum." << endl;

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
			wcout << width << "x" << height << endl;
			lastW = width;
			lastH = height;
		}
		i++;
	}
}
void ShowName()
{
	DEVMODE ExistDisplayMode;
	int i = 0;
	while (EnumDisplaySettings(NULL, i, &ExistDisplayMode))
	{
		i++;
	}
	int width = ExistDisplayMode.dmPelsWidth;
	int height = ExistDisplayMode.dmPelsHeight;

	wcout << "Name    Resolution" << endl;
	wcout << "======  ==========" << endl;
	wcout << "CGA     320x200" << endl;
	wcout << "EGA     640x350" << endl;
	wcout << "DCGA    640x400" << endl;
	wcout << "SVGA    800x600" << endl;
	wcout << "XGA     1024x768" << endl;
	wcout << "HD      1280x720" << endl;
	wcout << "FWXGA   1366x768" << endl;
	wcout << "SXGA    1280x1024" << endl;
	wcout << "XGA++   1600x900" << endl;
	wcout << "UXGA    1600x1200" << endl;
	wcout << "FHD     1920x1080" << endl;
	wcout << "WUXGA   1920x1200" << endl;
	wcout << "WQHD    2560x1440" << endl;
	wcout << "WQXGA   2560x1600" << endl;
	wcout << "4K      3840x2160" << endl;
	wcout << "------  ----------" << endl;
	wcout << "MAX     " << width << "x" << height << endl;
}

bool ShowCurrent()
{
	DEVMODE deviceMode = { 0 };
	deviceMode.dmSize = sizeof(deviceMode);
	deviceMode.dmDriverExtra = 0;
	if (EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &deviceMode, 0))
	{
		cout << deviceMode.dmPelsWidth << "x" << deviceMode.dmPelsHeight << endl;
	}
	else
	{
		cout << "Failed to get current resolution." << endl;
		return false;
	}
	return true;
}

bool is_option(char *cstr, string option)
{
	string str = cstr;
	transform(str.begin(), str.end(), str.begin(), toupper);
	transform(option.begin(), option.end(), option.begin(), toupper);
	for (int i = 0; i<(int)str.size(); i++)
	{
		if (!(str[i] == option[i]))
		{
			return false;
		}
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
		transform(str.begin(), str.end(), str.begin(), toupper);

		if (is_option(arg, "-help") || is_option(arg, "/help") || is_option(arg, "-?") || is_option(arg, "/?"))
		{
			ShowHelp(argv);
			exit(0);
		}
		else if (is_option(arg, "-list") || is_option(arg, "/list"))
		{
			ShowList();
			exit(0);
		}
		else if (is_option(arg, "-name") || is_option(arg, "/name"))
		{
			ShowName();
			exit(0);
		}
		else if (is_option(arg, "-current") || is_option(arg, "/current") || is_option(arg, "-now") || is_option(arg, "/now"))
		{
			ShowCurrent();
			exit(0);
		}
		else if (str == "CGA")
		{
			*width = 320; *height = 200;
		}
		else if (str == "EGA")
		{
			*width = 640; *height = 350;
		}
		else if (str == "DCGA")
		{
			*width = 640; *height = 400;
		}
		else if (str == "VGA")
		{
			*width = 640; *height = 480;
		}
		else if (str == "SVGA")
		{
			*width = 800; *height = 600;
		}
		else if (str == "XGA")
		{
			*width = 1024; *height = 768;
		}
		else if ((str == "HD") || (str == "HD720") || (str == "720P") || (str == "HD720P"))
		{
			*width = 1280; *height = 720;
		}
		else if (str == "FWXGA")
		{
			*width = 1366; *height = 768;
		}
		else if (str == "SXGA")
		{
			*width = 1280; *height = 1024;
		}
		else if (str == "XGA++")
		{
			*width = 1600; *height = 900;
		}
		else if (str == "UXGA")
		{
			*width = 1600; *height = 1200;
		}
		else if ((str == "FHD") || (str == "FULLHD") || (str == "FULL-HD") || (str == "HD1080") || (str == "1080P"))
		{
			*width = 1920; *height = 1080;
		}
		else if (str == "WUXGA")
		{
			*width = 1920; *height = 1200;
		}
		else if (str == "WQHD")
		{
			*width = 2560; *height = 1440;
		}
		else if (str == "WQXGA")
		{
			*width = 2560; *height = 1600;
		}
		else if ((str == "4K") || (str == "QFHD"))
		{
			*width = 3840; *height = 2160;
		}
		else if (str == "MAX")
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
		cout << "Invalid Argument(s)." << endl << endl;
		//ShowHelp(argv);
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
				cout << "Succeeded: " << newWidth << "x" << newHeight << endl;
			}
			else
			{
				cout << "Failed: " << newWidth << "x" << newHeight << endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			cout << "Already Same Resolution: " << newWidth << "x" << newHeight << endl;
		}
	}
	return EXIT_SUCCESS;
}

