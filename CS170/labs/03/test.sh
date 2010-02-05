#!/bin/bash

./ll > myoutput.txt
diff --strip-trailing-cr ./output2.txt ./myoutput.txt

