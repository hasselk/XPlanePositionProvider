# XPlanePositionProvider
KDE Marble plugin to parse X-Plane UDP packets and track position.

@akeyla420, akeyla@protonmail.ch

The following are extra libraries you'll need to install for the build
> sudo apt install git cmake qtdeclarative5-dev libqt5svg5-dev

Download the marble source from kde.org.  Some of these instructions where taken from https://marble.kde.org/sources.php
> git clone -b Applications/16.12 git://anongit.kde.org/marble ~/marble/sources

Create directory for plugin and download
> mkdir ~/marble/sources/src/plugins/positionprovider/xp

> git clone https://github.com/akeyla420/XPlanePositionProvider.git ~/marble/sources/src/plugins/positionprovider/xp/

Add entry to CMakeLists.txt in the positionprovider dir so the plugin is included during the build
> sed -i '1s;^;ADD_SUBDIRECTORY( xp )\n;' ~/marble/sources/src/plugins/positionprovider/CMakeLists.txt

Build it!
> mkdir -p ~/marble/build

> cd ~/marble/build

> cmake -DCMAKE_BUILD_TYPE=Debug -DWITH_KF5=TRUE -DCMAKE_INSTALL_PREFIX=/usr/local ~/marble/sources

> make

> sudo make install

> marble-qt

Once Marble is loaded, on the Location tab, under Position Tracking, select X-Plane.
Set X-Plane to output datasets 3, 17, 20 to the IP of the machine running Marble, port 49003
