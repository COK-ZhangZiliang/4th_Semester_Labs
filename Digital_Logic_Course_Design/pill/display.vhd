library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity display is
port(pills_num:in std_logic_vector(11 downto 0);--��ҩƬ��
	bottles_num:in std_logic_vector(7 downto 0);--ƿ��/���ƿ��
	en_display:in std_logic;--��ʾʹ��
	led:out std_logic_vector(11 downto 0)--�������ʾ
);
end display;

architecture ar of display is
begin
process(pills_num,bottles_num,en_display)
begin
	if(en_display='0')then
		led<=pills_num;
	else
		led(7 downto 0)<=bottles_num;
		led(11 downto 8)<="ZZZZ";
	end if;
end process;
end ar;
