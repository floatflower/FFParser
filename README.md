FFParser
===
[![Build Status](https://travis-ci.org/floatflower/FFParser.svg?branch=master)](https://travis-ci.org/floatflower/FFParser)

這個專案是為了編譯原理所開發的 LL(1) Parser，這個專案已經完成開發並完全符合老師要求，取得專題滿分。

This LL(1) Parser is the final project for the class "compiler", this project had been developed completely, and matched all requirement from professor.

## Notice
若需要使用此專案作為個人作業繳交，請先來信告知作者，
此外，若為其他教學用途，敬請使用並附上原始碼出處。

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
