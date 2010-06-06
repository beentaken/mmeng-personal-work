#!/bin/bash

./$1 $2 > $3
diff --strip-trailing-cr $4 $3

