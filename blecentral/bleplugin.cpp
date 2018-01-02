/*
 * bleplugin.cpp
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


#include "bleplugin.h"
#include <iostream>

#define BLEPLUGIN_ENABLE_DEBUG

#ifdef BLEPLUGIN_ENABLE_DEBUG
#define BLEPL_DEBUG(...)		std::cerr << __VA_ARGS__
#define BLEPL_DEBUGLN(...)		std::cerr << __VA_ARGS__ << std::endl
#else
#define BLEPL_DEBUG(...)
#define BLEPL_DEBUGLN(...)

#endif

#define MYDEV_NOPARAM_CALL(meth)  getDev()->meth(callbacks.success, callbacks.error); return true

#define BLEPLUGIN_STANDARD_SUCCESSCB(cb)\
		[this, cb](){ \
				triggerCallback(cb.success); \
			}
#define BLEPLUGIN_STANDARD_FAILCB(cb)\
		[this, cb](){ \
				triggerCallback(cb.error); \
			}

#define BLEPLUGIN_STANDARD_SUCCFAILPARAMS(cb) \
		BLEPLUGIN_STANDARD_SUCCESSCB(cb), \
		BLEPLUGIN_STANDARD_FAILCB(cb)

#define BLEPLUGIN_STDGATTLIBCALL(method, clbks) \
		Gattlib::BLECentral::getInstance()->method(BLEPLUGIN_STANDARD_SUCCFAILPARAMS(clbks))

#define BLEPLUGIN_DEVICEGATTLIBCALL(method, dev, clbks) \
		Gattlib::BLECentral::getInstance()->method(dev, BLEPLUGIN_STANDARD_SUCCFAILPARAMS(clbks))


#define BLEPLUGINARGS_ATLEAST_ORFAIL(argsArray, argsMin, callbacks) \
	if (! (args.size() >= argsMin) ) { \
		BLEPL_DEBUGLN("Insufficient args, need " << argsMin << " but got " << args.size()); \
		reportError(callbacks); \
		return false; \
	}


#define BLEPLUGINARGS_TYPE_ORFAIL(argsArray, argsIdx, argsTypeFunc, callbacks) \
	if (! (args[argsIdx].argsTypeFunc()) ) { \
		BLEPL_DEBUGLN("Arg idx " << argsIdx << " doesn't pass type test"); \
		reportError(callbacks); \
		return false; \
	}






BLEPlugin::BLEPlugin(const Coraline::Plugin::Context & ctx) : Coraline::Plugin::Base(ctx)
{

}



Coraline::Plugin::AboutString BLEPlugin::about() {
	return Coraline::Plugin::AboutString(
			"Bluetooth Low Energy central plugin, Copyright (C) 2017 Pat Deegan, https://psychogenic.com"
	);

}
Coraline::Plugin::AboutString BLEPlugin::usage() {

	return Coraline::Plugin::AboutString(
			"BLE central plugin, (C) 2017 Pat Deegan psychogenic.com\n"
			"This plugin should be a drop-in replacement for the cordova-plugin-ble-central "
			"and used in the same manner."
	);


}


void BLEPlugin::startUp() {
	Gattlib::BLECentral::getInstance()->setAutoDiscoverOnConnect(true);

    this->Coraline::Plugin::Base::startUp();
    this->executeResourceJS("init.js");

}

void BLEPlugin::update()
{

	Gattlib::BLECentral::getInstance()->processAsync();
}
void BLEPlugin::shutdown() {
	Gattlib::BLECentral::getInstance()->shutdown();
}
/*
Coraline::Plugin::ClientCode BLEPlugin::clientSideSupport() {
    return Coraline::Plugin::ClientCode(
                "var Device =  (function() {"
                 "   function Device() {"
                 "   }"
                 "   "
                 "  Device.prototype.getInfo = function(win,fail,args) {"
                 "       cordova.exec(function (asArray) {"
                 "           win({model: asArray[0], cordova: asArray[1],"
                 "                platform: asArray[2], uuid: asArray[3], version: asArray[4], manufacturer: asArray[5]});"
                 "      }, null, \"com.cordova.device\", \"getInfo\", []);"
                 "   };"
                 "   return Device;"
                "}());");



}
*/


Coraline::Version BLEPlugin::version() {

    return Coraline::Version(MYPLUGIN_VERSION_MAJOR,
            MYPLUGIN_VERSION_MINOR,
            MYPLUGIN_VERSION_PATCH);
}




/*
void BLEPlugin::cbbTrigger(int cbId, QString val) {
    std::string utf8_text = val.toUtf8().constData();

    qDebug() << "cbbTrigger: " << val;
    json ho;
    try {
     ho = json::parse(utf8_text);
    } catch (std::invalid_argument&) {
        qDebug() << "bad json stuffs?? " << val;
        ho = json::parse("{\"parseError\":true}");
    }

    triggerCallback(cbId, ho);

}

void BLEPlugin::cbbTriggerNoRemove(int cbId, QString val) {
    std::string utf8_text = val.toUtf8().constData();

     qDebug() << "cbbTriggerNoRemove: " << val;
    json ho;
    try {
     ho = json::parse(utf8_text);
    } catch (std::invalid_argument&) {
        qDebug() << "bad json stuffs?? " << val;
    }

    triggerCallbackNoRemove(cbId, ho);

}
*/
void BLEPlugin::registerAllMethods() {
    PLUGINREGMETH(scan);
    PLUGINREGMETH(startScan);
    PLUGINREGMETH(stopScan);
    PLUGINREGMETH(connect);
    PLUGINREGMETH(isConnected);
    PLUGINREGMETH(disconnect);

    PLUGINREGMETH(read);
    PLUGINREGMETH(write);
    PLUGINREGMETH(writeWithoutResponse);
    PLUGINREGMETH(startNotification);
    PLUGINREGMETH(stopNotification);
    PLUGINREGMETH(stopAllNotifications);
    PLUGINREGMETH(isEnabled);
    PLUGINREGMETH(enable);



}

bool BLEPlugin::scan(const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	MYPLUGIN_DEBUGLN("BLEPlugin::startScan()");
	if (! (args.size() > 1) && args[1].is_number()) {
		// invalid
		reportError(callbacks);
		return false;
	}

	int duration = args.at(1);

	Coraline::CallbackID succId = callbacks.success;
	Coraline::CallbackID errId = callbacks.error;
	return Gattlib::BLECentral::getInstance()->scan(duration,
		[](){
			BLEPL_DEBUGLN("Scan start succeeded");
		},
		[this, succId](const Gattlib::Discovery::Device & devFound){
			json devObj;
			json::array_t emptyAdv;
			devObj["name"] = devFound.name;
			devObj["id"] = devFound.id;
			devObj["rssi"] = devFound.rssi;
			devObj["advertising"] = emptyAdv;

			triggerCallbackNoRemove(succId, devObj);
		}, [this, errId](){
			triggerCallback(errId);
		});
}

bool BLEPlugin::startScan(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	MYPLUGIN_DEBUGLN("BLEPlugin::startScan()");

	json::array_t myargs;
	if (args.size() > 0) {
		myargs.push_back(args[0]);
	}
	myargs.push_back(0);
	return scan(callbacks, myargs);
}


bool BLEPlugin::stopScan(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {


	return BLEPLUGIN_STDGATTLIBCALL(stopScan, callbacks);


}



bool BLEPlugin::connect(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 1, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);

	std::string devId= args[0];

	return Gattlib::BLECentral::getInstance()->connect(devId, [this, devId, callbacks](){

		Gattlib::BLECentral * central = Gattlib::BLECentral::getInstance();

		Gattlib::Service::List servs =
				central->servicesFor(devId);

		Gattlib::Characteristic::List  chars =
				central->characteristicsFor(devId);

		json retObj = json::object();
		retObj["name"] = central->deviceName(devId);
		retObj["id"] = devId;
		retObj["advertising"] = json::array();
		retObj["rssi"] = 0;
		retObj["services"] = json::array();
		retObj["characterstics"] = json::array();
		for (Gattlib::Service::List::iterator iter = servs.begin();
				iter != servs.end();
				iter++)
		{
			retObj["services"].push_back((*iter).id);
		}
		for (Gattlib::Characteristic::List::iterator iter = chars.begin();
				iter != chars.end();
				iter++)
		{
			json achar = json::object();
			achar["service"] = "n/a";
			achar["characteristic"] = ((*iter).id);
			json propArray = json::array();
			if ((*iter).supportsReads()) {
				propArray.push_back("Read");
			}
			if ((*iter).supportsWrites()) {
				propArray.push_back("Write");
			}
			if ((*iter).supportSubscriptions()) {
				propArray.push_back("Notify");
			}
			achar["properties"] = propArray;
			retObj["characteristics"].push_back(achar);
		}

		reportSuccess(callbacks, retObj);

	}, BLEPLUGIN_STANDARD_FAILCB(callbacks));



	return BLEPLUGIN_DEVICEGATTLIBCALL(connect, devId, callbacks);


}

bool BLEPlugin::isConnected(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {
	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 1, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);


	std::string devId= args[0];
	return BLEPLUGIN_DEVICEGATTLIBCALL(isConnected, devId, callbacks);

}

bool BLEPlugin::disconnect(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 1, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);


	std::string devId= args[0];
	return BLEPLUGIN_DEVICEGATTLIBCALL(disconnect, devId, callbacks);
}

bool BLEPlugin::characteristicsFor(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	reportError(callbacks, std::string("unimplemented"));
	return false;
}

bool BLEPlugin::read(const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 3, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 1, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 2, is_string, callbacks);

	return Gattlib::BLECentral::getInstance()->read(args[0], args[1], args[2],
			[this, callbacks](const Gattlib::BinaryBuffer & rcvdData){

			json valsArray = json::array();
			for (Gattlib::BinaryBuffer::const_iterator iter = rcvdData.begin();
					iter != rcvdData.end();
					iter++)
				{
					valsArray.push_back(*iter);
				}

			reportSuccess(callbacks, valsArray);
	},
	BLEPLUGIN_STANDARD_FAILCB(callbacks));

}

bool BLEPlugin::write(const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {
	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 4, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 1, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 2, is_string, callbacks);
	// BLEPLUGINARGS_TYPE_ORFAIL(args, 3, is_array, callbacks);
	Gattlib::BinaryBuffer buf;
	if (args[3].is_array()) {
		for (uint8_t i=0; i< args[3].size(); i++) {
			uint8_t c = args[3].at(i);
			buf.push_back(c);
		}
	}else {
		buf.push_back(0xAA);
	}
	return Gattlib::BLECentral::getInstance()->write(args[0], args[1], args[2],
			buf,
			BLEPLUGIN_STANDARD_SUCCFAILPARAMS(callbacks));

}

bool BLEPlugin::writeWithoutResponse(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {
		BLEPLUGINARGS_ATLEAST_ORFAIL(args, 4, callbacks);
		BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);
		BLEPLUGINARGS_TYPE_ORFAIL(args, 1, is_string, callbacks);
		BLEPLUGINARGS_TYPE_ORFAIL(args, 2, is_string, callbacks);
		BLEPLUGINARGS_TYPE_ORFAIL(args, 3, is_array, callbacks);
		Gattlib::BinaryBuffer buf;
		for (uint8_t i=0; i< args[3].size(); i++) {
			uint8_t c = args[3].at(i);
			buf.push_back(c);
		}
		return Gattlib::BLECentral::getInstance()->writeWithoutResponse(args[0], args[1], args[2],
				buf,
				BLEPLUGIN_STANDARD_SUCCFAILPARAMS(callbacks));


}

bool BLEPlugin::startNotification(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 3, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 1, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 2, is_string, callbacks);

	Coraline::CallbackID notifCbId = callbacks.success;

	return Gattlib::BLECentral::getInstance()->startNotification(args[0], args[1], args[2],
			[this, notifCbId](const Gattlib::BinaryBuffer & inData) {
				// we got a notification.
				json dataArray = json::array();
				for (Gattlib::BinaryBuffer::const_iterator iter=inData.begin();
						iter != inData.end();
						iter++) {
					dataArray.push_back(*iter);
				}

				triggerCallbackNoRemove(notifCbId, dataArray);

			},
			BLEPLUGIN_STANDARD_FAILCB(callbacks));

}

bool BLEPlugin::stopNotification(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {


	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 3, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 1, is_string, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 2, is_string, callbacks);

	return Gattlib::BLECentral::getInstance()->stopNotification(args[0], args[1], args[2],
			BLEPLUGIN_STANDARD_SUCCFAILPARAMS(callbacks));


}

bool BLEPlugin::stopAllNotifications(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	BLEPLUGINARGS_ATLEAST_ORFAIL(args, 1, callbacks);
	BLEPLUGINARGS_TYPE_ORFAIL(args, 0, is_string, callbacks);

	Gattlib::BLECentral::getInstance()->stopAllNotifications(args[0]);

	if (callbacks.success) {
		triggerCallback(callbacks.success);
	}
	return true;

}

bool BLEPlugin::isEnabled(
		const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	return Gattlib::BLECentral::getInstance()->isEnabled(BLEPLUGIN_STANDARD_SUCCFAILPARAMS(callbacks));
}

bool BLEPlugin::enable(const Coraline::Plugin::StandardCallbackIDs& callbacks,
		const Coraline::Plugin::ArgsList& args) {

	return Gattlib::BLECentral::getInstance()->enable(BLEPLUGIN_STANDARD_SUCCFAILPARAMS(callbacks));

}
