library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity display is
port(pills_num:in std_logic_vector(11 downto 0);--总药片数
	bottles_num:in std_logic_vector(7 downto 0);--瓶数/最大瓶数
	en_display:in std_logic;--显示使能
	led:out std_logic_vector(11 downto 0)--数码管显示
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
