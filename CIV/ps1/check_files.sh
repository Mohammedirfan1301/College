#!/bin/bash
#*****************************************************************************
#  Check all cpp and hpp files in a directory
#*****************************************************************************
cpplint.py --filter=-runtime/references,-build/header_guard *.cpp
cpplint.py --filter=-runtime/references,-build/header_guard *.hpp
