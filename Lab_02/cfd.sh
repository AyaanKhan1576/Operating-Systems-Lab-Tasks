#!/bin/bash

while [[ $# -gt 0 ]]; do
    case "$1" in
        -d)
            if [ -n "$2" ]; then
                mkdir "$2"
            else
                echo "No directory name provided after -d"
            fi
            shift 2
            ;;
        -f)
            if [ -n "$2" ]; then
                touch "$2"
            else
                echo "No file name provided after -f"
            fi
            shift 2
            ;;
        -t)
            if [ -n "$2" ]; then
                if [ -n "$3" ]; then
                    echo "$2" >> "$3"
                else
                    echo "No string or file name provided after -t"
                    break
                fi
            else
                echo "No string provided after -t"
            fi
            shift 3
            ;;
        *)
            echo "Unknown option: $1"
            shift
            ;;
    esac
done

