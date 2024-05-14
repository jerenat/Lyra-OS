/*
    This file is part of Luxur
    Copyright (C) 2010 - 2013 Esteban Misael Maltauro

    Luxur is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Luxur is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Escrito por Sebastian Fernandez
*/

 
#ifndef _STDARG_H_
#define	_STDARG_H_

typedef char *va_list;

#define	__va_promote(type) \
	(((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define	va_start(ap, last) \
	(ap = ((char *)&(last) + __va_promote(last)))


#define	va_arg(ap, type) \
	((type *)(ap += sizeof(type)))[-1]


#define	va_end(ap)

#endif
