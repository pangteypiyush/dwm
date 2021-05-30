![DWM](https://raw.githubusercontent.com/pangteypiyush/dwm/master/dwm.png)

dwm (dynamic window manager) is an extremely fast, small, and dynamic window manager for X.

[![License MIT](https://img.shields.io/github/license/pangteypiyush/dwm.svg)](https://raw.githubusercontent.com/pangteypiyush/dwm/gruvbox/LICENSE) [![Last Commit](https://img.shields.io/github/last-commit/pangteypiyush/dwm.svg?color=282828)](https://github.com/pangteypiyush/dwm/commits) [![makepkg](https://github.com/pangteypiyush/dwm/actions/workflows/makepkg.yml/badge.svg?branch=gruvbox)](https://github.com/pangteypiyush/dwm/actions/workflows/makepkg.yml)

## Screenshot

Checkout [Gallery][gallery] for more screenshots

![gruvbox](https://raw.githubusercontent.com/wiki/pangteypiyush/dwm/screenshots/2019/03/06/1.png)

## Installation

In order to build dwm you need the Xlib header files.

Checkout branch `gruvbox` and run `make clean install`, or use [PKGBUILD](https://github.com/pangteypiyush/dwm/tree/pkgbuild) from `pkgbuild` branch.

## Custom Patches

### Alternate box and schemes
 - Description: more colorschemes and new ui for tag box elements
 - Branch: [feature/alternatebox-n-scheme][alternatebox-n-scheme]

### Alternative tags
 - Description: switchable alternative tags character
 - Branch: [feature/ppang-dwm-alttag][ppang-dwm-alttag]
 - Link: https://dwm.suckless.org/patches/alternativetags

### Clean monocle
 - Description: remove monocle client count
 - Branch: [feature/ppang-dwm-cleanmonocle][ppang-dwm-cleanmonocle]

### Spawntag
 - Description: spawn application by directly clicking a tag
 - Branch: [feature/ppang-dwm-spawntag][ppang-dwm-spawntag]

## Community Patches

### Gapless grid
 - Branch: [feature/ppang-dwm-gaplessgrid][ppang-dwm-gaplessgrid]
 - Link: https://dwm.suckless.org/patches/gaplessgrid

### Useless gap
 - Branch: [feature/ppang-dwm-uselessgaps][ppang-dwm-uselessgaps]
 - Link: https://dwm.suckless.org/patches/uselessgap

### Autostart
 - Branch: [feature/dwm-autostart][dwm-autostart]
 - Link: https://dwm.suckless.org/patches/autostart

### Pertag
 - Branch: [feature/dwm-pertag][dwm-pertag]
 - Link: https://dwm.suckless.org/patches/pertag

### Shiftview
 - Branch: [feature/dwm-shiftview][dwm-shiftview]
 - Link: *NA*

### EWMH tags
 - Branch: [feature/ewmhtags][ewmhtags]
 - Link: https://dwm.suckless.org/patches/ewmhtags

## Links
 - [Gallery][gallery]
 - [Dotfiles](https://github.com/pangteypiyush/dotfiles)


[gallery]: https://github.com/pangteypiyush/dwm/wiki/Gallery
[wiki]: https://github.com/pangteypiyush/wiki

[alternatebox-n-scheme]: https://github.com/pangteypiyush/dwm/tree/feature/alternatebox-n-scheme
[dwm-autostart]: https://github.com/pangteypiyush/dwm/tree/feature/dwm-autostart
[dwm-pertag]: https://github.com/pangteypiyush/dwm/tree/feature/dwm-pertag
[dwm-shiftview]: https://github.com/pangteypiyush/dwm/tree/feature/dwm-shiftview
[ewmhtags]: https://github.com/pangteypiyush/dwm/tree/feature/ewmhtags
[ppang-dwm-alttag]: https://github.com/pangteypiyush/dwm/tree/feature/ppang-dwm-alttag
[ppang-dwm-cleanmonocle]: https://github.com/pangteypiyush/dwm/tree/feature/ppang-dwm-cleanmonocle
[ppang-dwm-gaplessgrid]: https://github.com/pangteypiyush/dwm/tree/feature/ppang-dwm-gaplessgrid
[ppang-dwm-spawntag]: https://github.com/pangteypiyush/dwm/tree/feature/ppang-dwm-spawntag
[ppang-dwm-uselessgaps]: https://github.com/pangteypiyush/dwm/tree/feature/ppang-dwm-uselessgaps
