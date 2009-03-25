# portablemediamanager Simple and minimalistic portable audio/video player manager for Linux
# Copyright (C) 2009 Nikolay "Livid" Yakimov
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
QT += dbus
TARGET = portablemediamanager
TEMPLATE = app
DESTDIR = bin/
SOURCES += main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    ccopythread.cpp \
    licensedialog.cpp
HEADERS += mainwindow.h \
    settingsdialog.h \
    ccopythread.h \
    licensedialog.h
FORMS += mainwindow.ui \
    settingsdialog.ui \
    licensedialog.ui
TRANSLATIONS = portablemediamanager_ru.ts
RESOURCES += icons.qrc \
    gpl.qrc
target.path+=/usr/bin
INSTALLS+=target
images.files+=./portablemediamanager.png
images.path+=/usr/share/pixmaps
INSTALLS+=images
desktop.files+=./portablemediamanager.desktop
desktop.path+=/usr/share/applications
INSTALLS+=desktop
