#!/bin/bash
mkdir -p analysis_project/files
cd analysis_project
cat << EOF > files/text_file1.txt
This is a sample text file.
It contains multiple lines of text.
We will use it for our analysis project.
EOF
cat << EOF > files/text_file2.txt
Another text file.
It has some more lines of text.
EOF
cat << EOF > files/.hidden_file.txt
Hello CBNU
EOF
cat << EOF > files/script.sh
#!/bin/bash
echo " 현재 시간은 $(date +%H:%M:%S) 입니다 ."
EOF
chmod +x files/script.sh
