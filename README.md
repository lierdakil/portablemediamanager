# portablemediamanager

This piece of software was designed with UMS portable media players in mind. Program allows to mount or unmount your media player, "upload" or "download" media, perserving folder structure, remove files or folders on portable media. Files are copied in alphabetical order.

This software relies on Qt4, HAL and, consequently, DBus. It was tested with Qt 4.5, but earlier versions like 4.4 or 4.3 might work as well.

This project also incorporates some icons from amazing GANT iconset.

# Install

## Gentoo ##

There is a gentoo ebuild available. You can get it on [Downloads](http://code.google.com/p/portablemediamanager/downloads/list) page.

If you want some help on creating and maintaining local portage overlay, I suggest you to consult Gentoo Wiki: http://en.gentoo-wiki.com/wiki/Overlays#Creating_a_local_overlay

## Other systems ##

There are no prebuilt packages (yet). So you will most likely need to checkout desired version from svn and build it from source.

Currently, only one version is available -- development, or trunk.

### Checkout ###

To checkout sources from repository, you will need subversion client (usually called subversion or svn-cilent in your distribution repository). After installing it, choose a directory to store sources in (for example, /home/user/src) and execute
```
cd /home/user/src
git clone "git@github.com:lierdakil/portablemediamanager.git"
```

## Build ##

Cd to Portabe Media Manager source directory
```
cd portablemediamanager
```

and run qmake, make and sudo make install
```
qmake portablemediamanager.pro
make
```

this will build Portable Media Manager. You can actually run it already from bin/portablemediamanager.

### Install ###

In Portabe Media Manager source directory, execute
```
sudo make install
```

this will install binaries to /usr/bin, application icon to /usr/share/pixmaps and desktop file to /usr/share/applications. Now you should have Portable media Manager launch icon under Audio/Video category in your desktop environment's launch menu.

### Uninstall ###

To uninstall, simply execute
```
make uninstall
```
in Portabe Media Manager source directory.
