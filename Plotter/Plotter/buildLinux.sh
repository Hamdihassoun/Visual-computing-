#!/bin/bash

# Erst auf Kommandozeile Pfad setzen, z.B. so:
#export QTDIR=~/Qt5/5.14.2/gcc_64
#export PATH=$QTDIR/bin:$PATH:.

qmake -spec linux-g++-64 Plotter.pro

