#!/bin/sh
svnurl="https://hopmod.googlecode.com/svn/trunk/"
oldrev=`cat rev.h | cut -d " " -f3`
newrev=$1
if [ "$newrev" = "latest" ]; then
    echo "getting latest revision..."
    newrev=`svn info $svnurl | grep Revision: | cut -c11-`
    echo "latest revision is $newrev"
fi
if [ "$oldrev" -ge "$newrev" ]; then
    echo "revision $newrev is already merged"
    exit 1
fi
echo "writing new revision to rev.h"
echo "#define HOPMODSVNREV $newrev" > rev.h
echo "merging..."
bash -c "svn merge -r$oldrev:$newrev $svnurl ." || exit 1
exit 0
