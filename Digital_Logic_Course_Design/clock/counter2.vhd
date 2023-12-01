library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter2 is
port(limit1:in integer range 9 downto 0;
	limit2:in integer range 5 downto 0;
	cp:in std_logic;--100Hz
	clr:in std_logic;--���� ����Ч
	ENwork:in std_logic;--��������
	show:in std_logic;--��ʾѡ��
	ENset:in std_logic;--����ʱ��
	ENalarm:in std_logic;--��������
	set_vector:in std_logic_vector(6 downto 0);--��������
	EN_alarm_check:in std_logic;--�Ƿ�������Ӽ��
	EN_loudspeaker:out std_logic;--���㱨ʱ/����
	counter_time:out std_logic_vector(7 downto 0);--��ǰʱ��
	co1:out std_logic;--��λ�ź�
	check:out std_logic--����ź�
	);
end counter2;

architecture func of counter2 is

signal time1:std_logic_vector(3 downto 0);--��λ
signal time2:std_logic_vector(2 downto 0);--ʮλ
signal alarm1:std_logic_vector(3 downto 0);--��λ
signal alarm2:std_logic_vector(2 downto 0);--ʮλ

begin

--������	
process(cp,clr,ENwork,ENset,set_vector)
begin
	if(clr='1')then--����
		time2<="000";
		time1<="0000";
	elsif(ENwork='1')then
		if(cp'event and cp='1')then
			if(time1=limit1)then
				time1<="0000";
				if(time2=limit2)then
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

--��������
process(ENalarm)
begin
	if(ENalarm='1')then
		alarm2<=set_vector(6 downto 4);
		alarm1<=set_vector(3 downto 0);
	end if;
end process;

--ѡ����ʾʱ��
counter_time<="11111111" when((ENset='1' or ENalarm='1')and cp='1')else 
			'0'&time2&time1 when(show ='0')else
			'0'&alarm2&alarm1;

--��λ
co1<='1' when(time1=limit1 and time2=limit2 and ENwork='1')else
	'0';
			
--���Ӽ��
check<='1' when(EN_alarm_check='1' and time2=alarm2 and time1=alarm1)else
     '0';

--������
EN_loudspeaker<=ENwork;

end func;