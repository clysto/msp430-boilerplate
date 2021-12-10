# MSP430FR5969 开发模板

## 开发环境

1. 下载 [MSP430-GCC-OPENSOURCE](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) 编译器。注意要下载 **GCC ALL-IN-ONE INSTALLER** 而不是 GCC TOOLCHAIN ONLY 因为 GCC TOOLCHAIN ONLY 中不包含 `gdb_agent_console`。运行 installer 安装到任意位置，建议安装到 `~/.ti/msp430-gcc`。

2. 下载 [MSP430-FLASHER](https://www.ti.com/tool/MSP430-FLASHER) 命令行烧写工具。运行 installer 安装到任意位置，建议安装到 `~/.ti/MSPFlasher_1.3.20`。（根据版本号路径会不同）

3. 下载 SRecord：
   
   ```
   brew install srecord
   ```

## 开始编写代码

1. 克隆本仓库 `git clone https://github.com/clysto/msp430-boilerplate.git`

2. 设置环境变量：
   ```sh
   export MSPGCC=/Users/<username>/.ti/msp430-gcc
   export MSPFLASER=/Users/<username>/.ti/MSPFlasher_1.3.20
   export PATH=$MSPFLASER:$MSPGCC/bin:$PATH
   ```

3. 编译和烧写：
   ```sh
   # 将源代码编译成 elf 文件和 txt 文件
   make

   # 通过 tiusb 将开发板连接到电脑
   # 使用 MSPFlasher 将程序上传到开发版
   make upload
   ```

## VS Code 配置

在代码目录下新建 `.vscode/c_cpp_properties.json`

```json
{
  "configurations": [
    {
      "name": "msp430",
      "includePath": [
        "${workspaceFolder}/**",
        "/Users/<username>/.ti/msp430-gcc/include"
      ],
      "defines": ["__MSP430FR5969__"]
    }
  ],
  "version": 4
}
```

配置好后 VS Code 就可以自动找到头文件目录。

## 调试代码

首先启动 gdb agent console：

```sh
# 进入 MSP430-GCC-OPENSOURCE 安装目录
cd msp430-gcc
# 启动 gdb agent console
./bin/gdb_agent_console msp430.dat
```

启动后会在本机的55000端口启动gdb代理服务器。然后将开发版连接到电脑。

```
CPU Name             Port
--------             ----
msp430              :55000

Starting all cores
CPU Name             Status
--------             ------
msp430               Waiting for client
```

在代码目录中启动gdb：

```sh
make debug
```

在 gdb 中连接到 gdb 代理服务器：

```
(gdb) target remote :55000
```

连接成功后就可以将 elf 文件加载到开发版：

```
(gdb) load
```

加载完成后可以使用 gdb 开始调试程序：

```
(gdb) continue
```
