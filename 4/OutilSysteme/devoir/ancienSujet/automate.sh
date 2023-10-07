/#!/bin/bash

s="000100110111110000000111010110000010111111111000110101010110111000000"

simulation() {
    s=$s
    s="0"$s"0"
    w="_"
    while [ "$s" != "$w" ] ; do
	w=$s
	s=$(echo $s | sed -E "s/([1b])1([1b])/\1b\2/g; s/([1b])0([1b])/\1a\2/g; s/([0a])0([1b])/\1a\2/g")
    done
    s=$(echo $s | sed -E "s/a/1/g; s/b/0/g")
    s=${s:1:${#s}-2}
}

for i in {1..18}; do
    simulation
    echo "$s" | sed -E 's/0/ /g' | sed -E 's/1/#/g';
done
