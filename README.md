# trojan-go-configmanager-qt
###描述
作为一个trojan-go客户端的配置管理工具，仅供学习trojan-go代码使用，如有人作为vpn客户端使用，与本人无关,
目前只支持windows。

### 运行界面
![image](https://user-images.githubusercontent.com/31812698/184277475-e9dc9100-e9ff-4fef-ae93-24555b66c914.png)

### 声明
确实抄的trojan-qt5的ui，准确的说qss文件是抄过来的，主题也是抄过来的，但是并非无脑的复制粘贴，只是依葫芦画瓢而已。因为本人是后端程序员，不擅长调样式。所以不算是抄袭，只能算借鉴。借鉴的模块有主题样式、windows代理设置（已读懂并修改），其他都是自己码出来的。
作为我qt的第一个项目，也是c语言的第一个项目，语法的应用可能稍有稚嫩。

### 依赖
[trojan-go](https://github.com/p4gefau1t/trojan-go)（核心）
windows api

都放在在了lib里面。你可以不用自己编译，直接拿来用

### 编译
      `mkdir ../build`
1. 编译trojan-go模块作为动态链接库使用

      `cd trojan-go`
      `go build -o ./trojan-go-start.lib -buildmode=c-shared ./easy-to-start`

2. 移动编译好的动态链接库到项目指定位置

      `cd ..`
      `mv ./trojan-go/trojan-go-start.h ./src/trojan/`
      `mv ./trojan-go/trojan-go-start.lib ./lib/windows/`

3. qmake编译

      `cd ../build`
      `qmake.exe ../trojan-go-configmanager-qt/trojan-go-desktop.pro`
      `mingw32-make.exe -j16 `

4. 最后的依赖复制

      `cp ../trojan-go-configmanager-qt/lib/windows/trojan-go-start.lib ./release/`
      `cp -R ../trojan-go-configmanager-qt/dat ./release/`

5. 更新域名列表

      `cd ./dat`
     `./update.sh`


