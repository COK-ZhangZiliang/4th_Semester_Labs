library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity pill is
port(cp:in std_logic;--100Hz
	clk:in std_logic;--ʱ���ź�
	clr:in std_logic;--�����ź�
	mode:in std_logic_vector(1 downto 0);--ģʽ�л�
	max:in std_logic_vector(7 downto 0);--�趨����
	set:in std_logic;--0 ����ҩƬ�� 1 ����ƿ��
	start:in std_logic;--��ʼ/��ͣ
	led:out std_logic_vector(19 downto 0);--�������ʾ
	green:out std_logic;--�̵�
	red:out std_logic;--���
	loudspeaker:out std_logic--����
);
end pill;

architecture func of pill is

--00 ��ʾ���õ�ÿƿҩƬ�����ֵ �� ���õ�ƿ�����ֵ����˸��
--01 ��ʾ��ǰҩƬ���� �� ��ǰ��ƿҩƬ������
--10 ��ʾ��ǰƿ��
--11 ��ʾ���õ�ÿƿҩƬ�����ֵ �� ���õ�ƿ�����ֵ
component control
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
end component;

component total_pills
port(clr:in std_logic;--�����ź�
	clk:in std_logic;--ʱ���ź�
	en:in std_logic;--ʹ���ź�
	pills_num:out std_logic_vector(11 downto 0)--��ҩƬ��
);
end component;

component per_bottle
port(clr:in std_logic;--�����ź�
	clk:in std_logic;--ʱ���ź�
	en:in std_logic;--ʹ���ź�
	max:in std_logic_vector(7 downto 0);--�趨����
	en_max:in std_logic;--��ʾmaxʹ��
	en_set:in std_logic;--����ʹ��
	set:in std_logic;--0 ����ҩƬ��
	co:out std_logic;--��λ�ź�
	led:out std_logic_vector(7 downto 0);--�������ʾ��ƿҩƬ��
	illegal:out std_logic--�Ƿ�����
);
end component;

component display
port(pills_num:in std_logic_vector(11 downto 0);--��ҩƬ��
	bottles_num:in std_logic_vector(7 downto 0);--ƿ��/���ƿ��
	en_display:in std_logic;--��ʾʹ��
	led:out std_logic_vector(11 downto 0)--�������ʾ
);
end component;

signal isfull1:std_logic;--װ���ź�
signal co:std_logic;--��λ�ź�
signal illegal1:std_logic;--�Ƿ�����
signal illegal2:std_logic;--�Ƿ�����
signal en1:std_logic_vector(3 downto 0);--ʹ���ź�
signal en_display1:std_logic;--��ʾʹ��
signal pills_num1:std_logic_vector(11 downto 0);--��ҩƬ��
signal bottles_num1:std_logic_vector(7 downto 0);--ƿ��/���ƿ��


begin

u1:control port map(cp,clk,mode,isfull1,illegal1 or illegal2,start,green,red,en1,en_display1,loudspeaker);
u2:total_pills port map(clr,clk,en1(1),pills_num1);
u3:per_bottle port map(clr,clk,co,max,en1(3),en1(0),not(set),isfull1,bottles_num1,illegal2);
u4:per_bottle port map(clr,clk,en1(1),max,en1(3),en1(0),set,co,led(7 downto 0),illegal1);
u5:display port map(pills_num1,bottles_num1,en_display1,led(19 downto 8));

end func;