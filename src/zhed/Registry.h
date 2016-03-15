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
 * @file  Registry.h
 *
 * @brief zhed registry functions.
 *
 */
#ifndef _REGISTRY_H_
#define _REGISTRY_H_

BOOL contextpresent();
BOOL linkspresent();
BOOL defaultpresent();
BOOL unknownpresent();
BOOL oldpresent();
BOOL zhedpresent();

#endif // _REGISTRY_H_
