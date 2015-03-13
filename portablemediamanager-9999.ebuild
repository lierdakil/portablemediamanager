# Copyright 1999-2009 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

inherit qt4-r2 git-r3

DESCRIPTION="Simple and minimalistic portable audio/video player manager for
Linux"
HOMEPAGE="https://github.com/lierdakil/portablemediamanager"
EGIT_REPO_URI="https://github.com/lierdakil/portablemediamanager"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64 ~x86"

DEPEND=">=x11-libs/qt-core-4.5.0
	>=x11-libs/qt-dbus-4.5.0
	>=x11-libs/qt-gui-4.5.0"
RDEPEND="${DEPEND}
	sys-apps/hal"

src_prepare() {
	qt4-r2_src_prepare
	sed -i '/^desktop.files/,+2d' "${PN}.pro" || die "sed failed"
}

src_install() {
	qt4-r2_src_install
	make_desktop_entry ${PN} 'Portable Media Manager' ${PN} \
		'Qt;AudioVideo' || die "make_desktop_entry failed"
}
