#!/bin/bash

./$1 | diff --strip-trailing-cr $2 -

