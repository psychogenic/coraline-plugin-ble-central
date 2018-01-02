/*
 * loader.cpp
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


#include "loader.h"
#include "bleplugin.h"


extern "C" bool supports_driver(const Coraline::Version & v) {
    return true;
}

extern "C"  Coraline::Version object_version() {

    return Coraline::Version(MYPLUGIN_VERSION_MAJOR,
            MYPLUGIN_VERSION_MINOR,
            MYPLUGIN_VERSION_PATCH);
}

extern "C" Coraline::Plugin::Plugin * create_object(const Coraline::Plugin::Context & ctx)
{
  return new BLEPlugin(ctx);
}


extern "C" void destroy_object(Coraline::Plugin::Plugin * object )
{
  delete object;
}
