#!/usr/bin/python

#######################################################
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License version 2, 1991 as published by
# the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
# 
# A copy of the GNU General Public License can be found at:
# [url="http://www.gnu.org/licenses/gpl.html"]http://www.gnu.org/licenses/gpl.html[/url]
# or you can write to:
# Free Software Foundation, Inc.
# 59 Temple Place - Suite 330
# Boston, MA 02111-1307
# USA.
#
#######################################################

#
# buftool.py:  By Linuxchuck
#
# Inspired by genbuf.pl, which uses Pex::Text::PatternCreate and also by
#   pattern_offset.rb found in the Metasploit Framework 3 tools directory.
#
# This script combines the function of both scripts into one package.

import sys

def usage():
    print (f"Usage: {sys.argv[0]} <number> [string]")
    print ("<number> is the size of the buffer to generate.")
    print ("[string] is the optional string to search for in the buffer.\n")
    print ("If [string] is provided, the buffer will not be printed, only the location")
    print ("of where the string starts in the buffer.  This search is CASE SENSITIVE!")
    sys.exit()

try:
    dummy = int(sys.argv[1])
except Exception as e:
    usage()

if len(sys.argv) > 3:
    usage()

if len(sys.argv) == 3:
    SEARCH = "TRUE"
    searchstr = sys.argv[2]
else:
    SEARCH = "FALSE"

stop = int(int(sys.argv[1]) / 3) + 1
patend = int(sys.argv[1])
patrange = range(0,stop,1)
first = 65
second = 97
third = 0
item = ""

for i in patrange:
    reset_first = "FALSE"
    reset_second = "FALSE"
    if third == 10:
        third = 0
        second += 1
    if second == 123:
        first +=1
        reset_second = "TRUE"
    if first == 92:
        reset_first = "TRUE"
    item += chr(first)
    item += chr(second)
    item += str(third)
    third += 1
    if reset_first == "TRUE":
        first = 65
    if reset_second == "TRUE":
        second = 97

if SEARCH != "TRUE":
    sys.stdout.write(item[0:patend])
else:
    location = item.find(searchstr)
    if location == -1:
        print (sys.argv[2] + " not found in buffer.")
        sys.exit()
    print (location)
