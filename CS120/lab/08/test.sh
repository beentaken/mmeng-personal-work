#1/bin/bash

./reverse > output.txt
diff --strip-trailing-cr ./output.sample.txt ./output.txt

