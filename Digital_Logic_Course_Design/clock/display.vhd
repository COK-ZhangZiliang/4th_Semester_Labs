library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity display is 
port(cp_flicker:in std_logic;
    time_display:in std_logic_vector(20 downto 0);--传入时间
	EN_flicker:in std_logic_vector(2 downto 0);--是否闪烁
	ledout1:out std_logic_vector(6 downto 0);--驱动7段发光管
	ledout2:out std_logic_vector(19 downto 0)--5个七段显示译码器
	);
end display;

architecture dis_play of display is
begin
 
	process(cp_flicker,EN_flicker,time_display)
	begin
		case time_display(3 downto 0) is
			when "0000" => ledout1<="0111111";
			when "0001" => ledout1<="0000110";
			when "0010" => ledout1<="1011011";
			when "0011" => ledout1<="1001111";
			when "0100" => ledout1<="1100110";
			when "0101" => ledout1<="1101101";
			when "0110" => ledout1<="1111101";
			when "0111" => ledout1<="0000111";
			when "1000" => ledout1<="1111111";
			when "1001" => ledout1<="1101111";
			when others => ledout1<="0000000";
		end case;
	
		ledout2 <="0"&time_display(20 downto 18)&time_display(17 downto 14)&'0'&time_display(13 downto 11)&time_display(10 downto 7)&'0'&time_display(6 downto 4);	
		
		if(cp_flicker='1') then
			case EN_flicker is
				when "001" => ledout2(3 downto 0)<="1111";
									ledout1<="ZZZZZZZ";
				when "010" => ledout2(11 downto 4) <="ZZZZZZZZ";
				when "100" => ledout2(19 downto 12) <="ZZZZZZZZ";
				when others  => null;
			end case;
		end if; 
	end process;
	
end dis_play;
