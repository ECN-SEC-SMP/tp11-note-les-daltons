this_dir=$(dirname "$(realpath $0)")
for test_file in $this_dir/../build/bin/test_*; do
    if [[ -x "$test_file" ]]; then
        "$test_file"
    fi
done