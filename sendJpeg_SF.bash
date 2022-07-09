#!/bin/bash
#id="SF_Image_Send"
#xterm_options="-iconic -geometry 110x20"

# kill existing applications
/usr/bin/pkill -f 'snap_jpegStandalone'

# open windows and start application
#xterm $xterm_options -title "${id}"\
#    -e "
./snap_jpegStandalone 127.0.0.1 5311 2 SFground test.jpg

sleep 5
