library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity alarm is--闹钟
port(
	ENalarm:in std_logic;--闹钟设置使能
	clr_alarm:in std_logic;--清零 高有效
	set_vector:in std_logic_vector(6 downto 0);--设置输入
	alarm_time:out std_logic_vector(6 downto 0)--闹钟时间
	);
end alarm;
architecture func of alarm is
signal time1: std_logic_vector(3 downto 0);
signal time2: std_logic_vector(2 downto 0);
begin
process(ENalarm,clr_alarm,set_vector)
begin

	if (clr_alarm='1') then --清零操作
		time1<="0000";
		time2<="000";
	elsif (ENalarm='1') then --设置操作
		time1<=set_vector(3 downto 0);
		time2<=set_vector(6 downto 4);
	end if;
	
end process;
alarm_time <= time2&time1;
end func;
