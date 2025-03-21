#!/usr/bin/env python3

# If a rule doesn't work, run this script.
# Usage: ./add_rule.py <rule>
import sys
from lifelib.autocompile import reset_tree
reset_tree(sys.argv[1])