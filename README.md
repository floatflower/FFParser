FFParser
===
[![Build Status](https://travis-ci.org/floatflower/FFParser.svg?branch=master)](https://travis-ci.org/floatflower/FFParser)

這個專案是為了編譯原理所開發的 LL(1) Parser。
This LL(1) Parser is the final project for the class "compiler"。

## Developer
+ Developer: FloatFlower.Huang
+ Email: mail@floatflower.me
+ Website: https://blog.floatflower.me

## How to use
### Compile this project
```
$ sudo add-apt-repository ppa:beineri/opt-qt562-trusty
$ sudo apt-get update
$ sudo apt-get install -qq qt5-qmake qt56base
$ source /opt/qt56/bin/qt56-env.sh
$ /opt/qt56/bin/qmake
$ make
```

### Execute
```
$ ./ffparser    --cfg,-c <CFG_FILE>
                --source,-s <SOURCE_CODE_PATH>
                --output,-o <OUTPUT_FILE_PATH>
```
