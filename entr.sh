#!/bin/bash

fd --type f -e cpp -e hpp | entr -r -s "make run"
