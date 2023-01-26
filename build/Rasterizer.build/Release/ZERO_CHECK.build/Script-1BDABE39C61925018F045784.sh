#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/young/CSCE441/A1/build
  make -f /Users/young/CSCE441/A1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/young/CSCE441/A1/build
  make -f /Users/young/CSCE441/A1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/young/CSCE441/A1/build
  make -f /Users/young/CSCE441/A1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/young/CSCE441/A1/build
  make -f /Users/young/CSCE441/A1/build/CMakeScripts/ReRunCMake.make
fi

