## Wake-On-LAN

### Compilation
Compile the project using CMake.

### Usage
```bash
wake_on_lan [-b <broadcast>] [-p <port>] <target>
```
+ target: Mac address of the target
+ default values: 192.168.1.255 (broadcast) and 9 (port)

#### Example usage
```bash
wake_on_lan -b '192.168.0.255' -p 6 'aa:bb:cc:dd:ee:ff'
```
