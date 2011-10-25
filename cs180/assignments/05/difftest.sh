#!/bin/bash

./$1 $2 | diff -b --strip-trailing-cr $3 -

