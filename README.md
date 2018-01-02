# coraline-plugin-ble-central
[Coraline](https://coraline.psychogenic.com/) Bluetooth Low Energy (BLE) Central plugin

	Copyright (C) 2017,2018 Pat Deegan psychogenic.com

This plugin gives cordova/ionic/JS apps running on Coraline access to BLE devices.

*Pre-packaged binary bundles* are available on the [Coraline Project Site](https://coraline.psychogenic.com/).

# Building 
This system using Cmake and, to build, you need access to the coraline headers (easiest way to get 
that is through the [coraline repo](https://github.com/psychogenic/coraline).  Once that source is
installed somewhere (e.g. /full/path/to/coraline), then move into this plugin's source directory, 
create a build dir and, from there, issue cmake while specifying where to find the headers:


cd <top-level-src director>
mkdir build; cd build
cmake -DCORALINE_INCLUDES=/full/path/to/coraline/include/ ..
make
