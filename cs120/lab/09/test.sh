#!/bin/bash

./dumpit decl-win.txt > output.txt
diff --strip-trailing-cr decl.dumpit.txt output.txt

./dumpit icon1.bmp > output.txt
diff --strip-trailing-cr icon1.dumpit.txt output.txt

