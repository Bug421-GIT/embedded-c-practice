# 嵌入式 C 基础练习

> 位操作、寄存器读写、`volatile` 的动手练习，为 STM32 裸机开发打底。
> 每个 `.c` 是一个独立程序，带 `main()`，编译即可运行。
> 起点 2026-10-31。**17 个文件全部在 GCC 16.2.0 上编译通过，`-Wall -Wextra` 零警告。**

---

## 练的是什么

| 主题 | 内容 | 文件 |
|---|---|---|
| **位操作** | 置位、清位、翻转、读位、段掩码、先清后写 | `bit01.c` `bit02.c` `bit-op-01-05.c` `bit-op-06-09.c` `bit-op-10-15.c` |
| **寄存器仿真** | 用 `uint32_t` 模拟 CRL / ODR / BSRR，按手册语义读改写 | `reg-01-06.c` `reg-07-10.c` |
| **volatile** | 加与不加的汇编差异、指针的 volatile、局部变量为什么没用 | `volatile-*.c` |

另有三份**反例演示**，专门验证「为什么不能这么做」：

- `demo-bit-errors.c` —— 用加法置位会进位改邻位、用减法清位会借位、掩码写错少翻 6 位
- `demo-mask.c` —— `int` 装不下 24 位以上掩码、XOR 造掩码会把参数写反藏起来
- `demo-10-15.c` —— 移位取字节 ≠ 看内存布局、BSRR 先置后清与先清后置的差异

---

## 编译与运行

需要 GCC（本项目在 MinGW-w64 GCC 16.2.0 上验证，GCC 9+ 应均可）。

```bash
# 编译
gcc -g -Wall -Wextra -std=c17 c-basics/bit01.c -o bin/bit01

# 运行
./bin/bit01

# 生成汇编（Intel 语法，对比 volatile 优化差异用）
gcc -S -O2 -masm=intel c-basics/volatile-nv.c -o bin/volatile-nv.s
```

### VSCode

1. 用 VSCode 打开**本目录**（`.vscode/tasks.json` 在这里）
2. 打开任意 `.c` 文件
3. `Ctrl+Shift+B` 编译到 `bin/`
4. `Ctrl+Shift+P` → `Tasks: Run Task` → `gcc: 编译并运行`

> `tasks.json` 里写死了本地 MinGW 路径，**在别的机器上要改 `command` 字段**，或者直接用上面的命令行。

---

## 目录

```
.
├── .vscode/            # VSCode 编译任务
├── c-basics/           # 全部练习源码
└── bin/                # 产物（.exe / .s），已在 .gitignore 中排除
```

| 文件 | 第几题 / 内容 |
|---|---|
| `bit01.c` | 置位 / 清位 / 读位，最小示例 |
| `bit02.c` | 位编号方向验证 + BCD 编码 |
| `bit_test.c` | 位操作速查（早期版本，保留对照） |
| `bit-op-01-05.c` | 1–5：置位、清位、翻转、读位、读字段 |
| `bit-op-06-09.c` | 6–9：构造掩码、先清后写 |
| `bit-op-10-15.c` | 10–15：大小端、nibble swap、BSRR、popcount |
| `reg-01-06.c` | 寄存器 1–6：CRL 字段读改写 |
| `reg-07-10.c` | 寄存器 7–10：BSRR 语义、字节序、溢出、`gpio_set_mode` |
| `volatile-nv.c` | 不加 volatile：`while` 退化成死循环 |
| `volatile-v.c` | 加 volatile：每圈重新读内存 |
| `volatile-local.c` / `volatile-local2.c` | 全局 / 局部 × volatile 四象限对照 |
| `volatile-ptr.c` | 指针的 volatile（`volatile uint32_t *`） |
| `volatile-irq.c` | 用线程模拟中断（**仅 Windows**） |
| `demo-bit-errors.c` | 反例：加法置位、减法清位、掩码写错 |
| `demo-mask.c` | 反例：`int` 装不下掩码、XOR 对称性掩盖错误 |
| `demo-10-15.c` | 反例：移位 vs 指针取字节、BSRR 顺序 |

---

## 几个值得单独记的点

### 位编号方向

**最低位是 bit 0。** 这一条搞反，所有寄存器操作全错。`bit02.c` 用 `0x0F0F` 把 bit 0–15 逐个打出来验证过。

### 段掩码的标准写法

```c
// 把 reg 的 bit n 到 bit n+width-1 改成 val
uint32_t mask = ((1u << width) - 1) << n;
reg &= ~mask;              // 先清
reg |= (val << n) & mask;  // 后写，且用 mask 限定范围
```

**`(val << n) & mask` 里的 `& mask` 不能省**——`val` 超出 width 位时会污染相邻字段。见 `reg-01-06.c` 的 `set_field()`。

### 移位量是起始位号，不是长度

`(R >> 8) & 0xF` 取的是 bit 8..11。写成 `>> 12` 就取到 bit 12..15 去了。

### 为什么先清后写不能省

清位之后那段位置是 0；直接 `|=` 只会把 1 加进去，原来该是 0 的位不会被改回 0。`bit-op-06-09.c` 第 8、9 题练的就是这个。

### BSRR 是「复位优先」

STM32 的 BSRR 低 16 位写 1 置位、高 16 位写 1 复位。**同时写同一位时，复位赢。**

`demo-10-15.c` 跑过对照：`bsrr = 0x00010001`（同时置 PA0 和清 PA0），先置后清得 `0`，先清后置得 `1`。

### volatile 只保证「不被优化掉」，不保证原子性

`volatile-nv.c` 与 `volatile-v.c` 用 `gcc -S -O2 -masm=intel` 对比：

- 不加：`mov flag(%rip), %eax` 只读一次，然后 `jmp .L3` 空转
- 加了：`je .L2` 跳回 `mov`，每圈重新读

**`volatile` 解决可见性，不解决竞态。** 多核或中断里改的共享变量，还需要原子操作或临界区。

---

## 已知限制

- `volatile-irq.c` 用 `CreateThread` 模拟中断，**仅 Windows**，Linux / macOS 编译不过。它只用于演示「不加 volatile 会卡死」。
- **`volatile-nv.c` / `volatile-v.c` / `volatile-irq.c` 运行会挂住**——`while` 循环等一个永远不变的变量，本来就是这个演示的目的。要么在终端里 `Ctrl+C` 结束，要么只看 `-S` 生成的汇编，不要直接跑。
- `tasks.json` 里的编译器路径是本机绝对路径，换机器要改。
- 源码是 UTF-8。Windows 控制台默认代码页（GBK）下中文 `printf` 会乱码，先 `chcp 65001` 或改用 Windows Terminal。
- 这是**学习练习**，不是生产代码：没有测试框架，靠 `main()` 里的 `printf` 肉眼校验。

---

## 接下来

板子到手后（野火 F103 指南者），会新增 `stm32/` 目录放裸机代码：GPIO 点灯、串口收发、Modbus RTU 从机。

在那之前，这里的内容够用来回答「位操作怎么用」「volatile 到底解决什么问题」这类问题。
