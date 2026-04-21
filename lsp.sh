#!/usr/bin/env bash
find . -name compile_commands.json -exec jq -s add {} +
