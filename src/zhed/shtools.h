/*
zhed - Free hex editor based on Frhed
Copyright (C) 2000 Raihan Kibria
Copyright (C) 2016 Kevin Mullins

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

Last change: 2013-02-24 by Jochen Neubeck
*/
/** 
 * @file  shtools.h
 *
 * @brief Declaration of Shell api tool functions.
 *
 */
#ifndef _SHTOOLS_H_
#define _SHTOOLS_H_

STDAPI CreateLink(LPCTSTR lpszPathObj, LPCTSTR lpszPathLink);
STDAPI CreateLinkToMe(LPCTSTR lpszPathLink);
STDAPI ResolveIt(HWND hwnd, LPCTSTR lpszLinkFile, LPTSTR lpszPath);
STDAPI PathsEqual(LPCTSTR, LPCTSTR);
STDAPI PathPointsToMe(LPCTSTR);
STDAPI CreateShellCommand(LPCTSTR);
STDAPI GetLongPathNameWin32(LPCTSTR lpszShortPath, LPTSTR lpszLongPath);

#endif // _SHTOOLS_H_


