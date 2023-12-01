library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_signed.all;
use ieee.numeric_std.all;


entity vga_display is
	port(
		vga_r : out std_logic;
		vga_g : out std_logic;
		vga_b : out std_logic;
		h_sync : out std_logic;
		v_sync : out std_logic;
		clk	  : in std_logic;
		clr   : in std_logic;
		QD    : in std_logic
	);
end vga_display;

architecture rt1 of vga_display is 
-- VGA颜色参数常量
constant black: std_logic_vector(2 downto 0) := "000";
constant red: std_logic_vector(2 downto 0) := "001";
constant blue: std_logic_vector(2 downto 0) := "010";
constant pink: std_logic_vector(2 downto 0) := "011";
constant green: std_logic_vector(2 downto 0) := "100";
constant yellow: std_logic_vector(2 downto 0) := "101";
constant cyan: std_logic_vector(2 downto 0) := "110";
constant white: std_logic_vector(2 downto 0) := "111";	
-- 内部计数器和信号 
signal h_count : std_logic_vector(4 downto 0) := (others => '0'); -- 水平计数器
signal h_part : std_logic_vector(3 downto 0); --水平划分
signal v_count : integer range 0 to 524 := 0; -- 垂直计数器
signal v_part : std_logic_vector(3 downto 0);--垂直划分
signal temp_color : std_logic_vector(2 downto 0);
signal h_end : std_logic;
signal finish : std_logic;
signal LinePart : std_logic_vector(3 downto 0);
signal RowPart : std_logic_vector(3 downto 0); 
signal mode_count : std_logic_vector(1 downto 0) := "00";  -- 模式计数器

	
begin
-- 时序逻辑，生成水平计数器,垂直计数器
process (clk)
begin
    if(clk'event and clk = '1') then
		if h_count = "11111" then
			h_count <= (others => '0');
			if v_count = 524 then
				v_count <= 0;
			else
				v_count <= v_count + 1;
			end if;
		else
			h_count <= h_count + 1;
		end if;
	 end if;
end process;
	
	
--根据水平计数，进行列划分	
process(h_count, v_count)
begin
	if h_count = "00000" then
		h_end <= '1';
		h_part <= "0000";
	else
		h_end <= '0';
		if h_count >= "00001" and h_count <= "00011" then
			h_part <= "0001";
		elsif h_count >= "00100" and h_count <= "00110" then
			h_part <= "0010";
		elsif h_count >= "00111" and h_count <= "01001" then
			h_part <= "0011";
		elsif h_count >= "01010" and h_count <= "01011" then
			h_part <= "0100";
		elsif h_count >= "01100" and h_count <= "01110" then
			h_part <= "0101";
		elsif h_count >= "01111" and h_count <= "10001" then
			h_part <= "0110";
		elsif h_count >= "10010" and h_count <= "10011" then
			h_part <= "0111";
		elsif h_count >= "10100" and h_count <= "10110" then
			h_part <= "0001";
		elsif h_count >= "10111" and h_count <= "11001" then
			h_part <= "1000";
		elsif h_count >= "11010" and h_count <= "11111" then
			h_part <= "0001";
		end if;
	end if;
	LinePart <= h_part;
--根据垂直计数，做行划分
	if v_count < 2 then
		finish <= '1';
		v_part <= "0000";
	else
		finish <= '0';
		if v_count < 65 then
			v_part <= "0001";
		elsif v_count < 128 then
			v_part <= "0010";
		elsif v_count < 191 then
			v_part <= "0011";
		elsif v_count < 254 then
			v_part <= "0100";
		elsif v_count < 319 then
			v_part <= "0101";
		elsif v_count < 392 then
			v_part <= "0110";
		elsif v_count < 456 then
			v_part <= "0111";
		elsif v_count < 525 then
			v_part <= "1000";
		end if;
    end if;
    RowPart <= v_part;
end process;



-- 更新模式计数器
process (QD,clr)
begin 
	if (clr = '0') then
		mode_count <= "00";
	elsif (QD'event and QD = '1') then
		mode_count <= mode_count + 1;
	end if;
end process;

	
	
-- 组合逻辑，根据模式计数器生成temp_color信号	
process (mode_count)
begin
	case mode_count is 
		when "00" =>
			if ( RowPart = "0001" ) then
				if ( LinePart  = "0001") then					
					temp_color <= "000";
				elsif ( LinePart  = "0010") then					
					temp_color <= black;					
				elsif ( LinePart  = "0011") then
					temp_color <= black;							
				elsif ( LinePart  = "0100") then					
					temp_color <= black;						
				elsif ( LinePart  = "0101") then				
					temp_color <= black;						
				elsif ( LinePart  = "0110") then					
					temp_color <= black;					
				elsif ( LinePart  = "0111") then					
					temp_color <= black;							
				elsif ( LinePart  = "1000") then					
					temp_color <= black;	
				else 
					temp_color <= black;				
				end if;
			elsif ( RowPart = "0010") then
				if ( LinePart  = "0001") then					
					temp_color <= red;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red;					
				elsif ( LinePart  = "0011") then
					temp_color <= red;							
				elsif ( LinePart  = "0100") then					
					temp_color <= red;						
				elsif ( LinePart  = "0101") then				
					temp_color <= red;						
				elsif ( LinePart  = "0110") then					
					temp_color <= red;					
				elsif ( LinePart  = "0111") then					
					temp_color <= red;							
				elsif ( LinePart  = "1000") then					
					temp_color <= red;	
				else 
					temp_color <= "000";				
				end if;
			elsif ( RowPart = "0011") then
				if ( LinePart  = "0001") then					
					temp_color <= pink;					
				elsif ( LinePart  = "0010") then					
					temp_color <= pink;				
				elsif ( LinePart  = "0011") then
					temp_color <= pink;					
				elsif ( LinePart  = "0100") then					
					temp_color <= pink;					
				elsif ( LinePart  = "0101") then				
					temp_color <= pink;					
				elsif ( LinePart  = "0110") then					
					temp_color <= pink;					
				elsif ( LinePart  = "0111") then					
					temp_color <= pink;					
				elsif ( LinePart  = "1000") then					
					temp_color <= pink;
				else 
					temp_color <= "000";				
				end if;	
			elsif ( RowPart = "0100") then
				if ( LinePart  = "0001") then					
					temp_color <= green;					
				elsif ( LinePart  = "0010") then					
					temp_color <= green;				
				elsif ( LinePart  = "0011") then
					temp_color <= green;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green;					
				elsif ( LinePart  = "0101") then				
					temp_color <= green;					
				elsif ( LinePart  = "0110") then					
					temp_color <= green;					
				elsif ( LinePart  = "0111") then					
					temp_color <= green;					
				elsif ( LinePart  = "1000") then					
					temp_color <= green;
				else 
					temp_color <= "000";				
				end if;	
			elsif ( RowPart = "0101") then
				if ( LinePart  = "0001") then					
					temp_color <= cyan;					
				elsif ( LinePart  = "0010") then					
					temp_color <= cyan;				
				elsif ( LinePart  = "0011") then
					temp_color <= cyan;					
				elsif ( LinePart  = "0100") then					
					temp_color <= cyan;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan;					
				elsif ( LinePart  = "0110") then					
					temp_color <= cyan;					
				elsif ( LinePart  = "0111") then					
					temp_color <= cyan;					
				elsif ( LinePart  = "1000") then					
					temp_color <= cyan;
				else 
					temp_color <= "000";				
				end if;	
			elsif ( RowPart = "0110") then					
				if ( LinePart  = "0001") then					
					temp_color <= yellow;					
				elsif ( LinePart  = "0010") then					
					temp_color <= yellow;				
				elsif ( LinePart  = "0011") then
					temp_color <= yellow;						
				elsif ( LinePart  = "0100") then					
					temp_color <= yellow;					
				elsif ( LinePart  = "0101") then				
					temp_color <= yellow;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow;						
				elsif ( LinePart  = "0111") then					
					temp_color <= yellow;					
				elsif ( LinePart  = "1000") then					
					temp_color <= yellow;	
				else 
					temp_color <= "000";				
				end if;						
			elsif ( RowPart = "0111") then					
				if ( LinePart  = "0001") then					
					temp_color <= white;					
				elsif ( LinePart  = "0010") then					
					temp_color <= white;				
				elsif ( LinePart  = "0011") then
					temp_color <= white;						
				elsif ( LinePart  = "0100") then					
					temp_color <= white;					
				elsif ( LinePart  = "0101") then				
					temp_color <= white;					
				elsif ( LinePart  = "0110") then					
					temp_color <= white;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white;					
				elsif ( LinePart  = "1000") then					
					temp_color <= white;	
				else 
					temp_color <= "000";				
				end if;							
			elsif ( RowPart = "1000") then					
				if ( LinePart  = "0001") then					
					temp_color <= blue;					
				elsif ( LinePart  = "0010") then					
					temp_color <= blue;					
				elsif ( LinePart  = "0011") then
					temp_color <= blue;							
				elsif ( LinePart  = "0100") then					
					temp_color <= blue;						
				elsif ( LinePart  = "0101") then				
					temp_color <= blue;							
				elsif ( LinePart  = "0110") then					
					temp_color <= blue;						
				elsif ( LinePart  = "0111") then					
					temp_color <= blue;							
				elsif ( LinePart  = "1000") then					
					temp_color <= blue;		
				else 
					temp_color <= "000";				
				end if;					
			else
				temp_color <= "000";
			end if;
--------------------------------------------------------------
		when "01" =>
			if ( LinePart  = "0001") then					
				temp_color <= black;					
			elsif ( LinePart  = "0010") then					
				temp_color <= red;				
			elsif ( LinePart  = "0011") then
				temp_color <= pink;					
			elsif ( LinePart  = "0100") then					
				temp_color <= green;					
			elsif ( LinePart  = "0101") then				
				temp_color <= cyan;					
			elsif ( LinePart  = "0110") then					
				temp_color <= yellow;					
			elsif ( LinePart  = "0111") then					
				temp_color <= white;					
			elsif ( LinePart  = "1000") then					
				temp_color <= blue;
			elsif (LinePart = "0000") then
				temp_color <= "000";				
			end if;
-------------------------------------------------------------
		when "10" =>
			if ( RowPart = "0001" ) then
				if ( LinePart  = "0001") then					
					temp_color <= black xor black;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor black;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor black;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor black;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor black;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor black;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor black;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor black;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;
			elsif ( RowPart = "0010") then
				if ( LinePart  = "0001") then					
					temp_color <= black xor red;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor red;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor red;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor red;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor red;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor red;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor red;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor red;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;
			elsif ( RowPart = "0011") then
				if ( LinePart  = "0001") then					
					temp_color <= black xor pink;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor pink;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor pink;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor pink;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor pink;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor pink;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor pink;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor pink;
				elsif (LinePart = "0000") then
					temp_color <= "000" xor pink;				
				end if;
			elsif ( RowPart = "0100") then
				if ( LinePart  = "0001") then					
					temp_color <= black xor green;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor green;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor green;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor green;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor green;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor green;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor green;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor green;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;
			elsif ( RowPart = "0101") then
				if ( LinePart  = "0001") then					
					temp_color <= black xor cyan;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor cyan;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor cyan;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor cyan;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor cyan;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor cyan;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor cyan;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor cyan;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;
			elsif ( RowPart = "0110") then					
				if ( LinePart  = "0001") then					
					temp_color <= black xor yellow;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor yellow;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor yellow;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor yellow;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor yellow;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor yellow;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor yellow;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor yellow;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;					
			elsif ( RowPart = "0111") then					
				if ( LinePart  = "0001") then					
					temp_color <= black xor white;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor white;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor white;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor white;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor white;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor white;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor white;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor white;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;						
			elsif ( RowPart = "1000") then					
				if ( LinePart  = "0001") then					
					temp_color <= black xor blue;					
				elsif ( LinePart  = "0010") then					
					temp_color <= red xor blue;					
				elsif ( LinePart  = "0011") then
					temp_color <= pink xor blue;					
				elsif ( LinePart  = "0100") then					
					temp_color <= green xor blue;					
				elsif ( LinePart  = "0101") then				
					temp_color <= cyan xor blue;					
				elsif ( LinePart  = "0110") then					
					temp_color <= yellow xor blue;					
				elsif ( LinePart  = "0111") then					
					temp_color <= white xor blue;					
				elsif ( LinePart  = "1000") then					
					temp_color <= blue xor blue;
				elsif (LinePart = "0000") then
					temp_color <= "000";				
				end if;			
			else
				temp_color <= "000";
			end if;
-------------------------------------------------------------
		when "11" =>
			if (finish='0' and h_end='0') then					
				temp_color <= pink;
			else 
				temp_color <= "000";				
			end if;
	end case;
	 
end process;

vga_r <= temp_color(0);
vga_g <= temp_color(1);
vga_b <= temp_color(2);
h_sync <= h_end;
v_sync <= finish;

end rt1;
