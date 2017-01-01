# XPlanePositionProvider
KDE Marble plugin to parse X-Plane UDP packets and track position.
@akeyla420, akeyla@protonmail.ch

Let's see what I can come up with for an "install guide"...
I had a pretty fresh Ubuntu 16.04 install on an extra computer, so I tried building marble on it and wrote this down as I went.

The following were the extra libraries I needed to install
>> sudo apt install git cmake qtdeclarative5-dev libqt5svg5-dev

Download the marble source from kde.org.  Some of these instructions where taken from https://marble.kde.org/sources.php
>> git clone -b Applications/16.12 git://anongit.kde.org/marble ~/marble/sources

Create directory for plugin and download
>> mkdir ~/marble/sources/src/plugins/positionprovider/xp
>> git clone https://github.com/akeyla420/XPlanePositionProvider.git ~/marble/sources/src/plugins/positionprovider/xp/

Add entry to CMakeLists.txt in the positionprovider dir so the plugin is included during the build
>> sed -i '1s;^;ADD_SUBDIRECTORY( xp )\n;' ~/marble/sources/src/plugins/positionprovider/CMakeLists.txt

Build it!
>> mkdir -p ~/marble/build
>> cd ~/marble/build
>> cmake -DCMAKE_BUILD_TYPE=Debug -DWITH_KF5=TRUE -DCMAKE_INSTALL_PREFIX=/usr/local ~/marble/sources
>> make
>> sudo make install

>> marble-qt

Once Marble is loaded, on the Location tab, under Position Tracking, select the XPlane plugin.
Make sure XPlane is set to output data to 127.0.0.1 on port 49003, have #3 & #20 selected for output
Marble has to be running on the same box as XPlane, at least currently. 
