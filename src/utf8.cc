// This file is part of Extract PDFmark.
//
// Copyright (C) 2016 Masamichi Hosoda
//
// Extract PDFmark is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Extract PDFmark is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include "utf8.hh"

#ifdef HAVE_CODECVT
#include <cwchar>
#include <codecvt>
#endif

#include <string>

#ifdef HAVE_CODECVT

bool is_utf8 (const std::string &str)
{
  std::codecvt_utf8<char32_t> cvt;
  auto mb {std::mbstate_t ()};
  return (cvt.length (mb, &str.front (), &str.front () + str.length (),
                      std::string::npos)
          == str.length ());
}

#else  // HAVE_CODECVT

bool is_utf8 (const std::string &str)
{
  return false;
}

#endif  // HAVE_CODECVT
