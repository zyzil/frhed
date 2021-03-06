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
 * @file  hexeditctl.h
 *
 * @brief Interface definition for the hexeditctlor window.
 *
 */
#ifndef _hexeditctl_H_
#define _hexeditctl_H_

#ifndef hexeditctl_INTERFACE_VERSION
#define hexeditctl_INTERFACE_VERSION 2
#endif

/**
 * @brief Interface for the Hexeditor window.
 * @note This file is published to hosting applications. Do not add global declarations.
 */
class IHexEditorWindow
{
public:
	/**
	 * @brief Byte endians.
	 */
	enum BYTE_ENDIAN
	{
		ENDIAN_LITTLE, /**< Little endian used e.g. in Intel processors. */
		ENDIAN_BIG /**< Big endian used e.g. in Motorola processors. */
	};

	struct Colors
	{
		COLORREF iTextColorValue, iBkColorValue, iSepColorValue;
		COLORREF iSelBkColorValue, iSelTextColorValue;
		COLORREF iBmkColor;
		COLORREF iDiffBkColorValue, iDiffTextColorValue, iSelDiffBkColorValue, iSelDiffTextColorValue;
	};

	/** @brief zhed settings. */
	struct Settings
	{
		int iBytesPerLine; /**< How many bytes in one line in hex view. */
		int iAutomaticBPL; /**< Add max amount of bytes that fit to view. */
		BYTE_ENDIAN iBinaryMode; /**< Binary mode, little/big endian. */
		int bReadOnly; /**< Is editor in read-only mode? */
		int bSaveIni; /**< Save INI file when required. */
		int iFontSize;
		int iCharacterSet; /**< Use OEM or ANSI character set? */
		int iMinOffsetLen; /**< Minimum numbers used in offset. */
		int iMaxOffsetLen; /**< Maximum numbers used in offset. */
		int bAutoOffsetLen; /**< Determine offset length automatically. */
		int bCenterCaret;
		int iFontZoom;
	};

	struct Status
	{
		int iEnteringMode;
		int iCurByte;
		int iCurNibble;
		int iVscrollMax;
		int iVscrollPos;
		int iHscrollMax;
		int iHscrollPos;
		bool bSelected;
		int iStartOfSelection;
		int iEndOfSelection;
	};

	virtual unsigned STDMETHODCALLTYPE get_interface_version() = 0;
	virtual unsigned char*STDMETHODCALLTYPE get_buffer(int) = 0;
	virtual int STDMETHODCALLTYPE get_length() = 0;
	virtual void STDMETHODCALLTYPE set_sibling(IHexEditorWindow*) = 0;
	virtual Colors*STDMETHODCALLTYPE get_colors() = 0;
	virtual Settings*STDMETHODCALLTYPE get_settings() = 0;
	virtual Status*STDMETHODCALLTYPE get_status() = 0;
	virtual void STDMETHODCALLTYPE resize_window() = 0;
	virtual void STDMETHODCALLTYPE repaint(int from, int to) = 0;
	virtual void STDMETHODCALLTYPE adjust_hscrollbar() = 0;
	virtual void STDMETHODCALLTYPE adjust_vscrollbar() = 0;
	virtual int STDMETHODCALLTYPE translate_accelerator(MSG*) = 0;
	virtual void STDMETHODCALLTYPE CMD_find() = 0;
	virtual void STDMETHODCALLTYPE CMD_findprev() = 0;
	virtual void STDMETHODCALLTYPE CMD_findnext() = 0;
	virtual void STDMETHODCALLTYPE CMD_replace() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_cut() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_copy() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_paste() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_clear() = 0;
	virtual BOOL STDMETHODCALLTYPE select_next_diff(BOOL bFromStart) = 0;
	virtual BOOL STDMETHODCALLTYPE select_prev_diff(BOOL bFromEnd) = 0;
	virtual BOOL STDMETHODCALLTYPE load_lang(LANGID langid, LPCWSTR langdir = NULL) = 0;
	virtual void STDMETHODCALLTYPE CMD_zoom(int) = 0;
	virtual void STDMETHODCALLTYPE CMD_select_all() = 0;
	virtual void STDMETHODCALLTYPE set_sibling2(IHexEditorWindow*, IHexEditorWindow*) = 0;
	virtual void STDMETHODCALLTYPE copy_sel_from(IHexEditorWindow*) = 0;
	virtual void STDMETHODCALLTYPE copy_all_from(IHexEditorWindow*) = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_undo() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_redo() = 0;
	virtual bool STDMETHODCALLTYPE can_undo() const = 0;
	virtual bool STDMETHODCALLTYPE can_redo() const = 0;
	virtual void STDMETHODCALLTYPE set_savepoint() = 0;
	virtual bool STDMETHODCALLTYPE get_modified() const = 0;
	virtual void STDMETHODCALLTYPE clear_undorecords() = 0;
	virtual void STDMETHODCALLTYPE share_undorecords(IHexEditorWindow*) = 0;
	virtual void STDMETHODCALLTYPE CMD_view_settings() = 0;
	virtual void STDMETHODCALLTYPE CMD_binarymode() = 0;
	virtual void STDMETHODCALLTYPE CMD_character_set() = 0;
	virtual void STDMETHODCALLTYPE read_ini_data(TCHAR* key = 0) = 0;
};

#endif // _hexeditctl_H_


