library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity alarm is--����
port(
	ENalarm:in std_logic;--��������ʹ��
	clr_alarm:in std_logic;--���� ����Ч
	set_vector:in std_logic_vector(6 downto 0);--��������
	alarm_time:out std_logic_vector(6 downto 0)--����ʱ��
	);
end alarm;
architecture func of alarm is
signal time1: std_logic_vector(3 downto 0);
signal time2: std_logic_vector(2 downto 0);
begin
process(ENalarm,clr_alarm,set_vector)
begin

	if (clr_alarm='1') then --�������
		time1<="0000";
		time2<="000";
	elsif (ENalarm='1') then --���ò���
		time1<=set_vector(3 downto 0);
		time2<=set_vector(6 downto 4);
	end if;
	
end process;
alarm_time <= time2&time1;
end func;
