# README #

### 概要 ###
メインディスプレイの解像度を変更する。

### 使用方法 ###
~~~~
> ChangeResolution.exe /?
Usage:
  ChangeResolution [-list] | [-name] | [-current] | WIDTH HEIGHT | NAME

Options:
  -c, --current #Show the current resolution.
  -l, --list    #Show the available resolutions.
  -n, --name    #Show the defined resolution names.
  WIDTH HEIGHT  #Change the resolution to WIDTH x HEIGHT.
  NAME          #Change the resolution to NAME.

Examples:
  ChangeResolution 1024 768  #Change the resolution to 1024x768.
  ChangeResolution SXGA      #Change the resolution to SXGA.
  ChangeResolution MAX       #Change the resolution to maximum possible.
~~~~