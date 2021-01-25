var mq_color_hue = 190;

Blockly.Blocks["mq.data"] = {
  init: function () {
    this.appendDummyInput().appendField("Read MQ-135 value");

    this.setOutput(true, "Number");
    this.setInputsInline(false);
    this.setColour(mq_color_hue);
    this.setTooltip("value from mq");
    this.setHelpUrl(Blockly.Msg.BLINK_START_HELPURL);
  },
};
