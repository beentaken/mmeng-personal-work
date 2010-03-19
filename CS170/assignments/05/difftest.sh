#!/bin/bash

./$1 > $2
diff --strip-trailing-cr $3 $2

