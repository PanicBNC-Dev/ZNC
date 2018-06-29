#!/bin/sh
set -e

TMPDIR=`mktemp -d`
TMPDIR2=`mktemp -d`
trap 'rm -rf $TMPDIR $TMPDIR2' EXIT

if [ ! -f include/znc/main.h ] ; then
	echo "Can't find source!"
	exit -1
fi

if [ "x$1" = "x--nightly" ]; then
	# e.g. ./make-tarball.sh --nightly znc-git-2014-04-21 path/to/output/znc-foo.tar.gz
	ZNCDIR=$2
	TARGZ=$3
	SIGN=0
	DESC=-nightly-`date +%Y%m%d`-`git $GITDIR rev-parse HEAD | cut -b-8`
else
	VERSION=$1
	if [ "x$VERSION" = "x" ] ; then
		AWK_ARG='/#define VERSION_MAJOR/ { maj = $3 }
			/#define VERSION_MINOR/ { min = $3 }
			END { printf "%.1f", (maj + min / 10) }'
		VERSION=$(awk "$AWK_ARG" include/znc/main.h)
	fi
	if [ "x$VERSION" = "x" ] ; then
		echo "Couldn't get version number"
		exit -1
	fi

	ZNCDIR=panicbnc-$VERSION
	TARGZ=$ZNCDIR.tar.gz
	SIGN=1
	DESC=""
	# DESC="-rc1"
fi

TARGZ=`readlink -f -- $TARGZ`

echo "Exporting . to $TMPDIR/$ZNCDIR..."
git checkout-index --all --prefix=$TMPDIR/$ZNCDIR/
mkdir -p --mode=0755 $TMPDIR/$ZNCDIR/third_party/Csocket
cp -p third_party/Csocket/Csocket.cc third_party/Csocket/Csocket.h $TMPDIR/$ZNCDIR/third_party/Csocket/
(
	cd $TMPDIR2
	cmake $TMPDIR/$ZNCDIR
)
(
	cd $TMPDIR/$ZNCDIR
	AUTOMAKE_FLAGS="--add-missing --copy" ./autogen.sh
	rm -r autom4te.cache/
	rm make-tarball.sh
	# For autoconf
	sed -e "s/THIS_IS_NOT_TARBALL//" -i Makefile.in
	echo '#include <znc/version.h>' > src/version.cpp
	echo "const char* ZNC_VERSION_EXTRA = VERSION_EXTRA \"$DESC\";" >> src/version.cpp
	# For cmake
	if [ "x$DESC" != "x" ]; then
		echo $DESC > .nightly
	fi
)
(
	cd $TMPDIR
	echo "Creating tarball"
	env GZIP=-9 tar -czf $TARGZ $ZNCDIR	
)
echo "Done"

