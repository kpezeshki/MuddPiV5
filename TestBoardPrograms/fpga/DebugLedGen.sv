//DebugLedGen.sv
//Kaveh Pezeshki 1/31/2019
//Generates a 1Hz LED blink from an input 1MHz clock for the test board
//If a blink is produced, the FPGA and MCU are both functional


module debugLedGen (
                    input clk,
                    output led
    
                   );

    //Internal signals
    reg [20:0] clk_divide; //an input 1MHz clock is divided by 20 to produce a 1Hz output

    //Combinational logic
    assign led = clk[20];

    //Sequential logic
    always_ff @(posedge clk)
        begin
            clk <= clk + 1;
        end

endmodule
    