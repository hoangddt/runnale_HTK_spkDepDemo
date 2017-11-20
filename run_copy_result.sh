#!/bin/bash

./runDemo
mkdir Experiments/state$1_mix$2
cp -r result Experiments/state$1_mix$2
git add -A
git commit -m "Add result of run state: $1 mixture $2" &>/dev/null


echo "reporting"
tail Experiments/state$1_mix$2/result/testResult Experiments/state$1_mix$2/result/trainResult -n 4
tail Experiments/state$1_mix$2/result/testResult Experiments/state$1_mix$2/result/trainResult -n 4 > Experiments/reports/state$1_mix$2
echo "Done"