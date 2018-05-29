#!/bin/bash
export INCLUDE_DIRS=`cat modules/paths|tr '\n' ' '`
export MODULAR_FIRMWARE=n
export MODULAR=n
export PARTICLE_DEVELOP=1
# export USE_SWD=y
# export DEBUG_BUILD=y
export PLATFORM=photon
export SPARK_CLOUD=n
export GCC_PREFIX=/home/sedur/compilers/gcc-arm-none-eabi-5_3-2016q1/bin/arm-none-eabi-
#export GCC_PREFIX=/home/sedur/compilers/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-
#export GCC_PREFIX=~/compilers/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-
#export GCC_PREFIX=~/devel/OwlWare/Tools/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-
# export GCC_PREFIX=arm-none-eabi-
export APP=nodOSC
#export APP=tinker
export WARNINGS_AS_ERRORS=n
make $*
