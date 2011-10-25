#!/bin/bash

./main > out.txt
diff -b -B --strip-trailing-cr ./output.sample.txt ./out.txt

