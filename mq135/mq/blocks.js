var mq_color_hue = 190;

Blockly.Blocks["mq.data"] = {
    init: function() {
        this.appendDummyInput()
            .appendField("Read MQ-135 value");

        this.setOutput(true, 'Number');
        this.setInputsInline(false);
        this.setColour(mq_color_hue);
        this.setTooltip("value from mq");
        this.setHelpUrl(Blockly.Msg.BLINK_START_HELPURL);
    }
};

// Blockly.Blocks["mq.recieved"] = {
//     init: function() {
//         this.appendDummyInput()
//             .appendField("recieved mq");

//         this.appendStatementInput("DO")
//             .appendField("do");

//         this.setInputsInline(false);
//         this.setPreviousStatement(true);
//         this.setNextStatement(true);
//         this.setColour(mq_color_hue);
//         this.setTooltip("18 = trig, 19 = echo");
//         this.setHelpUrl(Blockly.Msg.BLINK_START_HELPURL);
//     }
// };

// Blockly.Blocks["mq.didEnter"] = {
//     init: function() {
//         this.appendDummyInput()
//             .appendField("did enter mq");

//         this.appendStatementInput("DO")
//             .appendField("do");

//         this.setInputsInline(false);
//         this.setPreviousStatement(true);
//         this.setNextStatement(true);
//         this.setColour(mq_color_hue);
//         this.setTooltip("18 = trig, 19 = echo");
//         this.setHelpUrl(Blockly.Msg.BLINK_START_HELPURL);
//     }
// };


