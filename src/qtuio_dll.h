/*
	qTUIO - TUIO Interface for Qt

	Original Version by Martin Blankenburg <martin.blankenburg@imis.uni-luebeck.de>
	Integrated into qTUIO by x29a <0.x29a.0@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// This is needed for the compiler to know whether it should build (export) or use (import) the library

#ifndef QTUIO_DLL_H
#define QTUIO_DLL_H

#include <QtCore/qglobal.h>

#if defined(QTUIO_LIBRARY)
#  define QTUIO_EXPORT Q_DECL_EXPORT
#else
#  define QTUIO_EXPORT Q_DECL_IMPORT
#endif

#endif // QTUIO_DLL_H
