#! /bin/sh

MAIN_FILE="main"

# set and create output directory
OUTPUT_DIR=latex_output
mkdir -p $OUTPUT_DIR

# compile twice when successful once
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_FILE.tex" && pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_FILE.tex"

# run biber
biber "$OUTPUT_DIR/$MAIN_FILE"

# recompile
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_FILE.tex"

