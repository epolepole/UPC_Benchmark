#!/bin/bash

export PATH=$PATH:/usr/local/non-commercial/berkeley-upc/2.18.0/bin/:/usr/local/non-commercial/berkeley-upc/2.18.0/include/:/scratch/s244866/cmake-3.6.0/bin/

. /etc/profile.d/modules.sh

source /usr/local/commercial/intel/xe2013/config_intel.sh

module load impi
. mpivars.sh


