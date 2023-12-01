library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity control is--模式切换
port(mode:in std_logic_vector(1 downto 0);
	set:in std_logic_vector(1 downto 0);--设置哪一位
	ENs:out std_logic_vector(2 downto 0);--闹钟设置、时间设置、正常工作
	Sets:out std_logic_vector(2 downto 0)--设置使能
	);
end control;

architecture func of control is
begin

process(mode)
begin
	case mode is
		when"00"=>ENs<="001";
		when"01"=>ENs<="010";
		when"11"=>ENs<="100";
		when others=>ENs<="001";
	end case;
end process;

process(set)
begin
	case set is
		when"00"=>Sets<="001";
		when"01"=>Sets<="010";
		when"11"=>Sets<="100";
		when others=>Sets<="001";
	end case;
end process;

end func;