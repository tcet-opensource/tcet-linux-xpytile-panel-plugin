# tcet-linux-xpytile-panel-plugin

A XFCE panel plugin for enabling/disabling xpytile

## Installation Instruction

```sh
cd xfce4-sample-plugin
./autogen.sh
make
make install
```
## Actual plugin install

- got to panel-plugin directory

- run 
```sh
sudo make install 
cp /usr/local/lib/xfce4/panel/plugins/libsample.so /usr/lib/xfce4/panel/plugins/
cp ./sample.desktop /usr/share/xfce4/panel/plugins/sample.desktop
```
- add sample plugin to panel

right click panel -> add new items -> search for 'Sample Plugin' -> add
