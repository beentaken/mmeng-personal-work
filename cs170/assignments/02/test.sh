#!/bin/bash

echo Running program...
./warboats > output.txt

echo Running diff...
diff --strip-trailing-cr ./out-99-30-30-tf.txt ./output.txt

