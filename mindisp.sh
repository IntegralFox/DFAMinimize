#!/bin/sh
if ./minimize $1
then
dot -T png $1.dot | display &
dot -T png $1-min.dot | display &
fi
