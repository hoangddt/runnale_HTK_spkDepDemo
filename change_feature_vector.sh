#!/bin/bash

# change $1 by $2
# protoconfigs/proto.pcf
# toolconfigs
FILES=(hcopy.conf hinit.conf herest.conf hrest.conf hvite.conf hsmooth.conf)


sed -i "s/$1/$2/g" protoconfigs/proto.pcf

for file in ${FILES[@]}; do
    echo "Editing $file"
    sed -i "s/$1/$2/g" toolconfigs/$file
done