#!/bin/bash
# 
# File:   ketod.sh.bash
# Author: ubuntu
#
# Created on Jan 12, 2018, 5:44:49 PM
#

# Get the current source directory
SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Assume the source ends in /bin and strip that off
KETO_HOME=${SOURCE_DIR%%/bin}
export KETO_HOME
echo "Setting KETO_HOME=${KETO_HOME}"

# execute ketod
${KETO_HOME}/bin/ketod $@


