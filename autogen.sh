#!/bin/bash

./scripts/autotools.sh ;
make ;
ln -s ./src/main ./runnable
