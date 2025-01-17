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

#ifndef FILE_STAT_H
#define FILE_STAT_H

#include "funcstat.h"
#include "linecount.h"
#include "namespacestat.h"

#include <filesystem>
#include <string>
#include <vector>

namespace ccccc
{
namespace use_clang
{
class FileStatTool;
} // namespace use_clang

class FileStat
{
	friend class use_clang::FileStatTool;

public:
	using NamespaceMap = NamespaceStat::NamespaceMap;
	using ClassMap = NamespaceStat::ClassMap;

public:
	explicit FileStat(const std::filesystem::path& filename);
	~FileStat();

	const std::filesystem::path& getFilename() const { return m_filename; }
	const LineCount& getLineCount() const { return m_lineCount; }
	unsigned int getFunctionCount() const { return m_root.getFunctionCount(); }
	const FuncStat& getFuncStat(unsigned int index) const { return m_root.getFuncStat(index); }
	const FuncStat* getFuncStatByName(const char* funcNameId) const
	{
		return m_root.getFuncStatByName(funcNameId);
	}

	unsigned int getNamespaceCount() const { return m_root.getNamespaceCount(); }
	const NamespaceMap& getNamespaces() const { return m_root.getNamespaces(); }
	const NamespaceStat* getNamespaceByName(const char* name) const
	{
		return m_root.getNamespaceByName(name);
	}

	unsigned int getClassCount() const { return m_root.getClassCount(); }
	const ClassMap& getClasses() const { return m_root.getClasses(); }
	const ClassStat* getClassByName(const char* name) const { return m_root.getClassByName(name); }

private:
	FuncStat* AddFuncStat(const std::vector<std::string>& namespaceNames,
	                      const std::vector<std::string>& classeNames,
	                      const std::string& funcname,
	                      unsigned int line);
	NamespaceStat* AddNamespace(const std::string& name);

private:
	std::filesystem::path m_filename;
	LineCount m_lineCount;
	NamespaceStat m_root;
};

} // namespace ccccc

#endif // FILE_STAT_H
