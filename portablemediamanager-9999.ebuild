# Copyright 1999-2009 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit qt4 subversion

DESCRIPTION="Simple and minimalistic portable audio/video player manager for
Linux"
HOMEPAGE="http://code.google.com/p/portablemediamanager/"
ESVN_REPO_URI="http://${PN}.googlecode.com/svn/trunk/"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64 ~x86"

DEPEND=">=x11-libs/qt-core-4.5.0
	>=x11-libs/qt-dbus-4.5.0
	>=x11-libs/qt-gui-4.5.0"
RDEPEND="${DEPEND}
	sys-apps/hal"

src_unpack() {
	subversion_src_unpack
}

src_compile() {
	qt4_src_prepare
	sed -i '/^desktop.files/,+2d' "${PN}.pro" || die "sed failed"
	eqmake4 ${PN}.pro
	emake || die "emake failed"
}

src_install() {
	emake INSTALL_ROOT="${D}" install || die "emake install failed"
	make_desktop_entry ${PN} 'Portable Media Manager' ${PN} \
		'Qt;AudioVideo' || die "make_desktop_entry failed"
}

