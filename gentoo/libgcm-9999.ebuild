# Copyright 1999-2016 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Id$

EAPI=5

AUTOTOOLS_AUTORECONF=1
inherit autotools-utils

DESCRIPTION="Google Cloud Messaging C library"
HOMEPAGE="https://github.com/doctaweeks/libgcm"
if [[ ${PV} == "9999" ]] ; then
	inherit git-r3
	EGIT_REPO_URI="https://github.com/doctaweeks/${PN}"
	KEYWORDS=""
else
	SRC_URI="https://github.com/doctaweeks/${PN}/archive/v${PV}.tar.gz -> ${P}.tar.gz"
	KEYWORDS="amd64 x86"
fi

LICENSE="GPL-2"
SLOT="0"
IUSE="static-libs"

DEPEND="dev-libs/json-c
	net-misc/curl"
RDEPEND="${DEPEND}"
