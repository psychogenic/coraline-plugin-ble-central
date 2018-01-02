/*
 * loader.h
 *
 *  Created on: Dec 2, 2017
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


#ifndef SRC_LOADER_H_
#define SRC_LOADER_H_

#include "bleplugin_global.h"

#ifdef __cplusplus
extern "C" {
#endif


bool supports_driver(const Coraline::Version & v);

Coraline::Version object_version();

Coraline::Plugin::Plugin * create_object(const Coraline::Plugin::Context & ctx);

void destroy_object(Coraline::Plugin::Plugin * object );

#ifdef __cplusplus
}
#endif



#endif /* SRC_LOADER_H_ */
