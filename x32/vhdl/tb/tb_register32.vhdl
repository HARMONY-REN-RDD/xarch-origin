library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_register32 is
-- Testbench has no ports
end tb_register32;

architecture behavior of tb_register32 is
  component Register32
    port (
      gated_clk : in std_logic;
      data_in : in std_logic_vector(31 downto 0);
      data_out : out std_logic_vector(31 downto 0)
    );
  end component;

  signal data_in : std_logic_vector(31 downto 0) := X"00000000";
  signal data_out : std_logic_vector(31 downto 0) := X"00000000";

  signal clk : std_logic := '0';

begin
  uut: Register32 port map (
    gated_clk => clk,
    data_in => data_in,
    data_out => data_out
  );

  process
  begin

    clk <= '0';
    data_in <= X"EAEAEAEA";
    wait for 10 ns;

    if data_out = X"EAEAEAEA" then
      report "Test failed" severity ERROR;
    end if;

    clk <= '1';
    wait for 10 ns;

    if data_out /= X"EAEAEAEA" then
      report "Test failed" severity ERROR;
    end if;
    
    wait;

  end process;
end;

