library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity control is
port(cp:in std_logic;--100Hz;
	clk:in std_logic;--��˸ʱ���ź�
	mode:in std_logic_vector(1 downto 0);--ģʽ�л�
	isfull:in std_logic;--װ���ź�
	illegal:in std_logic;--�Ƿ�����
	start:in std_logic;--��ʼ/��ͣ
	green:out std_logic;--�̵�
	red:out std_logic;--���
	en:out std_logic_vector(3 downto 0);--ʹ���ź� 00-0001 01-0010 10-0100 11-1000
	en_display:out std_logic;--��ʾʹ��
	loudspeaker:out std_logic--����
);
end control;

architecture func of control is

begin

process(mode, start, isfull)
begin
	case mode is
		when "00" => en <= "0001";
			en_display <= '1';
		when "01" => en(3 downto 2) <= "00";
			en(1) <= '1' and start and (not isfull);
			en(0) <= '0'; 
			en_display <= '0';
		when "10" => en(3 downto 2) <= "01";
			en(1) <= '1' and start and (not isfull);
			en(0) <= '0';
			en_display <= '1';
		when others => en <= "1000";
			en_display <= '1';
	end case;
end process;

process(isfull,illegal,clk,mode,start)
begin 
	if(illegal = '1')then
		green <= '0';
		red <= clk;
		loudspeaker <= clk and cp;
	elsif(isfull = '1' or start = '0')then
		green <= '0';
		red <= '1';
		loudspeaker <= '0';
	elsif((mode = "01") or (mode = "10"))then
		green <= '1';
		red <= '0';
		loudspeaker <= '0';
	else 
		red <= '0';
		green <= '0';
		loudspeaker <= '0';
	end if;
end process;

end func;
		
		
