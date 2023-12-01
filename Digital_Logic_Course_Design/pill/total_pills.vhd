library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity total_pills is
port(
	clr:in std_logic;--清零信号
	clk:in std_logic;--时钟信号
	en:in std_logic;--使能信号
	pills_num:out std_logic_vector(11 downto 0)--总药片数
);
end total_pills;
architecture fun of total_pills is

signal one: std_logic_vector(3 downto 0);
signal ten: std_logic_vector(3 downto 0);
signal hun: std_logic_vector(3 downto 0);

begin

process(clr, clk, en, one, ten, hun)
begin
	if (clr = '1') then
		one <= "0000";
		ten <= "0000";
		hun <= "0000";
	elsif(en = '1') then
		if (clk'event and clk = '1') then
			if (hun = 9 and ten = 0 and one = 0) then
				one <= "0000";
				ten <= "0000";
				hun <= "0000";
			end if;
			if (one = 9) then
				if (ten = 9) then
					one <= "0000";
					ten <= "0000";
					hun <= hun + 1;
				else
					one <= "0000";
					ten <= ten + 1;
				end if;
			else
				one <= one + 1;
			end if;
		end if;
	end if;
end process;

pills_num <= hun & ten & one;

end fun;
