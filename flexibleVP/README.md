## Features

- Launch applications and web pages directly from Vim.
- Store and manage the addresses of your apps and web pages from Vim.
- Cross-platform support for Windows, macOS, and Linux.

## Installation

To install flexibleVP, you can use a plugin manager like [Vim-Plug](https://github.com/junegunn/vim-plug). Add the following line to your Vim configuration file (e.g., `~/.vimrc` or `init.vim`):

```vim
Plug 'SuprimeBG/flexibleVP'
```

## Usage

To launch an app or open a web page, use the `:Launch` command followed by the name of the app or web page. For example:

```vim
:Launch facebook
```

This will search for the specified name in the app and web page address files and open the corresponding address.
You can add new app or web page addresses using the `:Addw` and `:Adda` commands or just go to webaddress.txt or appaddress.txt. 
For example:
```vim
:Addw example www.example.com
:Adda brave C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe
```

Check existing addresses or add new ones from witing Vim. For example:
To list web addresses:
```vim
:Listw
```

To list app addresses:
```vim
:Lista
```

## Common errors
Plugin may have problems with plugin managers

When opening something it may be low resolution.

Please note that when adding web address at leas end it with .com/.org/.net ... so command knows to look in the internet
