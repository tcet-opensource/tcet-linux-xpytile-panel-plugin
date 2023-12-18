project = Xpytile
mode = Release

all: compile

prepare:
	mkdir build

builddeps:
	cmake -B build -DCMAKE_BUILD_TYPE=$(mode) -S .

compile:
	cmake --build build --config $(mode)

install:
	cp build/src/libhello-plugin.so /usr/lib/xfce4/panel/plugins/
	cp src/hello-plugin.desktop /usr/share/xfce4/panel/plugins/

uninstall:
	rm /usr/lib/xfce4/panel/plugins/libhello-plugin.so
	rm /usr/share/xfce4/panel/plugins/hello-plugin.desktop

clean:
	rm -rf build/
