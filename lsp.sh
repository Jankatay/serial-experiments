#!/usr/bin/env bash
# likely want to redirect this to a compile_commands.json
find . -name compile_commands.json -exec jq -s add {} +
