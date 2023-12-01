library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity director is  
    port (
        clk_i    : in std_logic; --10000hz/100hz
        div   :in std_logic_vector(3 downto 0);
        clk_o :out std_logic
    );
end director;

architecture dir of director is 
      
    signal count_t: std_logic_vector(3 downto 0):="0001";
    signal clk_temp :std_logic:='0' ;

begin

process(div,clk_i)	
	begin
	if(clk_i'event and clk_i='1')then
		if count_t = div then
			count_t <= "0001";
			clk_temp<='1';
		else
			count_t <= count_t + 1;
			clk_temp<='0';
		end if;
	end if;
end process;

clk_o<=clk_temp;
end dir;