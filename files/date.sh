#!/bin/bash

mkdir -p analysis_project/data
cd analysis_project/data

log_file = $(date +"%Y%m%d").log
for i in {1, 5}
do
	log_file="

