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
 * @file Constants.h
 *
 * @brief zhed constants, URLs, paths etc.
 *
 */

/** @brief Application name used in the GUI. */
const TCHAR ApplicationName[] = _T("zhed");

/** @brief zhed homepage URL. */
const TCHAR ZhedHomepageURL[] = _T("https://github.com/zyzil/zhed");

/** @brief Filename of the contributors list. */
const TCHAR ContributorsList[] = _T("Docs\\Contributors.txt");

/** @brief HtmlHelp file to open from zhed program folder. */
const TCHAR HtmlHelpFile[] = _T("docs\\zhed.chm");

/** @brief Registry key for zhed. */
const TCHAR OptionsRegistryPath[] = _T("Software\\zhed");

/** @brief Registry key for zhed settings. */
const TCHAR OptionsRegistrySettingsPath[] = _T("Software\\zhed\\Settings");

/** @brief Subfolder where language files (PO files) are. */
const WCHAR LangFileSubFolder[] = L"Languages";
