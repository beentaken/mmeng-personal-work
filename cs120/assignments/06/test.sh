#!/bin/bash

./scantext > output.txt
diff --strip-trailing-cr ./output.sample.txt ./output.txt

