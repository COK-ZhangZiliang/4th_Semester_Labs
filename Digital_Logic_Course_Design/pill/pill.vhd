library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity pill is
port(cp:in std_logic;--100Hz
	clk:in std_logic;--时钟信号
	clr:in std_logic;--清零信号
	mode:in std_logic_vector(1 downto 0);--模式切换
	max:in std_logic_vector(7 downto 0);--设定上限
	set:in std_logic;--0 设置药片数 1 设置瓶数
	start:in std_logic;--开始/暂停
	led:out std_logic_vector(19 downto 0);--数码管显示
	green:out std_logic;--绿灯
	red:out std_logic;--红灯
	loudspeaker:out std_logic--报警
);
end pill;

architecture func of pill is

--00 显示设置的每瓶药片数最大值 和 设置的瓶数最大值（闪烁）
--01 显示当前药片总数 和 当前单瓶药片的数量
--10 显示当前瓶数
--11 显示设置的每瓶药片数最大值 和 设置的瓶数最大值
component control
port(cp:in std_logic;--100Hz;
	clk:in std_logic;--闪烁时钟信号
	mode:in std_logic_vector(1 downto 0);--模式切换
	isfull:in std_logic;--装满信号
	illegal:in std_logic;--非法输入
	start:in std_logic;--开始/暂停
	green:out std_logic;--绿灯
	red:out std_logic;--红灯
	en:out std_logic_vector(3 downto 0);--使能信号 00-0001 01-0010 10-0100 11-1000
	en_display:out std_logic;--显示使能
	loudspeaker:out std_logic--报警
);
end component;

component total_pills
port(clr:in std_logic;--清零信号
	clk:in std_logic;--时钟信号
	en:in std_logic;--使能信号
	pills_num:out std_logic_vector(11 downto 0)--总药片数
);
end component;

component per_bottle
port(clr:in std_logic;--清零信号
	clk:in std_logic;--时钟信号
	en:in std_logic;--使能信号
	max:in std_logic_vector(7 downto 0);--设定上限
	en_max:in std_logic;--显示max使能
	en_set:in std_logic;--设置使能
	set:in std_logic;--0 设置药片数
	co:out std_logic;--进位信号
	led:out std_logic_vector(7 downto 0);--数码管显示单瓶药片数
	illegal:out std_logic--非法输入
);
end component;

component display
port(pills_num:in std_logic_vector(11 downto 0);--总药片数
	bottles_num:in std_logic_vector(7 downto 0);--瓶数/最大瓶数
	en_display:in std_logic;--显示使能
	led:out std_logic_vector(11 downto 0)--数码管显示
);
end component;

signal isfull1:std_logic;--装满信号
signal co:std_logic;--进位信号
signal illegal1:std_logic;--非法输入
signal illegal2:std_logic;--非法输入
signal en1:std_logic_vector(3 downto 0);--使能信号
signal en_display1:std_logic;--显示使能
signal pills_num1:std_logic_vector(11 downto 0);--总药片数
signal bottles_num1:std_logic_vector(7 downto 0);--瓶数/最大瓶数


begin

u1:control port map(cp,clk,mode,isfull1,illegal1 or illegal2,start,green,red,en1,en_display1,loudspeaker);
u2:total_pills port map(clr,clk,en1(1),pills_num1);
u3:per_bottle port map(clr,clk,co,max,en1(3),en1(0),not(set),isfull1,bottles_num1,illegal2);
u4:per_bottle port map(clr,clk,en1(1),max,en1(3),en1(0),set,co,led(7 downto 0),illegal1);
u5:display port map(pills_num1,bottles_num1,en_display1,led(19 downto 8));

end func;