#!/bin/bash

./fractions > output.fractions.txt
diff --strip-trailing-cr ./output.fractions.sample.txt ./output.fractions.txt

