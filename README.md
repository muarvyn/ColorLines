# ColorLines
One more implementation of Lines 98.


## Build instructions

Requires at least Qt v5.5.1 and boost graph v1.58.0 (may work with earlier versions).

### Host and target platform: Linux

1. Install prerequisites:
```
sudo apt-get install build-essential git qt5-default libboost-graph-dev
```

2. Get Source files:
```
git clone https://github.com/muarvyn/ColorLines.git
cd ColorLines/
git submodule update --init --recursive --remote
```

3. Compile:
```
qmake -makefile
make
```

4. Install (Optional):
```
sudo install ./ColorLines /usr/bin
```
