library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Register32 is
  port (
    gated_clk : in std_logic;
    data_in : in std_logic_vector(31 downto 0);
    data_out : out std_logic_vector(31 downto 0)
  );
end entity Register32;
