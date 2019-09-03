#!/bin/bash

COUNT=0
old_ver=""
REVISION="../whole_log"
OUTPUT="../tmp_patch/"
CP_PATH="../tmp_patch/patchs/"
COPYFILE="../keep_list"
CPCOUNT=0
(
flock -n 9 || exit 1
svn update
svn log > $REVISION
) 9>/var/lock/mylockfile

## generate the patch for each log and sequence by revision num
for i in `cat $REVISION |grep "r[0-9]\{4\}\s|" | awk '{print $1 }'`; do
    echo $old_ver":"$i;
    if [ "$COUNT" -ne 0 ]; then
        FILE=$OUTPUT$old_ver".patch"
#        echo "writeing ... to "$FILE
#        cmd=`svn diff -r $old_ver:$i ./ > $FILE`
#        echo $cmd
        svn diff -r $i:$old_ver ./ > $FILE
    fi
    old_ver=$i
    ((COUNT+=1));

done
echo "generate all the patchs number="$COUNT;


for i in `cat $COPYFILE |grep "r[0-9]\{4\}\s|" | awk '{print $1 }'`; do
    FI=$i".patch"
    if [ -e $OUTPUT$FI ]; then
        echo "cp from "$OUTPUT$FI" to "$CP_PATH$FI
        cp $OUTPUT$FI $CP_PATH$FI
    fi
    ((CPCOUNT+=1));
done
echo "copy files number="$CPCOUNT;

