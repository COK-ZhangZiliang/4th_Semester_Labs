library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity per_bottle is
port(clr:in std_logic;--清零信号
	clk:in std_logic;--时钟信号
	en:in std_logic;--使能信号
	max:in std_logic_vector(7 downto 0);--设定上限
	en_max:in std_logic;--显示max使能
	en_set:in std_logic;--设置使能
	set:in std_logic;--0 设置药片数
	co:out std_logic;--进位信号
	led:out std_logic_vector(7 downto 0);--数码管显示单瓶药片数
	illegal:out std_logic--非法输入
);
end per_bottle;

architecture func of per_bottle is

signal pills_l:std_logic_vector(3 downto 0);
signal pills_h:std_logic_vector(3 downto 0);
signal max_value:std_logic_vector(7 downto 0);

begin


process(clr,clk,en,max_value)--模可控计数器
begin
	if(clr = '1')then
		pills_h <= "0000";
		pills_l <= "0000";
	elsif(en = '1')then 
		if(clk'event and clk = '1')then
			if(pills_h & pills_l = max_value)then
				pills_h <= "0000";
				pills_l <= "0000";
			elsif(pills_l = 9)then
				pills_l <= "0000";
			    pills_h <= pills_h + 1;
			else
				pills_l <= pills_l + 1;
			end if;
		end if;
	end if;
end process;


process(pills_h,pills_l,en)--进位
begin 
	if(pills_h & pills_l = max_value)then
		co <= '1';
	else
		co <= '0';
	end if;
end process;

process(clk,clr,en_set,set,max)--设定上限
begin
	if(clk'event and clk = '1')then
		if(en_set = '1' and clr = '1')then
			max_value <= "00000000";
		elsif(en_set = '1' and set = '0' and max(7 downto 4) <= 9 and max(3 downto 0) <= 9)then
			max_value <= max;
		end if;
	end if;
end process;


process(max_value,max)--非法输入检测
begin
	if(max_value(7 downto 4) > 3 or ((max_value(7 downto 4) = 3) and (max_value(3 downto 0) > 0) ) or max(3 downto 0) > 9 or max(7 downto 4) > 9)then
		illegal <= '1';
	else 
		illegal <= '0';
	end if;
end process;


led <= max_value when((en_set ='1' and set ='0' and clk = '1') or (en_max = '1'))else
	"ZZZZ1111" when(en_set ='1' and set ='0' and clk = '0')else
	max_value when(en_set ='1')else
	pills_h & pills_l;
	
end func; 