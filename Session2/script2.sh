[ ! -d "$3" ] && mkdir $3
cp -r $1/* $3
echo "All dir1 files copied to dir3"
cp -r $2/* $3
echo "All dir2 files copied to dir3"