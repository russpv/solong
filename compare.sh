#!/bin/bash

# Usage function
usage() {
    echo "Usage: $0 <dir1> <dir2>"
    echo "Compare files with the same name between <dir1> and <dir2>"
    exit 1
}

# Check for correct number of arguments
if [ "$#" -ne 2 ]; then
    usage
fi

DIR1=$1
DIR2=$2

# Check if both directories exist
if [ ! -d "$DIR1" ]; then
    echo "Directory $DIR1 does not exist."
    exit 1
fi

if [ ! -d "$DIR2" ]; then
    echo "Directory $DIR2 does not exist."
    exit 1
fi

# Compare files with the same name
echo "Comparing files with the same name between $DIR1 and $DIR2..."

# Find all files in the first directory
find "$DIR1" -type f | while read -r FILE1; do
    # Extract filename and create corresponding path in DIR2
    FILENAME=$(basename "$FILE1")
    FILE2="$DIR2/$FILENAME"

    if [ -f "$FILE2" ]; then
        # Files exist in both directories, compare them
        echo "Comparing $FILE1 and $FILE2"
        if ! diff -q "$FILE1" "$FILE2" >/dev/null; then
            echo "Files differ: $FILE1 and $FILE2"
        else
            echo "Files are identical: $FILE1 and $FILE2"
        fi
    else
        # File only exists in DIR1
        echo "File only in $DIR1: $FILE1"
    fi
done

# Check for files only in DIR2
find "$DIR2" -type f | while read -r FILE2; do
    FILENAME=$(basename "$FILE2")
    FILE1="$DIR1/$FILENAME"

    if [ ! -f "$FILE1" ]; then
        # File only exists in DIR2
        echo "File only in $DIR2: $FILE2"
    fi
done

echo "Comparison complete."

