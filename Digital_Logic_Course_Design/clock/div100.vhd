library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity div100 is
  port(clk_100 : in std_logic;
    clk_1   : out std_logic
  );
end div100;

architecture div of div100 is
  signal count : std_logic_vector(6 downto 0) := (others => '0');
begin
  process(clk_100)
  begin
    if rising_edge(clk_100) then
      if count = "1100011" then--1100011
        count <= (others => '0');
      else
        count <= count + 1;
      end if;
    end if;
  end process;

  clk_1 <= '1' when count < "0110010" else '0';--110010

end div;