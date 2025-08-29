architecture register32_arch of Register32 is
begin
  process(gated_clk)
  begin
    if rising_edge(gated_clk) then
      data_out <= data_in;
    end if;
  end process;
end architecture register32_arch;
