#!/bin/bash
cat env.log | tee summary.log
./pa1-p1-sol | tee -a summary.log 
./pa1-p2-sol | tee -a summary.log 
./pa1-p3-sol | tee -a summary.log 

