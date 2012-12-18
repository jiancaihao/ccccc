/*
** Copyright 2012 Joris Dauphin
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

#include "funcstattool.h"

#include "localstattool.h"

namespace ccccc
{
namespace use_clang
{

void FuncStatTool::Compute(const CXTranslationUnit& tu, const CXCursor& cursor, FuncStat* stat)
{
	LocalStatTool::Compute(tu, cursor, &stat->m_lineCount);
}

} // namespace use_clang
} // namespace ccccc
