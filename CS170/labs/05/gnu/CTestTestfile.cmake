# CMake generated Testfile for 
# Source directory: /home/amackenzie/work/mmeng-personal-work/CS170/labs/05
# Build directory: /home/amackenzie/work/mmeng-personal-work/CS170/labs/05/gnu
# 
# This file replicates the SUBDIRS() and ADD_TEST() commands from the source
# tree CMakeLists.txt file, skipping any SUBDIRS() or ADD_TEST() commands
# that are excluded by CMake control structures, i.e. IF() commands.
ADD_TEST(BASIC_DIFF "difftest.sh" "./ll" "myoutput.txt" "output-all.txt")
