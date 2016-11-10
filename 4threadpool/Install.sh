#!/bin/bash
make -f Makefile
./result >result.txt
rm *.fifo
