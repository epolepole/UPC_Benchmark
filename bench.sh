#!/bin/bash
#
#
#---------------------------------------------
# PBS Options:
#
# -N job name
#
# -l select=n:ncpus=y:mpiprocs=z
# 
# Where n number of chunks of:
#       y CPUs (max 16)
#       z MPI processes per CPU 
#
#       Therefore y should always equal z
#       y should always be a maxiumum of 16
#       Use n as multiplier.
# e.g.  16 CPUs: select=1:ncpus=16:mpiprocs=16
#       32 CPUs: select=2:ncpus=16:mpiprocs=16
#       48 CPUs: select=3:ncpus=16:mpiprocs=16
#       ..etc..
# -q queuename
# 
# -m abe -M your email address
# 
#
#---------------------------------------------
#PBS -N Bench
#PBS -l select=4:ncpus=16:mpiprocs=16
#PBS -k oe
#PBS -q express
#PBS -m abe -M l.ramos-munoz@cranfield.ac.uk

#
# Load module environment
export PATH=$PATH:/usr/local/non-commercial/berkeley-upc/2.18.0/bin/:/usr/local/non-commercial/berkeley-upc/2.18.0/include/:/scratch/s244866/cmake-3.6.0/bin/
. /etc/profile.d/modules.sh
source /usr/local/commercial/intel/xe2013/config_intel.sh

# Load MPI environment
module load impi
. mpivars.sh

# Change to working directory
cd $PBS_O_WORKDIR
pwd

# Calculate number of CPUs.

# Run code

echo "Compiling"
pwd
ls
cd UPC_Benchmark

./clean.sh
./go.sh R 64 1000



