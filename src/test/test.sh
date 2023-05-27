#!/bin/bash

extention=".traglodit501"

RED='\033[0;31m'
GREEN='\033[0;42m'
NC='\033[0m'


for filename in test_files/*.txt; do
  echo "----------------"
  testfile=$(echo $filename | tr "/" " " | awk '{ print $2 }')
  echo $testfile
  content_before=$(cat $filename)
  echo before: $(ls -lah $filename | awk '{ print $5 }')
  ../../cmake-build-debug/traglodit501 encode --file $(echo $filename)
  echo "after: " $(ls -lah $filename$extention | awk '{ print $5 }')
  ../../cmake-build-debug/traglodit501 decode --file $(echo $filename$extention)
  content_after=$(cat $filename)
  if [ "$content_before" == "$content_after" ]; then
    echo -e ${GREEN}success${NC}
  else
    echo -e ${RED}fail${NC}
  fi
  rm "./"$filename$extention
done
echo "----------------"