#1/bin/bash

./primes > output.txt
diff --strip-trailing-cr ./$1 ./output.txt

