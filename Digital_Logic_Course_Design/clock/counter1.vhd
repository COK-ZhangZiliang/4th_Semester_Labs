library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter1 is
port(cp:in std_logic;--100Hz
	clr:in std_logic;--���� ����Ч
	ENwork:in std_logic;--��������
	ENset:in std_logic;--����ʱ��
	set_vector:in std_logic_vector(6 downto 0);--��������
	counter_time1:out std_logic_vector(3 downto 0);--��ǰʱ��
	counter_time2:out std_logic_vector(6 downto 0);--�߶������
	co1:out std_logic;--��λ�ź�
	check:out std_logic--����ź�
	);
end counter1;

architecture func of counter1 is

signal time1:std_logic_vector(3 downto 0);--��λ
signal time2:std_logic_vector(2 downto 0);--ʮλ

begin

--������	
process(cp,clr,ENwork,ENset,set_vector)
begin
	if(clr='1')then--����
		time2<="000";
		time1<="0000";
	elsif(ENwork='1')then
		if(cp'event and cp='1')then
			if(time1=9)then
				time1<="0000";
				if(time2=5)then
					time2<="000";
				else
					time2<=time2+1;
				end if;
			else
				time1<=time1+1;
			end if;
		end if;
	elsif(ENset='1')then
		time2<=set_vector(6 downto 4);
		time1<=set_vector(3 downto 0);
	end if;
end process;

--��ʾʱ��
counter_time1<="1111" when(ENset='1' and cp='1')else 
			'0'&time2;
			
process(cp,ENset,time1)
begin
	if(ENset='1' and cp='1')then
		counter_time2<="ZZZZZZZ";
	else
		case time1(3 downto 0) is
			when "0000" => counter_time2<="0111111";
			when "0001" => counter_time2<="0000110";
			when "0010" => counter_time2<="1011011";
			when "0011" => counter_time2<="1001111";
			when "0100" => counter_time2<="1100110";
			when "0101" => counter_time2<="1101101";
			when "0110" => counter_time2<="1111101";
			when "0111" => counter_time2<="0000111";
			when "1000" => counter_time2<="1111111";
			when "1001" => counter_time2<="1101111";
			when others => counter_time2<="0000000";
		end case;
	end if;
end process;
		
--��λ
co1<='1' when(time1=9 and time2=5 and ENwork='1')else
	'0';
			
--���Ӽ��
check<='1' when(time2=0 and time1=0)else
     '0';

end func;