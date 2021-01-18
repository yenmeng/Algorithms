#!/bin/bash

iter=1
while [[ $iter -le 8 ]]; do
echo iter$iter
(set -x; ./pa3_checker_mac public_cases/public_case_$iter.in output/public_case_$iter.out)
iter=$[$iter+1];
done

