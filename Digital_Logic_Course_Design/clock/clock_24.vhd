library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity clock_24 is
port(clk:in std_logic;--100Hz
	clr:in std_logic;--���� ����Ч
	alarm_state:in std_logic;--������/�ر�����
	mode:in std_logic_vector(1 downto 0);--00��������	01����ʱ��	11��������
	set:in std_logic_vector(1 downto 0);--������һλ
	set_vector:in std_logic_vector(6 downto 0);--��������
	cp_in:in std_logic;--����������Ƶ��10000Hz
	cp_out:out std_logic;--���������Ƶ��
	ledout1:out std_logic_vector(6 downto 0);--����7�η����
	ledout2:out std_logic_vector(19 downto 0)--5���߶���ʾ������
	);
end clock_24;



architecture func of clock_24 is

component control--ģʽ�л�
port(mode:in std_logic_vector(1 downto 0);
	set:in std_logic_vector(1 downto 0);--������һλ
	ENs:out std_logic_vector(2 downto 0);--�������á�ʱ�����á���������
	Sets:out std_logic_vector(2 downto 0)--����ʹ��
	);
end component;

component counter1
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
end component;

component counter2
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
end component;

component loudspeaker--������
port(en_music:in std_logic;
	clk:in std_logic;   --1hz
	clk_i:in std_logic; --10000hz
	clk_o:out std_logic
	);
end component;

component div100--100��Ƶ 
port(clk_100:in std_logic;
    clk_1:out std_logic
  );
end component;

signal ENs:std_logic_vector(2 downto 0);--״̬ʹ���ź�
signal Sets:std_logic_vector(2 downto 0);--����ʹ���ź�
signal en_lp2:std_logic;--������ʹ��
signal en_lp3:std_logic;--������ʹ��
signal cp:std_logic;--1Hz
signal co11:std_logic;
signal co12:std_logic;
signal co21:std_logic;
signal co22:std_logic;
signal co31:std_logic;
signal co32:std_logic;
signal div:std_logic_vector(3 downto 0);

begin
u1:control port map(mode,set,ENs,Sets);
u2:counter1 port map(cp,clr,ENs(0),ENs(1) and Sets(0),set_vector,ledout2(3 downto 0),ledout1,co11,co12);
u3:counter2 port map(9,5,cp,clr,co11,ENs(2),ENs(1) and Sets(1),ENs(2) and Sets(1),set_vector,alarm_state,en_lp2,ledout2(11 downto 4),co21,co22);
u4:counter2 port map(3,2,cp,clr,co21,ENs(2),ENs(1) and Sets(2),ENs(2) and Sets(2),set_vector,alarm_state,en_lp3,ledout2(19 downto 12),co31,co32);
u5:div100 port map(clk,cp);
u6:loudspeaker port map(en_lp3 or (co32 and co22 and co12),cp,cp_in,cp_out);
end func;