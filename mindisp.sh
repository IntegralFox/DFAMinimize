#!/bin/sh
./minimize $1
dot -T png $1.dot | display &
dot -T png $1-min.dot | display &
rm $1.dot $1-min.dot
