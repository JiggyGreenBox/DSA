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

```text
arrows for notes
↖ ↑ ↗
← · →
↙ ↓ ↘
```