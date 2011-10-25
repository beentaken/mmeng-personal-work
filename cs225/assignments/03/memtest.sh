#!/bin/bash

valgrind $1 $2 |& grep "All heap blocks were freed -- no leaks are possible" || exit 1

