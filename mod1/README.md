## [mod1 工程](https://github.com/Qful/keyboard)

mod1工程包括两块电路板核心模块，偏向计算的数字加密单元和偏向通信IOT交互单元，结合外围电路和相应的选择芯片，完成预定工程目标。

#### [功能单元](PART1/)

数字货币钱包单元，用于管理数字货币和相应的信息加解密，独立运行的功能实体。

* [STM32F407](https://github.com/sochub/STM32F407)
* [trezor](https://github.com/trezor)

#### [交互单元](PART2/)

用于对外提供按键信息输入和按键状态信息，物联网化信息输出实体，可以外联协同其他模块完成鉴权和控制。

* [CH579](https://github.com/sochub/CH579)
