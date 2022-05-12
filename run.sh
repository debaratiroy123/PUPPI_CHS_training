g++  `root-config --cflags`  `root-config --libs` -o  MergeTree_PUID MergeTree_PUID.C
for i in 2018
do
    echo "dataset year" $i
    ./MergeTree_PUID $i
done
echo "Finished running..."
