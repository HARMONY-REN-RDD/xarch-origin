library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_test is
-- Testbench has no ports
end tb_test;

architecture behavior of tb_test is
  component Test
    port (
      a : in std_logic;
      b : out std_logic
    );
  end component;

  signal a : std_logic := '0';
  signal b : std_logic;

begin
  uut: Test port map (
    a => a,
    b => b
  );

  process
  begin
    a <= '0';
    wait for 10 ns;
    a <= '1';
    wait for 10 ns;

    if b = '1' then
      REPORT "TEST FAILED: ALU OUTPUT MISMATCH" SEVERITY ERROR;
    end if;

    wait;

  end process;
end;

