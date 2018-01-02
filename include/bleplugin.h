/*
 * bleplugin.h
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


#ifndef BLEPlugin_H
#define BLEPlugin_H

#include "bleplugin_global.h"

#include "blecentral.h"



class BLEPlugin : public Coraline::Plugin::Base
{

public:
    BLEPlugin(const Coraline::Plugin::Context & ctx);
    virtual void startUp();
    virtual void update();
    virtual void shutdown();
    Coraline::Version version();

    virtual const Coraline::PluginName fullName() { return "cordova-plugin-ble-central"; }
    virtual const Coraline::PluginName shortName() { return "BLE";}


	virtual Coraline::Plugin::ClientCodeFileName clientSideSupportFile() { return "ble.js";}
	virtual Coraline::Plugin::AboutString about();
	virtual Coraline::Plugin::AboutString usage();

protected:
    virtual void registerAllMethods();

private:
    json emptyResponse;
	/*
	 * scan -- starts a scan and with a specified timeout (or until stopScan)
	 */
	bool scan(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	/*
	 * startScan -- will scan until stopScan is called.
	 */

	bool startScan(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	/*
	 * stopScan -- what it says on the box.
	 */
	bool stopScan(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	/*
	 * connecting to a device
	 */
	bool connect(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);
	bool isConnected(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);
	bool disconnect(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	// todo?
	bool characteristicsFor(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	bool read(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	bool write(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	bool writeWithoutResponse(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	bool startNotification(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);


	bool stopNotification(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	bool stopAllNotifications(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	bool isEnabled(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

	bool enable(const Coraline::Plugin::StandardCallbackIDs & callbacks,
            const Coraline::Plugin::ArgsList & args);

};

#endif // BLEPlugin_H
