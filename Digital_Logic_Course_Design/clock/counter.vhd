library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter is
port(limit1:in integer range 9 downto 0;
	limit2:in integer range 5 downto 0;
	cp:in std_logic;--1Hz
	clr:in std_logic;--清零 高有效
	ENwork:in std_logic;--正常工作
	--show:in std_logic;--显示选择
	ENset:in std_logic;--设置时间
	ENalarm:in std_logic;--设置闹钟
	set_vector:in std_logic_vector(6 downto 0);--设置输入
	EN_alarm_check:in std_logic;--是否进行闹钟检测
	EN_loudspeaker:out std_logic;--整点报时/闹钟
	counter_time:out std_logic_vector(6 downto 0);--当前时间
	EN_flicker:out std_logic;--闪烁使能
	co1:out std_logic;--进位信号
	check:out std_logic--检测信号
	);
end counter;

architecture func of counter is
signal time1:std_logic_vector(3 downto 0);--个位
signal time2:std_logic_vector(2 downto 0);--十位
signal alarm1:std_logic_vector(3 downto 0);--个位
signal alarm2:std_logic_vector(2 downto 0);--十位
begin

--计数器	
process(cp,clr,ENwork,ENset,set_vector,ENalarm)
begin
	if(clr='1')then--清零
		time2<="000";
		time1<="0000";
	elsif(ENwork='1')then
		if(cp'event and cp='1')then
			if(time1=limit1)then
				time1<="0000";
				if(time2=limit2)then
					time2<="000";
				else
					time2<=time2+1;
				end if;
			else
				time1<=time1+1;
			end if;
		end if;
	elsif(ENset='1')then
		time2<=set_vector(6 downto 4);
		time1<=set_vector(3 downto 0);
	end if;
end process;

--设置闹钟,选择显示时间
process(ENalarm)
begin
	if(ENalarm='1')then
		alarm2<=set_vector(6 downto 4);
		alarm1<=set_vector(3 downto 0);
		counter_time<=alarm2&alarm1;
	else
		counter_time<=time2&time1;
	end if;
end process;

		
--闪烁
EN_flicker<=ENset or ENalarm;

--进位
co1<='1' when(time1=limit1 and time2=limit2 and ENwork='1')else
	'0';
			
--闹钟检测
check<='1' when(EN_alarm_check='1' and time2=alarm2 and time1=alarm1)else
     '0';

--整点检测
EN_loudspeaker<=ENwork;

end func;