# phpPI
基于wiringPi控制树莓派io的php扩展

## 安装流程：
* 先安装wiringPi,安装教程可百度 wiringPi官网：http://wiringpi.com/
* phpize
* ./configure --with-php-config=php-config路径 LDFLAGS=-lwiringPi
* make
* make install
* php -m 即可查看扩展

## 函数参考
该扩展函数大多数都和wiringPi命名相同，目前只实现了以下函数：

### 初始化
- wiringPiSetup 初始化成功返回true，否则返回false 当使用这个函数初始化树莓派引脚时，程序使用的是wiringPi 引脚编号表。引脚的编号为 0~16需要root权限
- wiringPiSetupGpio 初始化成功返回true，否则返回false 当使用这个函数初始化树莓派引脚时，程序中使用的是BCM GPIO 引脚编号表。   需要root权限


### gpio控制函数
- pinMode(pin,model)  pin：配置的引脚  mode:指定引脚的IO模式 可取的值：PI_INPUT、PI_OUTPUT、PI_PWM_OUTPUT，PI_GPIO_CLOCK 作用：配置引脚的IO模式
> 注意：只有wiringPi 引脚编号下的1脚（BCM下的18脚） 支持PWM输出 
> 只有wiringPi编号下的7（BCM下的4号）支持GPIO_CLOCK输出
- digitalWrite(pin,value) pin：控制的引脚  value：引脚输出的电平值。 可取的值：PI_HIGH，PI_LOW分别代表高低电平
> 让对一个已近配置为输出模式的 引脚  输出指定的电平信号
- digitalRead(pin)  pin：读取的引脚 返回：引脚上的电平，可以是PI_LOW PI_HIGH 之一

- pwmWrite(pin,value) pin：引脚 value：写入到PWM寄存器的值，范围在0~1024之间。
> pin：引脚 value：写入到PWM寄存器的值，范围在0~1024之间。
> 输出一个值到PWM寄存器，控制PWM输出。
> pin只能是wiringPi 引脚编号下的1脚（BCM下的18脚）
- pullUpDnControl(pin,pud)   pin：引脚 pud：拉电阻模式 可取的值：PI_PUD_OFF        不启用任何拉电阻。关闭拉电阻。PI_PUD_DOWN    启用下拉电阻，引脚电平拉到GND  PI_PUD_UP         启用上拉电阻，引脚电平拉到3.3v
> 对一个设置IO模式为 INPUT 的输入引脚设置拉电阻模式。
> 与Arduino不同的是，树莓派支持的拉电阻模式更丰富。 
> 树莓派内部的拉电阻达50K欧姆

### 时间控制函数
- piMillis();
> 这个函数返回 一个 从你的程序执行 wiringPiSetup  初始化函数（或者wiringPiSetupGpio ） 到 当前时间 经过的 毫秒数。  返回类型是unsigned int，最大可记录 大约49天的毫秒时长。

- piMicros();
> 这个函数返回 一个 从你的程序执行 wiringPiSetup  初始化函数（或者wiringPiSetupGpio ） 到 当前时间 经过的 微秒数。返回类型是unsigned int，最大可记录 大约71分钟的时长。

- piDelay(howLong);
> 将当前执行流暂停 指定的毫秒数。因为Linux本身是多线程的，所以实际暂停时间可能会长一些。参数是unsigned int 类型，最大延时时间可达49天

- piDelayMicroseconds(howLong);
> 将执行流暂停 指定的微秒数（1000微秒 = 1毫秒 = 0.001秒）。因为Linux本身是多线程的，所以实际暂停时间可能会长一些。参数是unsigned int 类型，最大延时时间可达71分钟

## 常量
PI_INPUT= 0
PI_OUTPUT= 1
PI_PWM_OUTPUT= 2
PI_GPIO_CLOCK= 3

PI_LOW= 0
PI_HIGH= 1

PI_PUD_OFF= 0
PI_PUD_DOWN= 1
PI_PUD_UP= 2