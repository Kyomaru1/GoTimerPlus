#!/bin/bash
# Make sure to change the name of the SD card here to what the name of your
# SD card is;
SD_CARD_NAME=B05B-E09F


#Color codes for terminal output. Change if you'd like.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White
bldblk='\e[1;30m' # Black - Bold
bldred='\e[1;31m' # Red
bldgrn='\e[1;32m' # Green
bldylw='\e[1;33m' # Yellow
bldblu='\e[1;34m' # Blue
bldpur='\e[1;35m' # Purple
bldcyn='\e[1;36m' # Cyan
bldwht='\e[1;37m' # White
unkblk='\e[4;30m' # Black - Underline
undred='\e[4;31m' # Red
undgrn='\e[4;32m' # Green
undylw='\e[4;33m' # Yellow
undblu='\e[4;34m' # Blue
undpur='\e[4;35m' # Purple
undcyn='\e[4;36m' # Cyan
undwht='\e[4;37m' # White
bakblk='\e[40m'   # Black - Background
bakred='\e[41m'   # Red
bakgrn='\e[42m'   # Green
bakylw='\e[43m'   # Yellow
bakblu='\e[44m'   # Blue
bakpur='\e[45m'   # Purple
bakcyn='\e[46m'   # Cyan
bakwht='\e[47m'   # White
txtrst='\e[0m'    # Text Reset

USER=$(whoami)
if [ -d /media/${USER}/${SD_CARD_NAME} ]
then
    printf $2"\n" | sudo -S cp -u $1 /media/${USER}/${SD_CARD_NAME}/roms/nds
    
    if [ $? -ne 0 ] 
    then
        echo -e $txtred"\nThere was an error copying file to SD Card "${SD_CARD_NAME}$txtrst
    else
        echo -e $txtgrn"\nFile copied successfully to /media/"$(whoami)"/"${SD_CARD_NAME}"/roms/nds"$txtrst
    fi
else
    echo -e $undylw"The selected SD Card is not mounted, or is not the name supplied."$txtrst
    echo "Please check the settings in the script file and try again."
    echo -e $bakred$undwht"ABORTING"$txtrst
fi