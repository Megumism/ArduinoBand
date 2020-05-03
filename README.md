<!--spellcheck-off-->
# 说明

## 开发说明

### 本地位置

&emsp;&emsp;由于Arduino过于“人性化”的设计，导致无法在一般位置实现头文件的引用，而只能引用三种位置的头文件。（具体参见<https://www.arduino.cc/en/Guide/Libraries>）本项目采用的是Sketch位置的方法，因此，本项目需要放在`X:\Users\xxx\Documents\Arduino\libraries`下进行开发，而且头文件不能再放进二级目录，否则Arduino的编译器会找不到。

&emsp;&emsp;另外其实有非常暴力的开发方法，就是直接在`main.ino`的兄弟位置写一个ino文件（不要包含`loop`和`setup`，然后Arduino会自动把他们链接在一起，但这样比较愚蠢，只是把一个文件砍几段放而已。而且会让Intellisense感到混乱。

### 命名规范

&emsp;&emsp;所有单独调试的文件（也就是直接可以上传运行的）命名为`**_o.ino`，放在`individual`文件夹中。建立好类库之后提出来去掉_o的后缀。

## keyboard44.ino

- 初始化函数需要八个参数，对应键盘从左到右的针脚位置，可以缺省，默认为4~11。
- 接口函数是`char keyboard44::getKey();`
- 可以通过`setKey`函数更改针脚对应键值，默认是矩阵下标值。

附：键的功能

| 1 | 2 | 3 |  backspace  |
| - | - | - | :---------: |
| 4 | 5 | 6 |      up     |
| 7 | 8 | 9 |     down    |
| b | 0 | # |     enter   |
