#!/bin/bash

./spell > output.txt
diff --strip-trailing-cr ./output.sample.txt ./output.txt

