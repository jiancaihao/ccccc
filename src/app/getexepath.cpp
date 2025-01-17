/*
** Copyright 2012-2022 Joris Dauphin
*/
/*
**  This file is part of CCCCC.
**
**  CCCCC is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  CCCCC is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with CCCCC. If not, see <http://www.gnu.org/licenses/>.
*/

#include "getexepath.h"

#ifdef _WIN32

# include <windows.h>

std::filesystem::path getExePath()
{
	char ownPth[MAX_PATH];
	HMODULE hModule = GetModuleHandle(nullptr);

	if (hModule != nullptr) {
		GetModuleFileName(hModule, ownPth, sizeof(ownPth));
	}
	return std::filesystem::path(ownPth).parent_path();
}

#elif defined(__linux__) || defined(__unix__)

# include <climits>
# include <unistd.h>

std::filesystem::path getExePath()
{
	char buff[PATH_MAX];

	const auto len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
	if (len != -1) {
		buff[len] = '\0';
		return buff;
	}
	return {};
}
#else

//Mac OS X: _NSGetExecutablePath() (man 3 dyld)
//Linux: readlink /proc/self/exe
//Solaris: getexecname()
//FreeBSD: sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
//BSD with procfs: readlink /proc/curproc/file

std::filesystem::path getExePath()
{
# warning "platform not supported: getExePath will return empty"
	return std::string();
}

#endif
