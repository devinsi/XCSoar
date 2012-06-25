/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "ConvertString.hpp"

#ifdef _UNICODE
#include <windows.h>

static TCHAR *
ConvertToWide(const char *p, UINT codepage)
{
  assert(p != NULL);

  int length = MultiByteToWideChar(codepage, 0, p, -1, NULL, 0);
  if (length <= 0)
    return NULL;

  TCHAR *buffer = new TCHAR[length];
  length = MultiByteToWideChar(codepage, 0, p, -1, buffer, length);
  if (length <= 0) {
    delete[] buffer;
    return NULL;
  }

  return buffer;
}

TCHAR *
ConvertUTF8ToWide(const char *p)
{
  return ConvertToWide(p, CP_UTF8);
}

TCHAR *
ConvertACPToWide(const char *p)
{
  return ConvertToWide(p, CP_ACP);
}

static char *
ConvertFromWide(const TCHAR *p, UINT codepage)
{
  assert(p != NULL);

  int length = WideCharToMultiByte(codepage, 0, p, -1, NULL, 0, NULL, NULL);
  if (length <= 0)
    return NULL;

  char *buffer = new char[length];
  length = WideCharToMultiByte(codepage, 0, p, -1, buffer, length, NULL, NULL);
  if (length <= 0) {
    delete[] buffer;
    return NULL;
  }

  return buffer;
}

char *
ConvertWideToUTF8(const TCHAR *p)
{
  return ConvertFromWide(p, CP_UTF8);
}

char *
ConvertWideToACP(const TCHAR *p)
{
  return ConvertFromWide(p, CP_ACP);
}

#endif
