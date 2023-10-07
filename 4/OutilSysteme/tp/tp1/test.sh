#!/bin/bash

read -ra tableau <<< `cat coucou.txt`
echo ${tableau[0]}
