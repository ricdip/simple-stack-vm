#!/bin/bash

# run "make run" command every *.cpp and *.hpp file change using entr
fd --type f -e cpp -e hpp | entr -r -s "make run"
