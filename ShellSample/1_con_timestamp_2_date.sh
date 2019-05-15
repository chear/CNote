#!/bin/bash

# Input format:
# 82
# 824
# 1556
# 2288
# 3020
# 3752
#
# Output Format:

PATH=`pwd`
FILE="$PATH/timestamp.txt"


# -- Converts from human to epoch or epoch to human, specifically "Apr 28 07:50:01" human.
#    typeset now=$(date +"%s")
#    typeset now_human_date=$(convert_cron_time "human" "$now")
function convert_cron_time() {
case "${1,,}" in
    epoch)
        # human to epoch (eg. "Apr 28 07:50:01" to 1524916201)
        echo $(/bin/date -d "${2}" +"%s")
        ;;
    human)
        # epoch to human (eg. 1524916201 to "Apr 28 07:50:01")
        echo $(/bin/date -d "@${2}" +"_%H:%M:%S")
        ;;
esac

}

#line="82"
#_date=$(convert_cron_time "human" $line)
#echo "$line $_date"


echo "Starting to Operate"
echo $PATH
_last=0
if [ -f $FILE ]; then
    while read line; do
        _new=$(printf "%d" $line)
        _reduce=$((_new - _last))
        _last=$_new
        printf "%d\n" $_reduce
        _v=$line
        _date=$(convert_cron_time "human" $_v)
        printf "%s %s \n" $_date $line
    done < $FILE
fi
