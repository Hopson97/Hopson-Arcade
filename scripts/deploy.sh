sh scripts/build.sh release 

rm -rf -d hopson-arcade

mkdir hopson-arcade

cp bin/release/hopson-arcade hopson-arcade
cp -r res hopson-arcade

echo "Deploy build created."
echo "cd hopson-arcade to find it"
