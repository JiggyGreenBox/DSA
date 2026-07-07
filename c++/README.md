# C++
## 1. Installation
* [Setup-md](setup/install-C++.md)

## 2. Helpful commands
```sh
# delete executable cpp files
find . -type f -executable -delete

# rename files with spaces
find . -type f -name "* *" -print0 | while IFS= read -r -d '' f; do mv "$f" "${f// /_}"; done
```


```sh
# wrap long text from clipboard
# paste wrapped text back to clipboard

sudo apt install xclip

# command
xclip -o -selection clipboard | fold -s -w 80 | xclip -i -selection clipboard

# make keyboard shortcut
How do I bind a bash command to a global keyboard shortcut in Linux 
so I don't have to open the terminal?

Keyboard -> Keyboard Shortcuts
name: wrap
command: bash -c "xclip -o -sel clip | fold -s -w 70 | xclip -i -sel clip"
shortcut: super+w
```

```sh
# replace spaces with underscores

# commmand
xclip -o -sel clip | sed 's/ /_/g' | xclip -i -sel clip

# make keyboard shortcut
Keyboard -> Keyboard Shortcuts
name: wrap
command: bash -c "xclip -o -sel clip | sed 's/ /_/g' | xclip -i -sel clip"
shortcut: super+e
```

```sh
# easy comment block for notes

# commmand
echo -e "/*\n\n*/" | xclip -sel c

# make keyboard shortcut
Keyboard -> Keyboard Shortcuts
name: commentblock
command: bash -c 'echo -e "/*\n\n*/" | xclip -sel c'
shortcut: super+r
```

```text
arrows for notes
↖ ↑ ↗
← · →
↙ ↓ ↘
```

```text
My rule for SDE2 prep

There are about 10–20 problems in DSA that contain a clever 
representation or trick that most people simply remember.

Examples:

trees
    Width of Binary Tree (heap indices)
    22_count_nodes_in_complete
    Morris Traversal (threaded tree)
Median of a row-wise sorted matrix (binary search on answer)
Trapping Rain Water (prefix/suffix or two pointers)
Largest Rectangle in Histogram (monotonic stack)

My rule for SDE2 prep

There are about 10–20 problems in DSA that contain a clever 
representation or trick that most people simply remember.

Examples:

Width of Binary Tree (heap indices)
Morris Traversal (threaded tree)
Median of a row-wise sorted matrix (binary search on answer)
Trapping Rain Water (prefix/suffix or two pointers)
Largest Rectangle in Histogram (monotonic stack)

I don't think there's anything wrong with remembering the key insight 
for these. In fact, experienced engineers often do exactly that. The 
important part is understanding why the trick works so you can 
explain it and adapt it, not pretending you'll rediscover it from 
scratch under interview pressure.

Given how you've been revising, I'd put "Width of Binary Tree" in 
that category: memorize the representation, derive the 
implementation. That's a perfectly reasonable balance.
```