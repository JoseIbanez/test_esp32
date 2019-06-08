


tag=`git tag | tail -1`
commit=`git log --pretty=format:"%h" -n 1`
versiondate=`git log --pretty=format:"%cd" -n 1`

echo "#define VERSION $tag-$commit"      >  version.h
echo "#define VERSION_DATE $versiondate" >> version.h
