#!/bin/bash

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored messages
print_status() {
    local color=$1
    local message=$2
    echo -e "${color}${message}${NC}"
}

# Set up environment for ANTLR4 and GRUN
export CLASSPATH=".:/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH"
alias antlr4="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.Tool"
alias grun="java -Xmx500M -cp \"/usr/local/lib/antlr-4.13.2-complete.jar:$CLASSPATH\" org.antlr.v4.gui.TestRig"

# Apply aliases in current environment
shopt -s expand_aliases

print_status "$BLUE" "=== Iron Grammar Test Suite ==="

# Verify ANTLR4 and GRUN are configured correctly
print_status "$YELLOW" "Checking ANTLR4 and GRUN configuration..."
if ! type antlr4 > /dev/null 2>&1 || ! type grun > /dev/null 2>&1; then
    print_status "$RED" "ANTLR4 or GRUN commands are not properly configured."
    print_status "$YELLOW" "Make sure ANTLR is installed and properly configured in your environment."
    exit 1
fi
print_status "$GREEN" "✓ ANTLR4 and GRUN are properly configured"

# Create test directory if it doesn't exist
mkdir -p test_inputs

# Clean up previous generated files
print_status "$YELLOW" "Cleaning up previous generated files..."
rm -f Iron*.class Iron*.java *.interp *.tokens 2>/dev/null
print_status "$GREEN" "✓ Cleanup complete"

# Generate parser from grammar
print_status "$YELLOW" "Generating parser from Iron.g4..."
antlr4 -visitor Iron.g4

# Check if generation was successful
if [ $? -ne 0 ]; then
    print_status "$RED" "Failed to generate parser from Iron.g4"
    exit 1
fi
print_status "$GREEN" "✓ Parser generated successfully"

# Compile generated Java code
print_status "$YELLOW" "Compiling generated Java code..."
javac Iron*.java

# Check if compilation was successful
if [ $? -ne 0 ]; then
    print_status "$RED" "Failed to compile generated Java code"
    exit 1
fi
print_status "$GREEN" "✓ Java code compiled successfully"

# Test with simple input file
print_status "$YELLOW" "Testing parser with variables.txt (simple test)..."
grun Iron program -gui < variables.txt

# Check if parsing was successful
if [ $? -ne 0 ]; then
    print_status "$RED" "Failed to parse variables.txt"
    exit 1
fi
print_status "$GREEN" "✓ Successfully parsed variables.txt"

# Test with comprehensive input file
print_status "$YELLOW" "Testing parser with test_inputs/sample.iron (comprehensive test)..."
grun Iron program -gui test_inputs/sample.iron

# Check if parsing was successful
if [ $? -ne 0 ]; then
    print_status "$RED" "Failed to parse test_inputs/sample.iron"
    exit 1
fi
print_status "$GREEN" "✓ Successfully parsed test_inputs/sample.iron"

# Generate SVG visualization of the parse tree if possible
if command -v ps2pdf > /dev/null && command -v convert > /dev/null; then
    print_status "$YELLOW" "Generating parse tree visualization..."
    grun Iron program -ps test_inputs/sample.iron > antlr4_parse_tree.ps
    ps2pdf antlr4_parse_tree.ps antlr4_parse_tree.pdf
    convert -density 300 antlr4_parse_tree.pdf antlr4_parse_tree.svg
    rm -f antlr4_parse_tree.ps antlr4_parse_tree.pdf 2>/dev/null
    print_status "$GREEN" "✓ Parse tree visualization saved as 'antlr4_parse_tree.svg'"
fi

# Copy generated parser files to src/parsers if directory exists
if [ -d "../src/parsers" ]; then
    print_status "$YELLOW" "Copying generated parser files to src/parsers..."
    cp IronBaseListener.java IronLexer.java IronListener.java IronParser.java ../src/parsers/
    print_status "$GREEN" "✓ Parser files copied successfully"
fi

print_status "$BLUE" "=== Grammar Test Summary ==="
print_status "$GREEN" "✓ Grammar syntax is valid"
print_status "$GREEN" "✓ Parser generation successful"
print_status "$GREEN" "✓ Simple test file parsing successful"
print_status "$GREEN" "✓ Comprehensive test file parsing successful" 
print_status "$GREEN" "✓ All tests passed successfully!"
