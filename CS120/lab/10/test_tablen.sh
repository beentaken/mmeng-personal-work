#!/bin/bash

./tablen ./driver-sample.cpp > output.tablen.txt
diff --strip-trailing-cr ./driver-sample-tablen.txt ./output.tablen.txt

