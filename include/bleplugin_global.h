/*
 * bleplugin_global.h
 *
 *  Created on: Dec 16, 2017
 *           Copyright (C) 2017 Pat Deegan, https://psychogenic.com
 *
 *  This file is part of the Coraline BLE Central plugin [https://coraline.psychogenic.com/]
 *
 *  Coraline is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Coraline is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Coraline.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef DEVICEPLUGIN_GLOBAL_H
#define DEVICEPLUGIN_GLOBAL_H

#include <coraline/plugins/pluginDev.h>

#include <Gattlibpp.h>

#define MYPLUGIN_VERSION_MAJOR     1
#define MYPLUGIN_VERSION_MINOR     0
#define MYPLUGIN_VERSION_PATCH     5

//define MYPLUGIN_ENABLE_DEBUG

#ifdef MYPLUGIN_ENABLE_DEBUG
#include <iostream>
#define MYPLUGIN_DEBUG(...)		std::cerr << __VA_ARGS__
#define MYPLUGIN_DEBUGLN(...)		std::cerr << __VA_ARGS__ << std::endl;
#else
#define MYPLUGIN_DEBUG(...)
#define MYPLUGIN_DEBUGLN(...)
#endif




#endif // DEVICEPLUGIN_GLOBAL_H
