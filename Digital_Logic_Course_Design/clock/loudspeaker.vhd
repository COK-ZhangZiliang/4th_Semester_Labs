library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity loudspeaker is
port(en_music:in std_logic;
	clk:in std_logic;   --1hz
	clk_i:in std_logic; --10000hz
	clk_o:out std_logic
	);
end loudspeaker;

architecture func of loudspeaker is
signal count1:std_logic_vector(2 downto 0) := (others => '1');
signal count2:std_logic_vector(5 downto 0) := (others => '1');
signal div:std_logic_vector(5 downto 0) := (others => '0');


begin

	process(clk,en_music)	
	begin 
		if (clk'event and clk = '1') then
			if(en_music='1') then
				count1<="000";
			end if;
			if count1 < "101" then
				count1 <= count1 + 1;
			end if;
             --38   34   31   29   26    23   20
            case count1 is
                 when "000" =>  
                     div <= "100110"; 
                 when  "001"=>     
                     div <= "100010"; 
                 when  "010"=>     
                     div <= "100000"; 
                 when  "011"=>     
                     div <= "011110";
                 when  "100"=>
					 div <= "011010";
                 when  others =>
                     div <= "000000";
            end case;
		end if;
	end process;
	
	process(div,clk_i)
	begin
	if(div > 0)then
		if rising_edge(clk_i) then
			if count2 = div then
				count2 <= (others => '0');
			else
				count2 <= count2 + 1;
			end if;
		end if;
	end if;
	end process;
	
	clk_o <= '1' when(count2 < '0'&div(5 downto 1) and div > 0)else '0';	
	
end func;